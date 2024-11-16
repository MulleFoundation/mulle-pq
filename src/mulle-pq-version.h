#ifndef mulle_pq_version_h__
#define mulle_pq_version_h__

/*
 *  You can maintain this file with `mulle-project-version`
 *  version:  major, minor, patch
 */
#define MULLE__PQ_VERSION  ((0UL << 20) | (0 << 8) | 3)


static inline unsigned int   mulle_pq_get_version_major( void)
{
   return( MULLE__PQ_VERSION >> 20);
}


static inline unsigned int   mulle_pq_get_version_minor( void)
{
   return( (MULLE__PQ_VERSION >> 8) & 0xFFF);
}


static inline unsigned int   mulle_pq_get_version_patch( void)
{
   return( MULLE__PQ_VERSION & 0xFF);
}

#endif
