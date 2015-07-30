/**
    openMP_fibonacci_list_tasks.cpp Defines the entry point for the console application.
	
    Purpose: Exercise 7 Tasks in OpenMP. Consider the program linked.c 
	Traverses a linked list computing a sequence of Fibonacci numbers at each node.
	Parallelize this program using tasks. Compare your solution’s complexity to an 
	approach without tasks.

    @author George Papageorgakis
    @version 1.0 10/2014
*/
//parallel version using tasks!
#include "stdafx.h"

int fib(int n) {
	int x, y;
	if (n < 2) {
		return (n);
	} else {
		x = fib(n - 1);
		y = fib(n - 2);
		return (x + y);
	}
}
/*
int fib(int n) {
	int x, y;
	if (n < 2) return (n);
	#pragma omp task shared(x)
		x = fib(n - 1);
	#pragma omp task shared(y)
		y = fib(n - 2);
	#pragma omp taskwait
		return (x + y);
}*/

void processwork(struct node* p) {
	int n;
	n 			= p->data;
	p->fibdata 	= fib(n);
}

struct node* init_list(struct node* p) {
	int i;
	struct node* head = NULL;
	struct node* temp = NULL;
    
	head 		= (node*) malloc(sizeof(struct node));
	p 			= head;
	p->data 	= FS;
	p->fibdata 	= 0;
	for (i=0; i< N; ++i) {
		temp  		= (node*) malloc(sizeof(struct node));
		p->next 	= temp;
		p 			= temp;
		p->data 	= FS + i + 1;
		p->fibdata 	= i+1;
	}
	p->next = NULL;
	return head;
}


int _tmain(int argc, _TCHAR* argv[]){
	double start, end;
	struct node *p	  = NULL;
	struct node *temp = NULL;
	struct node *head = NULL;
     
	printf("Process linked list\n");
	printf("  Each linked list node will be processed by function 'processwork()'\n");
	printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);      
 
	p 		= init_list(p);
	head 	= p;
	start 	= omp_get_wtime();
	////////////////////////////////////////////////////////////////////////////////////
	//Create a set of threads.
	#pragma omp parallel
	{
		#pragma omp master
			printf("Threads:   %d\n", omp_get_num_threads());
		//One thread executes the single construct. The other threads wait 
		//at the implied barrier at the end of the single construct
		#pragma omp single 
		{
			//The “single” thread creates a task with its own value for the pointer p
			p = head;
			while (p){
				//Shared variable p updated by multiple tasks, first private is required
				#pragma omp task firstprivate(p)
				{
					processwork(p);
				}
				p = p->next;
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////

	//old serial code
	/*
	while (p != NULL) {
		processwork(p);
		p = p->next;
	}
	*/
	end = omp_get_wtime();
	p 	= head;
	while (p != NULL) {
		printf("%d : %d\n",p->data, p->fibdata);
		temp = p->next;
		free (p);
		p = temp;
	}  
	free (p);

	printf("Compute Time: %f seconds\n", end - start);
	getchar();
	return 0;
}
