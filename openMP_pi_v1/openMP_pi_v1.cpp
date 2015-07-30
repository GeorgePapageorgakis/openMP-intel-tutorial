/**
    openMP_pi_v1.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 2 Create a parallel version of the pi program using 
	a parallel construct. Pay close attention to shared versus private variables.
	This program has false sharing and we could Pad sum array to eliminate it.
	threads 1st SPMD
	1 		1.86
	2 		1.03
	3 		1.08
	4 		0.97
	
    @author George Papageorgakis
    @version 1.0 10/2014
*/
#include "stdafx.h"

//int NUM_THREADS 		= omp_get_max_threads();
int NUM_THREADS 		= 4;
static long num_steps 	= 100000;
double step;

int _tmain(int argc, _TCHAR* argv[]){
	// Shared variable, updated !
	int i;
	double pi, start, stop; 
	// Promote scalar to an array dimensioned by
	// number of threads to avoid race condition.
	double* sum = (double*) malloc(sizeof(double) * NUM_THREADS);
	step = 1.0/(double) num_steps;
	
	printf("SPMD with no synchronization \n\n");
	printf("Calculating with request of %d number of threads\n", NUM_THREADS);
	
	omp_set_num_threads(NUM_THREADS);
	start = omp_get_wtime();
	#pragma omp parallel 
	{	
		int i, id, os_threads; 
		double x;	
		id 			= omp_get_thread_num();
		os_threads 	= omp_get_num_threads();
		
		//Only one thread should copy the number of threads to the global value 
		//to make sure multiple threads writing to the same address don’t conflict.
		if (id == 0)
			NUM_THREADS = os_threads;
		
		//This is a common trick in SPMD programs to create 
		//a cyclic distribution of loop iterations
		for (i = id, sum[id]=0.0; i < num_steps; i = i + NUM_THREADS){ 
			x = (i + 0.5) * step; 
			sum[id] += 4.0 / (1.0 + x*x); 
		} 
	}
	for(i = 0, pi = 0.0; i < NUM_THREADS; i++){
		pi += sum[i] * step; 
	}
	stop = omp_get_wtime();

    printf("pi = %f\n", pi);
	printf("running time = %f\n", stop - start);
	printf("Actual active number of threads allocated by OS: %d threads \n", NUM_THREADS);
	getchar();
    return 0;
}
