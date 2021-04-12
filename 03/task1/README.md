### Programs
task1 corresponds to critical section

task2 corresponds to atomic statement

task3 corresponds to reduction clause

### Plots
final.pdf shows output of each program (wall execution time on lcc2) depending on OMP_NUM_THREADS.
From left to right the subfigures show task1, task2 and task3. Raw data is located in the directory data.
The script profiler.sh was used to generate these plots which were generated with the python program plot.py (matplotlib, 
numpy and pandas required).

### Comparison with /usr/bin/time
The time measurement with /usr/bin/time matches the output of each program (measured with omp_get_wtime).

### Comparison with Assignement 02
Way faster because in the last homework i used rand() which is not thread safe.

