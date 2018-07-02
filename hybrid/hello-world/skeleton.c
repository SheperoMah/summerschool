#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>
// $ cc -h omp -o hello skeleton.c; aprun -n 4 -d 4 -e OMP_NUM_THREADS=4 ./hello
int main(int argc, char *argv[])
{
    int my_id, omp_rank;
    int provided, required = MPI_THREAD_FUNNELED;

    /* TODO: Initialize MPI with thread support. */
    MPI_Init_thread(&argc, &argv, required, &provided);
    /* TODO: Find out the MPI rank and thread ID of each thread and print
     *       out the results. */
    
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    #pragma omp parallel private(omp_rank)
{
    omp_rank = omp_get_thread_num();

    printf("I am process %d and thread %d\n", my_id, omp_rank); 

}
    /* TODO: Investigate the provided thread support level. */
    // change the required to MPI_THREAD_FUNNELED

    MPI_Finalize();
    return 0;
}
