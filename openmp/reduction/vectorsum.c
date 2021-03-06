#include <stdio.h>
#include <omp.h>


#define NX 102400

int main(void)
{
    long vecA[NX];
    long sum,  sumex, threadSum;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = (long) i + 1;
    }

    sumex = (long) NX * (NX + 1) / ((long) 2);
    printf("Arithmetic sum formula (exact):                  %ld\n",
           sumex);

    sum = 0.0;
    /* TODO: Parallelize computation */
    #pragma omp parallel for shared(vecA) private(i) reduction(+:sum)
    for (i = 0; i < NX; i++) {
        sum += vecA[i];
    }

    printf("Sum using \"reduction\" clause: %ld\n", sum);

    sum = 0.0;
    /* TODO: Parallelize computation using critical */
    #pragma omp parallel shared(vecA, sum) private(i, threadSum)
    {   threadSum = 0.0;
        for (i = 0; i < NX; i++) {
                threadSum += vecA[i];
            }
        #pragma omp critical(addThreadSums)
        sum += threadSum; 
    }
    printf("Sum using critical sum :%ld\n", sum);



    return 0;
}
