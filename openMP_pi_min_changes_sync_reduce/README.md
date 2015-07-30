###Exercise 4 
**Pi with loops.** 

Go back to the serial pi program and parallelize it with a loop construct. The goal is to minimize the number of changes made to the serial program.

threads | 1st SPMD | 1st SPMD padded | SPMD critical
------- | -------- | --------------- | ------------
1 	    | 1.86 	   | 1.86 	         | 1.87
2 	    | 1.03	   | 1.01	           | 1.00
3 	    | 1.08 	   | 0.69 	         | 0.68
4 	    | 0.97 	   | 0.53 	         | 0.53
