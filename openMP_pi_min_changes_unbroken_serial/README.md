###Exercise 4 
**Pi with loops.** 

Use minimum changes in the classic serial pi program without breaking the serial version for compilers that do not support openMP if compiler does not support openMP it skips all directives #pragma omp
	
threads | 1st SPMD | 1st SPMD padded | SPMD critical | PI Loop
------- | -------- | --------------- | ------------  | -------
1 	| 1.86 	   | 1.86 	     | 1.87	     | 1.91
2 	| 1.03	   | 1.01	     | 1.00	     | 1.02
3 	| 1.08 	   | 0.69 	     | 0.68	     | 0.80
4 	| 0.97 	   | 0.53 	     |	0.53	     | 0.68
