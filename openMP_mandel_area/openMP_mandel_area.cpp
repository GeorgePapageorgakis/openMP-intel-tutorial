/**
    openMP_mandel_area.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 5 Mandelbrot set area. The supplied program computes the
	area of a Mandelbrot set. The program has been parallelized with OpenMP, 
	but we were lazy and didn’t do it right.
	Find and fix the errors (the problem is in the data environment).
	Once you have a working version, try to optimize the program.
		Try different schedules on the parallel loop.
		Try different mechanisms to support mutual exclusion.

    @author George Papageorgakis
    @version 1.0 10/2014
*/
#include "stdafx.h"

struct d_complex c;
int numoutside 		= 0;
int OMP_NUM_THREADS = omp_get_max_threads();
//int OMP_NUM_THREADS = 4;

int _tmain(int argc, _TCHAR* argv[]){
	int i, j;
	double area, error, eps = 1.0e-5, start, stop;
	
	omp_set_num_threads(OMP_NUM_THREADS);
	start = omp_get_wtime();
	/*
	change shared to none(for debug) private(for release) and now I mean that 
	loop index j is not made private
	
	Remember that the loop control index that is parallelized will be made
	automatically private. But the same does not apply for the nested second 
	index j and so we have to declare it as private else it will be shared...
	*/
	#pragma omp parallel for default(none) private(c,j) firstprivate(eps)
	for (i=0; i<NPOINTS; ++i) {
		for (j=0; j<NPOINTS; ++j) {
			c.r = -2.0 + 2.5 * 	(double)(i) / (double)(NPOINTS) + eps;
			c.i = 1.125 * 		(double)(j) / (double)(NPOINTS) + eps;
			//this function would have race condition(no parameters-void) 
			//since all threads access global filescope c
			//so we have to pass the local (thread) variable
			testpoint(c);
		}
	}
	area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
	error = area / (double)NPOINTS;
	
	stop = omp_get_wtime();
	
	printf("area = %f,\t error = %f\n", area, error);
	printf("running time = %f\n", stop - start);
	printf("Active number of threads allocated by OS: %d threads \n", OMP_NUM_THREADS);
	getchar();
	return 0;
}

void testpoint(struct d_complex c){
	struct d_complex z;
	int iter;
	double temp;
	z=c;
	for (iter=0; iter<MXITR; ++iter){
		temp = (z.r * z.r)-(z.i * z.i) + c.r;
		z.i = z.r * z.i * 2 + c.i;
		z.r = temp;
		if ((z.r * z.r + z.i * z.i)>4.0) {
			//without atomic there would be race condition
			#pragma omp atomic
			++numoutside;
			break;
		}
	}
}
