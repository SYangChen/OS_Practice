#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#define TRUE 1
#define FALSE 0

volatile sig_atomic_t end ;

void inthand( int signum ) {
	// signal handler with ctrl+c
	end = TRUE ;
}

int main( int argc, const char *argv[] ) {

	signal( SIGINT, inthand ) ;				// signal handler with ctrl+c
	int i ;
	if ( argc < 2 ) {
		// file name argument
		printf( "***Error!!! Please input filename***\n" ) ;
		exit( EXIT_FAILURE ) ;
	}

	int fd = open( argv[1], O_RDONLY ) ;	// read only open file
	while ( !end ) {
		if ( fd == -1 ) {
			printf( "open '%s' failure\n" ,argv[1] ) ;
			exit( EXIT_FAILURE ) ;
		}
		struct stat fileInfo = { 0 } ;		// run successful => 0
		if ( fstat( fd, &fileInfo ) == -1 ) {
			// "fstat" copy fd status to fileInfo
			printf( "get file stat failed\n" ) ;
			exit( EXIT_FAILURE ) ;
		}
		if ( fileInfo.st_size == 0 ) {
			printf( "file is empty\n" ) ;
			exit( EXIT_FAILURE ) ;
		}
		char *map = ( char* )mmap( NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, 0 ) ;
		// map a text file to memory
		if ( map == MAP_FAILED ) {
			close( fd ) ;
			printf( "mmap failed\n" ) ;
			exit( EXIT_FAILURE ) ;
		}
		printf( "---BEGIN--- file:'%s' ---BEGIN---\n", argv[1] ) ;
		for ( i=0 ; i < fileInfo.st_size ; i++ )
			printf( "%c", map[i] ) ;
		printf( "----END---- file:'%s' ----END----\n", argv[1] ) ;
		if ( munmap( map, fileInfo.st_size ) == -1 ) {
			// memory release
			close( fd ) ;
			printf( "munmap failed\n" ) ;
			exit( EXIT_FAILURE ) ;
		}
		sleep(2) ;
	}
	close( fd ) ;
	printf( "\n-------------program exit-------------\n" ) ;
	return 0 ;
}
