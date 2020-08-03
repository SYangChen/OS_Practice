#include "mm.h"

Header *morecore( unsigned nu ){

	char *cp, *sbrk( int ) ;			//used for sbrk
	Header *up ;

	if( nu < NALLOC )
		nu = NALLOC ;					// to minimun #units
	cp = sbrk( nu*sizeof( Header ) ) ;	
	// increment the heap by nu*headersize
	// return the last( before increment ) heap program break address
	if( cp == ( char* )-1 )				/* no space at all*/
		return NULL ;
	up = ( Header* )cp ;
	up->s.size = nu ;					// size of this block
	myfree( ( void * )( up+1 ) ) ;		//add the space to the freelist
	return freeptr ;
    
} // morecore()

void *mymalloc( size_t size ){
	// general purpose storage allocator
	Header *walkptr, *prevptr ;
	Header *morecore( unsigned ) ;
	unsigned unit ;
	unit = ( size + sizeof( Header )-1 ) / sizeof( Header )+1 ;
	// caculate how many (header) size it needs ( align the header size ) + header
	if ( ( prevptr = freeptr ) == NULL ){		/* no free list yet */
		base.s.next = freeptr = prevptr = &base;// initialization
		base.s.size = 0;
	} // end if

	for ( walkptr = prevptr->s.next ; ; prevptr = walkptr, walkptr = walkptr->s.next ){
		if( walkptr->s.size >= unit ){	//enough
			if( walkptr->s.size == unit ){
				prevptr->s.next = walkptr->s.next ;
			} // end if
			else{						//too big
				walkptr->s.size -= unit ;
				walkptr += walkptr->s.size ;
				walkptr->s.size = unit ;
			} // end else
			freeptr = prevptr ;
			return ( void* )( walkptr+1 ) ;
		} // end if
		if ( walkptr == freeptr )			/* wrapped around free list */
			if ( ( walkptr = morecore( unit ) ) == NULL )
				return NULL ;			/* none left */
	} // end for
	
} // mymalloc()

void myfree( void *aptr ){
	// put block ap in free list
	Header *bptr, *walkptr ;
	
	bptr = ( Header* )aptr-1 ;				/* point to block header */
	for ( walkptr = freeptr ; !( bptr > walkptr && bptr < walkptr->s.next ) ;\
		  walkptr = walkptr->s.next )
		if ( walkptr >= walkptr->s.next && ( bptr > walkptr || bptr < walkptr->s.next ) )
			break ;							/* freed block at start or end of arena */
	/* join to upper nbr */
	if ( bptr+bptr->s.size == walkptr->s.next ){
		bptr->s.size += walkptr->s.next->s.size ;
		bptr->s.next = walkptr->s.next->s.next ;
	} // end if
	else
		bptr->s.next = walkptr->s.next ;
	/* join to upper nbr */
	/* join to lower nbr */
	if ( walkptr+walkptr->s.size == bptr ){
		walkptr->s.size += bptr->s.size ;
		walkptr->s.next = bptr->s.next ;
	} // end if
	else
		walkptr->s.next = bptr ;
	/* join to lower nbr */
	freeptr = walkptr ;
	
} // myfree() ;

void *myrealloc( void *ptr, size_t size ){

	Header *temp ;
	size_t unit ;
	// just new size same as malloc
	// if there have enough size to append
	if( ptr == NULL )
		return mymalloc( size ) ;
	temp = ( Header* )ptr-1 ;
    unit = ( size+sizeof(Header)-1) / sizeof(Header)+1;
    if( temp->s.size >= unit )
        return ptr ;
	// seek the bigger malloc size
	void *newptr = mymalloc( size ) ;
	if( newptr == NULL ){
		printf("the memory is not enough\n") ;
		return NULL ;
	} // end if
	memcpy( newptr, ptr, ( temp->s.size-1 )*sizeof( Header ) ) ;
	myfree( ptr ) ;
	return newptr ;
	
} // myrealloc()

void *mycalloc( size_t nmemb, size_t size ){
	// allocate n objects of size size 
	// with the storage intialized to zero
	size_t i, nbyte ;
	char *p, *q ;
	nbyte = nmemb*size ;
	if ( ( p = q = mymalloc( nbyte ) ) != NULL )
		for ( i = 0 ; i < nbyte ; i++ )
			*p++ = 0 ;
	return q ;
	
} // mycalloc
