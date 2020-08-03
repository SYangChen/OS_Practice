#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define N 5					// 5 philosopher
#define LEFT ( i+N-1 )%N	// left philosopher
#define RIGHT ( i+1 )%N		// right philosopher
#define THINKING 0			// Thinking state
#define HUNGRY 1			// Hungry state
#define EATING 2			// Eating state
#define TRUE 1				// True

sem_t s[N] ;				// one semaphore per philosopher
sem_t mutex ;				// mutual exclusion for critical regions
int state[N] ;				// array to keep track of everyone's state

void *Philosopher( void *data ) ;
void TakeForks( int i ) ;
void PutForks( int i ) ;
void Try( int i ) ;
void Thinking( int i ) ;
void Eating( int i ) ;
void PrintCurrentState() ;

void *Philosopher( void *data ) {

	int i = ( intptr_t )data ;	// int i = *(int *) data ;
	while ( TRUE ) {
		Thinking( i ) ;			// Thinking for a while
		TakeForks( i ) ;		// take two forks or block it
		Eating( i ) ;			// Eating for a while
		PutForks( i ) ;			// put both forks back on table
	} // end while
    
} // Philosopher()

void TakeForks( int i ) {

	sem_wait( &mutex ) ;		// wait for the process, if 1 to go, 0 block
	// critical region start
	state[i] = HUNGRY ;
	printf( "philosopher %d is HUNGRY\t", i+1 ) ;
	PrintCurrentState() ;
	Try( i ) ;					// Try to acquired two forks
	// critical region end
	sem_post( &mutex ) ;		// exit critical region, turn to idle
	sem_wait( &s[i] ) ;			// block if forks were not acquired
    
} // TakeForks()

void PutForks( int i ) {

	sem_wait( &mutex ) ;		// wait for the process, if 1 to go, 0 block
	// critical region start
	state[i] = THINKING ;
	printf( "philosopher %d is THINKING", i+1 ) ;
	PrintCurrentState() ;
	Try( LEFT );				// if left neighbor can eat now
	Try( RIGHT ) ;				// if right neighbor can eat now
	// critical region end
	sem_post( &mutex ) ;		// exit critical region, turn to idle
	
} // PutForks

void Try( int i ) {

	if ( ( state[i] == HUNGRY ) && ( state[LEFT] != EATING ) && 
		 ( state[RIGHT] != EATING ) ) {
		state[i] = EATING ;		// if both left, right neighbor is not eating
		printf( "philosopher %d is EATING\t", i+1 ) ;
		PrintCurrentState() ;
		sem_post( &s[i] ) ;		// turn to idle
	} // end if
	
} // Try()

void Thinking( int i ) { 

	sleep( rand()%10+1 ) ;
	return;
	
} // Thinking()

void Eating( int i ) { 

	sleep( rand()%10+1 );
	return;
	
} // Eating

void PrintCurrentState() {
	
	for( int i = 0 ; i < N ; i++ ) {
		if( state[i] == 0 )
			printf( "\tT" ) ;
		else if( state[i] == 1 )
			printf( "\tH" ) ;
		else if( state[i] == 2 )
			printf( "\tE" ) ;
	} // end for
	printf( "\n" ) ;
	
} // PrintCurrentState()

int main( int argc, char *argv[] ) {

	srand(time(NULL)) ;
	int i ;
	pthread_t thread[N] ;
	
	for ( i = 0 ; i < N ; i++ )
		sem_init( &s[i], 0, 1 ) ;
	sem_init( &mutex, 0, 1 ) ;
	
	printf( "Philosopher problem simulate :\tP1\tP2\tP3\tP4\tP5\n" ) ;
	for ( int i = 0 ; i < N ; ++i )
		pthread_create( &thread[i], NULL, Philosopher, (void*)(intptr_t)i ) ;
	for ( int i = 0 ; i < N ; ++i )
		pthread_join( thread[i], NULL ) ;

	return 0;
    
} // main()
