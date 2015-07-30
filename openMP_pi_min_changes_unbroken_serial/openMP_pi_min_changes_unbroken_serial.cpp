/**
    openMP_pi_min_changes_unbroken_serial.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 4 Pi with loops. Use minimum changes in the classic serial 
	pi program without breaking the serial version for compilers that do not support 
	openMP if compiler does not support openMP it skips all directives #pragma omp
	
	threads 	1st SPMD 	1st SPMD padded 	SPMD critical	PI Loop
	1 			1.86 		1.86 				1.87			1.91
	2 			1.03 		1.01 				1.00			1.02
	3 			1.08 		0.69 				0.68			0.80
	4 			0.97 		0.53 				0.53			0.68
	
    @author George Papageorgakis
    @version 1.0 10/2014
*/
#include "stdafx.h"

int OMP_NUM_THREADS = omp_get_max_threads();
//int OMP_NUM_THREADS = 4;
static long num_steps = 100000000;
double step;

int _tmain(int argc, _TCHAR* argv[]){
	// Shared variables, updated !
	int i;
	double x, pi = 0.0, sum = 0.0, start, stop; 
	step = 1.0/(double) num_steps;

	printf("Pi with minimum changes and able to run as serial\n\n");
	printf("Calculating with request of %d number of threads\n", OMP_NUM_THREADS);
	omp_set_num_threads(OMP_NUM_THREADS);

	start = omp_get_wtime();
	//reduction is more scalable than critical
	#pragma omp parallel for schedule(dynamic) private(x) reduction(+ : sum)
	{	
		for (i = 0; i < num_steps; ++i){ 
			x = (i + 0.5) * step; 
			sum += 4.0 / (1.0 + x*x); 
		}	
	}
	pi = sum * step;
	stop = omp_get_wtime();

    printf("pi = %.16f\n", pi);
	printf("running time = %f\n", stop - start);	
	printf("Active number of threads allocated by OS: %d threads \n", OMP_NUM_THREADS);
	getchar();
    return 0;
}