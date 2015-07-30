### Exercise 5 
**Mandelbrot set area.** 

The supplied program computes the area of a Mandelbrot set. The program has been parallelized with OpenMP, 
but we were lazy and didn’t do it right. Find and fix the errors (the problem is in the data environment).
Once you have a working version, try to optimize the program.

* Try different schedules on the parallel loop.
* Try different mechanisms to support mutual exclusion.
