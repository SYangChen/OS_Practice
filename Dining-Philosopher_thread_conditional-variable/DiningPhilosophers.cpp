#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>

#define N 5					// 5 philosopher
#define LEFT ( i+N-1 )%N	// left philosopher
#define RIGHT ( i+1 )%N		// right philosopher
#define THINKING 0			// Thinking state
#define HUNGRY 1			// Hungry state
#define EATING 2			// Eating state
#define TRUE 1				// True

using namespace std ;

class MonitorDP {

	private :
		
		int state[N] ;
		pthread_cond_t selfCond[N] ;
		pthread_mutex_t mutex ;
		
	public :
	
		void Init() ;
		void TakeForks( int i ) ;
		void PutForks( int i ) ;
		void Try( int i ) ;
		void PrintState() ;
		void Thinking() ;
		void Eating() ;
		
};

MonitorDP mDP ;

void *Philosopher( void *data ) {

	int i = ( intptr_t )data ;	// int i = *(int *) data ;
	while ( TRUE ) {
		mDP.Thinking() ;			// Thinking for a while
		mDP.TakeForks( i ) ;		// take two forks or block it
		mDP.Eating() ;			// Eating for a while
		mDP.PutForks( i ) ;			// put both forks back on table
	} // end while
    
} // Philosopher()

int main( int argc, char *argv[] ) {

	srand(time(NULL)) ;
	pthread_t thread[N] ;
	mDP.Init() ;
	cout << "-------------------------------------------------------" << endl ;
	cout << "|                 PHILOSOPHERS STATE                  |" << endl ;
	cout << "-------------------------------------------------------" << endl ;
	cout << "|  Phil_0  |  Phil_1  |  Phil_2  |  Phil_3  |  Phil_4  |" << endl ;
	for ( int i = 0 ; i < N ; ++i )
		pthread_create( &thread[i], NULL, Philosopher, (void*)(intptr_t)i ) ;
	while ( true  ) {
		mDP.PrintState() ;
		sleep(1) ;
	} // end while
	for ( int i = 0 ; i < N ; ++i )
		pthread_join( thread[i], NULL ) ;

	return 0;
    
} // main()

void MonitorDP::Init() {

	pthread_mutex_init( &mutex, NULL ) ;
	for ( int i = 0 ; i < N ; i++ ) {
		state[i] = THINKING ;
		pthread_cond_init( &selfCond[i], NULL ) ;
	} // end for

} // MonitorDP::Init()

void MonitorDP::TakeForks( int i ) {

	state[i] = HUNGRY ;
	sleep(1) ;						// Hungry > 1 second
	Try( i ) ;						// Try to acquired two forks
	pthread_mutex_lock( &mutex ) ;
	if ( state[i] != EATING )		// if unable to eat, wait to be signaled
		pthread_cond_wait( &selfCond[i], &mutex ) ;
	pthread_mutex_unlock( &mutex ) ;
		
} // MonitorDP::TakeForks()

void MonitorDP::PutForks( int i ) {

	state[i] = THINKING ;
	Try( LEFT );				// if left neighbor can eat now
	Try( RIGHT ) ;				// if right neighbor can eat now
	
	
} // MonitorDP::PutForks

void MonitorDP::Try( int i ) {

	if ( ( state[LEFT] != EATING ) && ( state[i] == HUNGRY ) &&\
		 ( state[RIGHT] != EATING ) ) {
		state[i] = EATING ;		// if both left, right neighbor is not eating
		pthread_cond_signal( &selfCond[i] ) ;
	} // end if
	
} // MonitorDP::Try()

void MonitorDP::PrintState() {

	cout << "| " ;
	for ( int i = 0 ; i < N ; i++ ) {
		switch ( state[i] ) {
			case 0 :
				cout << "THINKING | " ;
				break ;
			case 1 :
				cout << "*Hungry* | " ;
				break ;
			case 2 :
				cout << "EATING_" << i << " | " ;
				break ;
			default :
				cout << "UNKNOWN? | " ;
		} // end switch
	} // end for
	cout << endl ;
		

} // MonitorDP::PrintState()

void MonitorDP::Thinking() { 

	sleep( rand()%8+1 ) ;
	return;
	
} // MonitorDP::Thinking()

void MonitorDP::Eating() { 

	sleep( rand()%8+1 ) ;
	return;
	
} // MonitorDP::Eating

