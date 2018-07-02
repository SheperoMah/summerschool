#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int array[8][8];
    //TODO: Declare a variable storing the MPI datatype
    MPI_Datatype column;
    MPI_Datatype index;

    int i, j;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    } else {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                array[i][j] = 0;
            }
        }
    }

    if (rank == 0) {
        printf("Data in rank 0\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    //TODO: Create datatype that describes one column. Use MPI_Type_vector.
    MPI_Type_vector(8, 1, 8, MPI_INT, &column);
    MPI_Type_commit(&column);
    
    int displs[4];// = {0,17,33,51};
    int blocklens[4] = {1, 2, 3, 4};

    for (i=0; i < 4; i++){ 
        displs[i] = i + 2*i*8;
        }

    MPI_Type_indexed(4, blocklens, displs, MPI_INT, &index);
    MPI_Type_commit(&index);

    //TODO: Send first column of matrix form rank 0 to rank 1
    MPI_Request request;

    if (rank == 0){
       MPI_Send(&array[0][1], 1, column, 1, 9090, MPI_COMM_WORLD);  
       MPI_Send(&array[0][0], 1, index, 2, 9080, MPI_COMM_WORLD);
    }
    if (rank == 1){
        MPI_Recv(&array[0][1], 1, column, 0, 9090, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    if (rank ==2){
       MPI_Recv(&array[0][0], 1, index, 0, 9080, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    //TODO: free datatype
    MPI_Type_free(&column);
    MPI_Type_free(&index);
    // Print out the result on rank 1
    // The application is correct if the first column has the values of rank 0
    /*if (rank == 1) {
        printf("Received data on rank 1\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }*/

   if (rank == 2) {
        printf("Received data on rank 2\n");
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                printf("%3d", array[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
