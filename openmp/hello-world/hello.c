#include <stdio.h>
#include <omp.h>


int main(int argc, char *argv[])
{
    printf("Hello world!\n");
    
    #pragma omp parallel
    {
        int threadscount, threadnum;
        threadscount = omp_get_num_threads();
        #pragma omp master 
        {
            printf("total number of threads: %d \n", threadscount);
        }

        threadnum = omp_get_thread_num();
        printf("Thread ID: %d\n", threadnum);
    }

    return 0;
}
