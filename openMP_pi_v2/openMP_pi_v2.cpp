/**
    openMP_pi_v2.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 3. In exercise 2, you probably used an array to create 
	space for each thread to store its partial sum. If array elements happen 
	to share a cache line, this leads to false sharing. 
		Non-shared data in the same cache line so each update invalidates the 
		cache line... in essence “sloshing independent data” back and forth 
		between threads.
	Modify your “pi” from exercise 2 to avoid false sharing due to the sum array.
	
	threads 	1st SPMD 	1st SPMD padded 	SPMD critical
	1 			1.86 		1.86 				1.87
	2 			1.03 		1.01 				1.00
	3 			1.08 		0.69 				0.68
	4 			0.97 		0.53 				0.53
	
    @author George Papageorgakis
    @version 1.0 10/2014
*/
#include "stdafx.h"

//int NUM_THREADS 		= omp_get_max_threads();
int NUM_THREADS 		= 4;
static long num_steps 	= 100000;
double step;

int _tmain(int argc, _TCHAR* argv[]){
	// Shared variables, updated !
	int i;
	double pi = 0.0, start, stop; 
	step = 1.0/(double) num_steps;

	printf("SPMD with mutual exclusion (critical section) \n\n");
	printf("Calculating with request of %d number of threads\n", NUM_THREADS);
	
	omp_set_num_threads(NUM_THREADS);
	start = omp_get_wtime();

	#pragma omp parallel 
	{	
		int i, id, os_threads; 
		//Create a scalar local to each thread to accumulate partial sums.
		double x, sum;
		
		id = omp_get_thread_num();
		os_threads = omp_get_num_threads();	
		//Only one thread should copy the number of threads to the global value 
		//to make sure multiple threads writing to the same address don’t conflict.
		if (id == 0)
			NUM_THREADS = os_threads;

		for (i = id, sum=0.0; i < num_steps; i = i + NUM_THREADS){ 
			x = (i + 0.5) * step; 
			//No array, so no false sharing.
			sum += 4.0 / (1.0 + x*x); 
		} 
		//use mutual exclusion instead of pad(bad solution with 2d array for cache line)
		//Must protect summation into pi in a critical region so updates don’t conflict
		#pragma omp critical
			pi += sum * step;	
		/*
		//With atomic to remove impact of false sharing
		sum = sum * step;
		#pragma omp atomic
			pi += sum;
		*/
	}
	stop = omp_get_wtime();

    printf("pi = %f\n", pi);
	printf("running time = %f\n", stop - start);
	printf("Actual active number of threads allocated by OS: %d threads \n", NUM_THREADS);
	getchar();
    return 0;
}
