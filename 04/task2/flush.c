#include <omp.h>
#include <stdio.h>

// thread 1 *should* wait for thread 0 until execution can resume
// spinlock

// #pragma omp flush is necessary to make sure to update the threads copy of the shared memory
// if #pragma omp flush(flag) is not called the spinlock can fail
// i dont think that it can fail otherwise (tried it 10000 times)
// obviously thread 1 terminate execution if shared memory is not updated properly

int main() {
    int data, flag = 0;
    #pragma omp parallel default(none) shared(data, flag)
    {
        if (omp_get_thread_num()==0) {
            /* Write to the data buffer that will be read by thread */
            data = 42;
            /* Set flag to release thread 1 */
            flag = 1;
        }
        else if (omp_get_thread_num()==1) {
            /* Loop until we see the update to the flag */
            while (flag < 1) {
                #pragma omp flush(flag)
            }
            /* print flag and data */
            printf("flag=%d data=%d\n", flag, data);
        }
    }
    return 0;
}
