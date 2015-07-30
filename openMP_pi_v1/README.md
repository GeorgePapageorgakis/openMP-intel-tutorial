###Exercise 2 

Create a parallel version of the pi program using a parallel construct. Pay close attention to shared versus private variables.	This program has false sharing and we could Pad sum array to eliminate it.

	
threads | 1st SPMD 
------- | -------- 
1   	  | 1.86
2 	    | 1.03
3 	    | 1.08
4      	| 0.97
