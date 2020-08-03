#ifndef __MY_MM_H_INCLUDED__ 
#define __MY_MM_H_INCLUDED__ 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NALLOC 1024			/*minimum of #unit */

typedef long Align ;		// alignment boundary

typedef union header{		// block header :

	struct{
	
		union header *next ;// next block if on free list
		unsigned size ;		// size of this block
		
	} s ;
	
	Align x ;				// force alignment of blocks
							// align never used
} Header ;

static Header base ; 			// empty list to get started
static Header *freeptr = NULL ;	// start of free list

Header *morecore( unsigned nu ) ;
void *mymalloc( size_t size ) ;
void myfree( void *aptr ) ;
void *myrealloc( void *ptr, size_t size ) ;
void *mycalloc( size_t nmemb, size_t size ) ;

#endif
