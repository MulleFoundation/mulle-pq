#import "import-private.h"

#include <stdio.h>

#include "mulle-pq-version.h"
#include "mulle-clioption.h"


typedef NS_ENUM( int, plist_format)
{
   unknown,
   json,
   plist,
   xml
};


static NS_ENUM_TABLE( plist_format, 4) =
{
   NS_ENUM_ITEM( unknown),
   NS_ENUM_ITEM( json),
   NS_ENUM_ITEM( plist),
   NS_ENUM_ITEM( xml)
};


int   option_plist_format_conversion( struct mulle_clioption *o,
                                      char *s,
                                      struct mulle_clioptionparser *p)
{
   int   value;

   value = NS_ENUM_PARSE( plist_format, s);
   *_mulle_clioption_get_config_field_pointer( p->config, o->config_offset, int) = value;
   return( 0);
}


struct config
{
   enum plist_format   in_format;
   enum plist_format   out_format;
   BOOL                jq;
   char                *in_filename;
   char                *out_filename;
};


static inline void   _config_init( struct config *config)
{
   memset( config, 0, sizeof( *config));
   config->jq         = 1;
   config->out_format = plist;
}


// don't const it, because usage will sort it
static struct mulle_clioption  options[] =
{
   mulle_clioption_no_data( "don't run input plist through jq",
                             "--no-jq",
                             offsetof( struct config, jq)),
   {
      "input format one of json,xml,plist (auto)",
      "--in-format",
      YES,
      offsetof( struct config, in_format),
      option_plist_format_conversion
   },
   {
      "output format one of json,xml,(plist)",
      "--out-format",
      YES,
      offsetof( struct config, out_format),
      option_plist_format_conversion
   },
   mulle_clioption_string_argument_data( "input file (stdin)",
                                         "--in",
                                         offsetof( struct config, in_filename)),
   mulle_clioption_string_argument_data( "output file (stdout)",
                                         "--out",
                                         offsetof( struct config, out_filename)),
   mulle_clioption_alias( "-i","--in"),
   mulle_clioption_alias( "-o", "--out"),
   { 0 }
};



static char  usage_text[] =
"Usage: %s [options] ...\n"
"\n"
"   Convert between JSON, Plist, XML format.\n"
"   Any arguments after the known options are interpreted to be jq arguments.\n"
"   jq will be invoked and given the parsed input. The result of the jq\n"
"   command then will undergo output conversion.\n"
"\n"
"Options:\n";



int  main( int argc, char *argv[])
{
   struct config                  config;
   struct mulle_clioptionparser   parser;
   NSError                        *error;
   NSPropertyListFormat           plistFormat;
   NSFileHandle                   *input;
   NSFileHandle                   *output;
   NSData                         *data;
   NSData                         *filteredData;
   NSMutableArray                 *arguments;
   NSData                         *convertedData;
   int                            i;
   id                             propertyList;

#if defined( DEBUG)
   if( mulle_objc_global_check_universe( __MULLE_OBJC_UNIVERSENAME__) != mulle_objc_universe_is_ok)
      abort();
#endif

   _config_init( &config);
   mulle_clioptionparser_init( &parser, options, &config, usage_text);
   mulle_clioptionparser_set_argv0( &parser, argv[ 0]);

   i = mulle_clioptionparser_argc_argv( &parser, argc, (const char **) argv);
   if( i == 0)
      return( 1);
   if( i != argc && ! config.jq)
      mulle_clioptionparser_usage( &parser, "Superflous argument \"%s\" ...", argv[ i]);

   if( config.in_filename && strcmp( config.in_filename, "-"))
   {
      input = [NSFileHandle fileHandleForReadingAtPath:@( config.in_filename)];
      if( ! input)
      {
         mulle_fprintf( stderr, "could not read \"%s\"\n", config.in_filename);
         exit( 1);
      }
   }
   else
      input = [NSFileHandle fileHandleWithStandardInput];
   data = [input readDataToEndOfFile];
   if( ! [data length])
   {
      mulle_fprintf( stderr, "empty property list is useless\n");
      exit( 1);
   }

   switch( config.in_format)
   {
   case json  : plistFormat = MullePropertyListJSONFormat; break;
   case xml   : plistFormat = NSPropertyListXMLFormat_v1_0; break;
   case plist : plistFormat = NSPropertyListOpenStepFormat; break;
   default    : plistFormat = 0; break;
   }
   propertyList = [NSPropertyListSerialization propertyListWithData:data
                                                            options:0
                                                             format:&plistFormat
                                                              error:&error];
   if( ! propertyList)
   {
      mulle_fprintf( stderr,
                     "input could not be parsed: %@\n",
                     error ? error : @"???");
      exit( 1);
   }

   if( config.jq)
   {
      convertedData = [NSPropertyListSerialization dataWithPropertyList:propertyList
                                                                 format:MullePropertyListJSONFormat
                                                                options:0
                                                                  error:&error];
      if( ! convertedData)
      {
         mulle_fprintf( stderr,
                        "Could not be converted to intermediate JSON: %@\n",
                        error ? error : @"???");
         exit( 1);
      }

      arguments = [NSMutableArray arrayWithObject:@"jq"];
      while( i < argc)
         [arguments addObject:@( argv[ i++])];

      filteredData = [NSTask mulleSystem:arguments
                        workingDirectory:nil
                      standardOutputData:convertedData];

      // assume jq said enough
      if( ! filteredData)
      {
         mulle_fprintf( stderr, "jq failed\n");
         exit( 1);
      }

      plistFormat  = MullePropertyListJSONFormat;
      propertyList = [NSPropertyListSerialization propertyListWithData:filteredData
                                                               options:0
                                                                format:&plistFormat
                                                                 error:&error];
      if( ! propertyList)
      {
         mulle_fprintf( stderr,
                        "jq output could not be parsed as JSON: %@\n",
                        error ? error : @"???");
         exit( 1);
      }
   }

   switch( config.out_format)
   {
   case json : plistFormat = MullePropertyListJSONFormat; break;
   case xml  : plistFormat = NSPropertyListXMLFormat_v1_0; break;
   default   : plistFormat = NSPropertyListOpenStepFormat; break;
   }

   if( config.jq || plistFormat != MullePropertyListJSONFormat)
   {
      convertedData = [NSPropertyListSerialization dataWithPropertyList:propertyList
                                                                 format:plistFormat
                                                                options:0
                                                                  error:&error];
      if( ! convertedData)
      {
         mulle_fprintf( stderr,
                        "output could not be converted: %@\n",
                        error ? error : @"???");
         exit( 1);
      }
   }

   if( config.out_filename && strcmp( config.out_filename, "-"))
      output = [NSFileHandle fileHandleForWritingAtPath:@( config.out_filename)];
   else
      output = [NSFileHandle fileHandleWithStandardOutput];
   [output writeData:convertedData];
   [output closeFile];

   return( 0);
}
