#include <stdio.h>

#include <omp.h>
#include <mpi.h>

int main (int argc, char** argv[]) {
    int rc, rank;
    MPI_Init(&argc, argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello world! by thread %d\n", rank);
    MPI_Finalize();

}

