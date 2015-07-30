###Exercise 3. 

In exercise 2, you probably used an array to create space for each thread to store its partial sum. If array elements happen to share a cache line, this leads to false sharing. 
Non-shared data in the same cache line so each update invalidates the cache line, in essence “sloshing independent data” back and forth between threads.

Modify your “pi” from exercise 2 to avoid false sharing due to the sum array.
	
threads | 1st SPMD | 1st SPMD padded | SPMD critical
------- | -------- | --------------- | ------------
1 	| 1.86 	   | 1.86 	     | 1.87
2 	| 1.03	   | 1.01	     | 1.00
3 	| 1.08 	   | 0.69 	     | 0.68
4 	| 0.97 	   | 0.53 	     |	0.53
