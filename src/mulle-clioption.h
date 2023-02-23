#ifndef mulle_clioption_h__
#define mulle_clioption_h__

#include <stdarg.h>
#include <string.h>



#undef _mulle_clioption_get_config_field_pointer
#define _mulle_clioption_get_config_field_pointer( config, offset, type) \
   ((type *) &((char *) config)[ offset])


struct mulle_clioptionparser;
struct mulle_clioption;

typedef int   mulle_clioption_converter_t( struct mulle_clioption *,
                                           char *,
                                           struct mulle_clioptionparser *);


extern mulle_clioption_converter_t   _mulle_clioption_convert_to_float;   // like -f 18.48
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_double;  // like -f 18.48
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_long;    // like -n 2
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_integer; // like -n 2
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_int;     // like -n 2
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_yes;     // like --batch    -> 1 (integer!)
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_no;      // like --no-batch -> 0 (integer!)
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_string;  // --foo <s>
extern mulle_clioption_converter_t   _mulle_clioption_convert_to_FILE;    // --infile <s>


struct mulle_clioption
{
   const char                    *comment;
   const char                    *name;
   int                           has_arg;
   unsigned int                  config_offset;
   mulle_clioption_converter_t   *converter;
   const void                    *userinfo;
};


static inline void   mulle_clioption_init( struct mulle_clioption *o,
                                           const char *comment,
                                           const char *name,
                                           int has_arg,
                                           unsigned int config_offset,
                                           mulle_clioption_converter_t *converter,
                                           const void *userinfo)
{
   if( ! o)
      return;

   memset( o, 0, sizeof( *o));

   o->comment       = comment;
   o->name          = name;
   o->has_arg       = has_arg;
   o->config_offset = config_offset;
   o->converter     = converter;
   o->userinfo      = userinfo;
}


static inline int  _mulle_clioption_is_alias( struct mulle_clioption *o)
{
   return( o->has_arg == 2);
}


#define mulle_clioption_data( comment, name, has_arg, config_offset, converter, userinfo) \
   { (comment), (name), (has_arg), (config_offset), (converter), (userinfo) }

#define mulle_clioption_alias( name, alias) \
   { 0, (name), 2, 0, 0, (alias) }

#define mulle_clioption_yes_data( comment, name, config_offset) \
   { (comment), (name), 0, (config_offset), _mulle_clioption_convert_to_yes, 0 }

#define mulle_clioption_no_data( comment, name, config_offset) \
   { (comment), (name), 0, (config_offset), _mulle_clioption_convert_to_no, 0 }


#define mulle_clioption_string_argument_data( comment, name, config_offset) \
   { (comment), (name), 1, (config_offset), 0 }

#define mulle_clioption_integer_argument_data( comment, name, config_offset) \
   { (comment), (name), 1, (config_offset), _mulle_clioption_convert_to_integer, 0 }

#define mulle_clioption_long_argument_data( comment, name, config_offset) \
   { (comment), (name), 1, (config_offset), _mulle_clioption_convert_to_long, 0 }

#define mulle_clioption_double_argument_data( comment, name, config_offset) \
   { (comment), (name), 1, (config_offset), _mulle_clioption_convert_to_double, 0 }

#define mulle_clioption_float_argument_data( comment, name, config_offset) \
   { (comment), (name), 1, (config_offset), _mulle_clioption_convert_to_float, 0 }

#define mulle_clioption_FILE_argument_data( comment, name, config_offset, mode) \
   { (comment), (name), 1, (config_offset), _mulle_clioption_convert_to_FILE, mode }


//
// nothing will be strduped or freed, so everything is const
//
struct mulle_clioptionparser
{
   struct mulle_clioption   *options;
   void                     *config;
   const char               *usage_text;
   const char               *usage_footer;
   int                      (*usage)( char *format, va_list va);
   const char               *argv0;
};


static inline void   mulle_clioptionparser_init( struct mulle_clioptionparser *parser,
                                                 struct mulle_clioption *options,
                                                 void *config,
                                                 const void *usage_text)

{
   if( ! parser)
      return;

   memset( parser, 0, sizeof( *parser));

   parser->options    = options;
   parser->config     = config;
   parser->usage_text = usage_text;
}


//
// don't let mulle_clioptionparser_argc_argv, because it changes
// parser->usage_text from a string to a format, which is a hack
// the format can then ask 24 times for a "nice" basename of
// argv0
//
static inline void
   mulle_clioptionparser_set_argv0( struct mulle_clioptionparser *parser,
                                    const char *s)

{
   if( ! parser)
      return;

   parser->argv0 = s;
}


static inline void
   mulle_clioptionparser_set_usage_text( struct mulle_clioptionparser *parser,
                                         const char *s)

{
   if( ! parser)
      return;

   parser->usage_text = s;
}


//
// its assumed that argv, points to strings that need not be strduped into
// the config
//
int   mulle_clioptionparser_argc_argv( struct mulle_clioptionparser *p,
                                       int argc, const char *argv[]);

//
// in this function argc must main's argc - 1 and &argv[ 1], so
// you can easily pick up the parse
//
int  _mulle_clioptionparser_argc_argv( struct mulle_clioptionparser *p,
                                       int argc, const char *argv[]);


static inline void   mulle_clioptionparser_usage( struct mulle_clioptionparser *parser,
                                                  char *format,
                                                  ...)
{
   extern void   _mulle_clioptionparser_usagev( struct mulle_clioptionparser *parser,
                                                char *format,
                                                va_list va);
   va_list   va;

   if( ! parser)
      return;

   va_start( va, format);
   {
      _mulle_clioptionparser_usagev( parser, format, va);
   }
   va_end( va);
}

#endif
