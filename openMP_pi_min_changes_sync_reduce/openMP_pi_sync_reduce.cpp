/**
    openMP_pi_sync_reduce.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 4 Pi with loops. Go back to the serial pi program and parallelize
	it with a loop construct. The goal is to minimize the number of changes made to 
	the serial program.
	
	threads 	1st SPMD 	1st SPMD padded 	SPMD critical	PI Loop
	1 			1.86 		1.86 				1.87			1.91
	2 			1.03 		1.01 				1.00			1.02
	3 			1.08 		0.69 				0.68			0.80
	4 			0.97 		0.53 				0.53			0.68
	
    @author George Papageorgakis
    @version 1.0 10/2014
*/

#include "stdafx.h"

// Exercise 4 calculation of pi with thread sync and reduce

int NUM_THREADS = omp_get_max_threads();
//int NUM_THREADS = 4;
static long num_steps = 100000000;
double step;

int _tmain(int argc, _TCHAR* argv[])
{
	// Shared variables, updated !
	int i;
	double pi = 0.0, sum=0.0, start, stop; 
	step = 1.0/(double) num_steps;

	printf("SPMD with parallel for loop\n\n");
	printf("Calculating with request of %d number of threads\n", NUM_THREADS);
	
	omp_set_num_threads(NUM_THREADS);
	start = omp_get_wtime();

	#pragma omp parallel 
	{	
		int i, id, os_threads;
		// Create a scalar local to each thread to hold value x at the centre of each interval
		double x;
		
		id = omp_get_thread_num();
		os_threads = omp_get_num_threads();
		
		if (id == 0)
			NUM_THREADS = os_threads;
		//omp_set_schedule(static);
		//Break up loop iterations and assign them to threads. Setting up a reduction into sum.
		//Note the loop index is local to a thread by default.
		#pragma omp for schedule(runtime) reduction(+ : sum)
		for (i = 0; i < num_steps; ++i){ 
			x = (i + 0.5) * step; 
			sum += 4.0 / (1.0 + x*x); 
		}	
	}
	pi = sum * step;
	stop = omp_get_wtime();

    printf("pi = %.16f\n", pi);
	printf("running time = %f\n", stop - start);
	printf("Active number of threads allocated by OS: %d threads \n", NUM_THREADS);

	getchar();
    return 0;
}