#ifndef mulle_plist_convert_version_h__
#define mulle_plist_convert_version_h__

/*
 *  You can maintain this file with `mulle-project-version`
 *  version:  major, minor, patch
 */
#define MULLE_PLIST_CONVERT_VERSION  ((0 << 20) | (7 << 8) | 56)


static inline unsigned int   mulle_plist_convert_get_version_major( void)
{
   return( MULLE_PLIST_CONVERT_VERSION >> 20);
}


static inline unsigned int   mulle_plist_convert_get_version_minor( void)
{
   return( (MULLE_PLIST_CONVERT_VERSION >> 8) & 0xFFF);
}


static inline unsigned int   mulle_plist_convert_get_version_patch( void)
{
   return( MULLE_PLIST_CONVERT_VERSION & 0xFF);
}

#endif
