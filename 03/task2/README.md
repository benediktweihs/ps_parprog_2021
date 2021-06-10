### Issues found

Generally, all Threads operate on the same location in memory which is not safe and unnecessary. Maybe two threads will try to access a specific value in the array c at the same time. This could lead to some results getting lost.

Furthermore, the aspired final result is the sum of all products of corresponding elements in `a` and `b`. This will not be calculated as every single thread overwrites (maybe not exactly) each value in `c`. Hence, the final result should be approximately (num_threads)^2 times the real value as each thread also adds up their values in c to the final result `res` via the array `local_res`.

Also it is not very performant if all threads essentially operate on the same section of (shared) memory. This is basically the case since `a`, `b`, `c` and `local_res` are shared variables.

Problems with formatting have not been addressed.