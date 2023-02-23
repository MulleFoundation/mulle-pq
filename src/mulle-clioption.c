#include "mulle-clioption.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>


static void   _mulle_clioption_usage( struct mulle_clioption *o, int max)
{
   int  len;

   len = strlen( o->name);
   if( len > max)
      max = len; // paranoia
   if( o->has_arg)
      fprintf( stderr, "   %s <value>%*s : %s\n", o->name,
                                                 (max - len), "",
                                                 o->comment ? o->comment : "???");
   else
      fprintf( stderr, "   %-*s         : %s\n", max,
                                                 o->name,
                                                 o->comment ? o->comment : "???");
}


int   _mulle_clioption_convert_to_double( struct mulle_clioption *o,
                                          char *s,
                                          struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               double) = strtod( s, NULL);
   return( 0);
}


int   _mulle_clioption_convert_to_float( struct mulle_clioption *o,
                                         char *s,
                                         struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               float) = strtod( s, NULL);
   return( 0);
}


int   _mulle_clioption_convert_to_long_long( struct mulle_clioption *o,
                                             char *s,
                                             struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               long long) = strtoll( s, NULL, 0);
   return( 0);
}


int   _mulle_clioption_convert_to_long( struct mulle_clioption *o,
                                        char *s,
                                        struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               long) = strtol( s, NULL, 0);
   return( 0);
}



int   _mulle_clioption_convert_to_integer( struct mulle_clioption *o,
                                           char *s,
                                           struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               intptr_t) = (intptr_t)
                                                           strtol( s, NULL, 0);
   return( 0);
}



int   _mulle_clioption_convert_to_int( struct mulle_clioption *o,
                                       char *s,
                                       struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               int) = (int) strtol( s, NULL, 0);
   return( 0);
}


int   _mulle_clioption_convert_to_no( struct mulle_clioption *o,
                                      char *s,
                                      struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               int) = 0;
   return( 0);
}


int   _mulle_clioption_convert_to_yes( struct mulle_clioption *o,
                                       char *s,
                                       struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               int) = 1;
   return( 0);
}


int   _mulle_clioption_convert_to_string( struct mulle_clioption *o,
                                          char *s,
                                          struct mulle_clioptionparser *p)
{
   *_mulle_clioption_get_config_field_pointer( p->config,
                                               o->config_offset,
                                               const char *) = s;
   return( 0);
}


int   _mulle_clioption_convert_to_FILE( struct mulle_clioption *o,
                                        char *s,
                                        struct mulle_clioptionparser *p)
{
   FILE  *fp;


   fp = fopen( s, o->userinfo);
   if( ! fp)
      return( -1);

   *_mulle_clioption_get_config_field_pointer( p->config, o->config_offset, FILE *) = fp;
   return( 0);
}


static int   mulle_compare_clioption( const void *_a, const void *_b)
{
   struct mulle_clioption  *a = (struct mulle_clioption *) _a;
   struct mulle_clioption  *b = (struct mulle_clioption *) _b;

   return( strcmp( a->name, b->name));
}


void   _mulle_clioptionparser_usagev( struct mulle_clioptionparser *parser,
                                      char *format,
                                      va_list va)
{
   int                      len;
   int                      max;
   int                      rval;
   struct mulle_clioption   *o;
   const char               *s;
   char                     **sorted;
   int                      n;

   if( parser->usage)
   {
      rval = parser->usage( format, va);
      if( ! rval)
         return;  // just return here
   }

   if( format)
   {
      fprintf( stderr, "Error: ");
      vfprintf( stderr, format, va);
      fprintf( stderr, "\n");
   }

   max = 0;
   if( parser->usage_text)
   {
      if( parser->argv0)
      {
         s = strrchr( parser->argv0, '/');
         s = s ? s + 1 : parser->argv0;

         // ugliness, can use basename up to 24 times in usage_text
         fprintf( stderr, parser->usage_text,
                        s, s, s, s, s, s, s, s,
                        s, s, s, s, s, s, s, s,
                        s, s, s, s, s, s, s, s);
      }
      else
         fprintf( stderr, "%s\n", parser->usage_text);
   }

   for( n = 0, o = parser->options; o->name; o++, n++)
   {
      if( ! _mulle_clioption_is_alias( o))
      {
         len = (int) strlen( o->name);
         if( len > max)
            max = len;
      }
   }

   if( max)
   {
      qsort( parser->options,
             n,
             sizeof( struct mulle_clioption),
             mulle_compare_clioption);

      for( o = parser->options; o->name; o++)
      {
         if( ! _mulle_clioption_is_alias( o))
            _mulle_clioption_usage( o, max);
      }
      fprintf( stderr, "\n");
   }

   if( parser->usage_footer)
      fprintf( stderr, "%s\n", parser->usage_footer);

   exit( 1);
}


void   _mulle_clioptionparser_usage( struct mulle_clioptionparser *parser,
                                     char *format,
                                     ...)
{
   va_list   va;

   va_start( va, format);
   {
      _mulle_clioptionparser_usagev( parser, format, va);
   }
   va_end( va);
}


int   _mulle_clioptionparser_argc_argv( struct mulle_clioptionparser *p,
                                        int argc, const char *argv[])
{
   int                     i;
   struct mulle_clioption  *o;
   const char              *name;

   for( i = 0; i < argc; i++)
   {
      if( ! strcmp( argv[ i], "-h") ||
          ! strcmp( argv[ i], "--help") ||
          ! strcmp( argv[ i], "help"))
      {
         _mulle_clioptionparser_usage( p, NULL);
         return( 0);
      }

      for( o = p->options; o->name; o++)
      {
         if( strcmp( argv[ i], o->name))
            continue;

retry:
         switch( o->has_arg)
         {
         case 0 :
            break;

         case 1 :
            if( ++i >= argc)
            {
               _mulle_clioptionparser_usage( p,
                                             "missing argument for \"%s\"",
                                             argv[ --i]);
               return( 0);
            }
            break;

         case 2:
            name = o->userinfo;
            if( ! name)
            {
               errno = EINVAL;
               return( -1);
            }

            for( o = p->options; o->name; o++)
            {
               if( ! strcmp( o->name, name))
                  break;
            }

            if( ! o->name)
            {
               errno = ENOENT;
               return( -1);
            }
            goto retry;
         }

         if( o->converter)
         {
            if( (*o->converter)( o, (char *) argv[ i], p))
            {
               _mulle_clioptionparser_usage( p,
                                             "wrong kind of argument for \"%s\"",
                                             argv[ --i]);
               return( 0);
            }
         }
         else
         {
            *_mulle_clioption_get_config_field_pointer( p->config,
                                                        o->config_offset,
                                                        const char *) = argv[ i];
         }

         break;
      }

      // reached end
      if( ! o->name)
         break;
   }
   return( i);
}


int   mulle_clioptionparser_argc_argv( struct mulle_clioptionparser *p,
                                       int argc, const char *argv[])
{
   int   rval;

   if( ! argc)
      return( 0);
   if( ! p)
      return( -1);
   if( ! argv)
      return( -1);

   rval =_mulle_clioptionparser_argc_argv( p, argc - 1, &argv[ 1]);
   return( rval <= 0 ? rval : rval + 1); // adjust argc
}