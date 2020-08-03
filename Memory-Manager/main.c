#include "mm.h"


int main(){
	
	
	int size = 0 ;
	
	printf( "Input arr size : " ) ;
	scanf( "%d", &size ) ;
	// size = 100000 ;
	int *arr1 = mymalloc( size*sizeof( int ) ) ;
	
	printf( "Input value : \n" ) ;
	for ( int i = 0 ; i < size ; i ++ ) {
		printf( "arr1[%d] = ", i ) ;
		// *(arr1+i) = 2 ;
		scanf( "%d", arr1+i ) ;
	} // end for 
	
	printf( "show value ( malloc ) :\n" ) ;
	for ( int i = 0 ; i < size ; i++ ) 
		printf( "arr1[%d] = %d\n", i, *(arr1+i)) ;
	
	int *arr2 = myrealloc( arr1, sizeof( int )*size*2 ) ;
	printf( "show value ( realloc ) :\n" ) ;
	for ( int i = 0 ; i < size*2 ; i++ ) 
		printf( "arr2[%d] = %d\n", i, *(arr2+i)) ;
	
	printf( "arr1 address : %p\n", arr1 ) ;
	printf( "arr2 address : %p\n", arr2 ) ;
	
	myfree( arr2 ) ;
	
	int *arr3 = mycalloc( size, sizeof( int ) ) ;
	printf( "show value ( calloc ) :\n" ) ;
	for ( int i = 0 ; i < size ; i++ ) 
		printf( "arr3[%d] = %d\n", i, *(arr3+i)) ;
	return 0 ;
	/*
	int **arr = ( int** )mymalloc( 200*sizeof( int* ) ) ;
	for ( int i = 0 ; i < 200 ; i++ ) 
		arr[i] = ( int* )mymalloc( sizeof( int ) ) ;
	arr = myrealloc( arr, 210*sizeof( int* ) ) ;
	for ( int i = 0 ; i < 210 ; i++ )
		arr[i] = ( int* )myrealloc( arr[i], 210*sizeof( int ) ) ;
	for ( int i = 0 ; i < 210 ; i++ ) {
		for( int j = 0 ; j < 210 ; j++ ) {
			printf( "%d", arr[i][j] ) ;
		}
	}
	*/
}

