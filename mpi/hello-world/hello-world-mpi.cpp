#include <stdio.h>

#include <omp.h>
#include <mpi.h>

int main (int argc, char** argv[]) {
    int rc, rank, size;
    MPI_Init(&argc, argv);


    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
       printf("Hi I am zero, and the number of processes is %d \n", size);
       printf("Hello world! by thread %d\n", rank);
    } else{
        printf("Hello world! by thread %d\n", rank); 
    }


    MPI_Finalize();

}

