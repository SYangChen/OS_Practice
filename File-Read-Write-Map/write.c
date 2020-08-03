#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 100

volatile sig_atomic_t end ;

void inthand( int signum ) {
	// signal handler with ctrl+c
	end = TRUE ;
}

int main( int argc , const char *argv[] ) {
	
	signal( SIGINT, inthand ) ;							// signal handler with ctrl+c
	
	if (argc < 2) {
		// file name argument
		printf( "***Error!!! Please input filename***\n" ) ;
	 	exit( EXIT_FAILURE ) ;	//exit
	}

	int fd = open( argv[1], O_RDWR | O_CREAT, 0666 ) ;	// write append or create
	if ( fd == -1 ) {
		printf( "open '%s' failure\n" ,argv[1] ) ;
		exit( EXIT_FAILURE ) ;	//exit
	}

	void* map = mmap( NULL, getpagesize(), PROT_WRITE, MAP_SHARED, fd, 0 ) ;
	// map a text file to memory
	if( map == MAP_FAILED ) {
		close(fd) ;
	    printf( "mmap failed\n" ) ;
		exit( EXIT_FAILURE ) ;	//exit
	}
	printf( "\n---Input file : %s ( limits to %d )---\n", argv[1], BUFFER_SIZE ) ;
	printf( "// enter \"ctrl+c\" to end\n" ) ;

	while( !end ) {
	    struct stat fileInfo = { 0 } ;		// run successful => 0
		if ( fstat( fd, &fileInfo ) == -1 ) {
			// "fstat" copy fd status to fileInfo
			printf( "get file stat failed\n" ) ;
			exit( EXIT_FAILURE ) ;
		}
	    int current_size = ( int )fileInfo.st_size ;
	    char add[BUFFER_SIZE] ;				// word adding
	    fgets( add, sizeof(add), stdin ) ;	// input word
		
		int add_size ;
	    add_size = strlen(add);
		lseek( fd, current_size+add_size, SEEK_SET ) ;
		// current file offset 
		write( fd,"", 1 ) ;
		// lseek( fd, 0, SEEK_SET ) ;
		sprintf( map+current_size, "%s", add ) ;
		
	}

	if( munmap( map, getpagesize() ) == -1 ) {
		//release memory
	    close( fd ) ;
	    printf( "munmap failed\n" ) ;
	    exit( EXIT_FAILURE ) ;	//exit
	}

	close( fd ) ;
	printf( "\n----------------finished----------------\n" ) ;
	return 0  ;
}
