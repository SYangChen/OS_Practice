#include "mm.h"


int main()
{

		int r = 0, c = 0;
		printf("Please enter row and column\n");
		scanf("%d%d", &r, &c);
		
		Header he;
		printf("sizeof header is: %lu\n", sizeof(he));

		testMalloc(r, c);
		testRealloc(r, c);
		testCalloc(r, c);

		return 0;
}


void printArray(int **array, int r, int c)
{
		int i, j; // flow control
		for(i=0;i<r;i++){

				for(j=0;j<c;j++){

						printf("%d\t", array[i][j]);
				}
				printf("\n");
		}
}

void testMalloc(int r, int c)
{

		printf("the test function of my malloc()\n");
		printf("--------------------------------\n");


		/* test the memory is allocated correct or not */
		int **array = (int**)mymalloc(sizeof(int*) * r);
		int i, j; // flow control
		for(i=0;i<r;i++){
				array[i] = (int*)mymalloc(sizeof(int) * c);
		}

		for(i=0;i<r;i++){
				/* give the value */	
				for(j=0;j<c;j++){
						array[i][j] = i*c + j;
				}
		}

		printArray(array, r, c);
		// traceMemory();

		/* end of test */


		/* start to test free */
		for(i=0;i<r;i++){

				myfree(array[i]);
		}
		myfree(array);

		printf("\n\nAfter my free()\n");
		printf("-------------------------------\n");
		// traceMemory();
}

void testRealloc(int r, int c)
{

		/* initialize the array */
		int **array = (int**)mymalloc(sizeof(int*) * r);
		int i, j; // flow control

		for(i=0;i<r;i++){
				array[i] = (int*)mymalloc(sizeof(int) * c);
		}

		for(i=0;i<r;i++){
				/* give the value */	
				for(j=0;j<c;j++){
						array[i][j] = i*r + j;
				}
		}
		printf("Before my realloc(), the status of the array\n");
		printf("-------------------------------\n");
		printArray(array, r, c);
		// traceMemory();

		printf("\n\nNow, we reallocate the array, row+5, column+5\n");
		printf("-------------------------------\n");


		array = (int**)myrealloc(array, sizeof(int*) * (r+5));
		for(i=0;i<r;i++){

		  array[i] = (int*)myrealloc(array[i], sizeof(int) * (c+5));
		  }
		  for(i=r;i<r+5;i++){

		  array[i] = (int*)mymalloc(sizeof(int) * (c+5));
		}


		for(i=0;i<r+5;i++){

				array[i] = (int*)myrealloc(array[i], (sizeof(int) * (c+5)));
		}

		for(i=0;i<r+5;i++){
				/* give the value */	
				for(j=0;j<c+5;j++){
						if(i<r && j<c)
								/* do nothing*/
								;
						else
								array[i][j] = 0;

				}

		}

		printArray(array, r+5, c+5);
		// traceMemory();


		/* free */
		for(i=0;i<r+5;i++){
				myfree(array[i]);
		}
		myfree(array);

		printf("\n\nAfter my free()\n");
		printf("-----------------------------\n");

		// traceMemory();
}

void testCalloc(int r, int c)
{
		printf("Here is the test of my calloc(), now, I will allocate");
		printf(" a two dimensional array using my calloc()\n");
		printf("-----------------------------\n");	
		
		int i, j; // flow control
		int **array = mycalloc(r, sizeof(int*));
		for(i=0;i<r;i++)
			array[i] = mycalloc(c, sizeof(int));


		for(i=0;i<r;i++){
				/* give the value */	
				for(j=0;j<c;j++){
						array[i][j] = i*r + j;
				}
		}
		printArray(array, r, c);
		// traceMemory();
		
		
		for(i=0;i<r;i++){
				myfree(array[i]);
		}
		myfree(array);

		printf("\n\nAfter my free()\n");
		printf("-----------------------------\n");

		// traceMemory();

}
