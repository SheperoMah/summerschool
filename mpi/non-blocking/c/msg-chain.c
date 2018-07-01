#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int size = 10000000;
    int *message;
    int *receiveBuffer;
    MPI_Status statuses[2];
    MPI_Request requests[2];

    double t0, t1;

    int source, destination, tag, recvtag;
    int count;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Allocate message buffers */
    message = malloc(sizeof(int) * size);
    receiveBuffer = malloc(sizeof(int) * size);
    /* Initialize message */
    for (i = 0; i < size; i++) {
        message[i] = myid;
    }

    /* Set source and destination ranks */
    if (myid < ntasks - 1) {
        destination = myid + 1;
        tag = destination;
    } else {
        destination = MPI_PROC_NULL;
        tag = 9999;
    }
    if (myid > 0) {
        source = myid - 1;
        recvtag = myid;
    } else {
        source = MPI_PROC_NULL;
        recvtag = 9999;
    }
    //printf("I %d send %d with tag %d\n", myid, destination, tag);
    //printf("I %d recv from %d with tag %d\n",myid, source, recvtag);
    /* Start measuring the time spend in communication */
    MPI_Barrier(MPI_COMM_WORLD);
    t0 = MPI_Wtime();

    /* Send and receive messages as defined in exercise */
    /* TODO: Implement the communication using non-blocking
             sends and receives */
    MPI_Isend(message, //buffer
              size, //count
              MPI_INT, //datatype
              destination, // dest
              tag, //tag
              MPI_COMM_WORLD, //comm
              &requests[0]); //request

    MPI_Irecv(receiveBuffer, //buffer
              size, //count
              MPI_INT, //datatype
              source, //source
              recvtag, //tag
              MPI_COMM_WORLD, //comm
              &requests[1]); //request

    printf("Sender: %d. Sent elements: %d. Tag: %d. Receiver: %d\n", myid,
           size, tag, destination);

    /* Blocking wait for messages */
    /* TODO: Add here the synchronization call so that you can
             be sure that all messages have been received */
    /*MPI_Wait(requests[0], &statuses[0]);
    MPI_Wait(requests[1], &statuses[1]);
*/
   MPI_Waitall(2, requests, statuses);

    MPI_Get_count(&statuses[0], MPI_INT, &count);
    printf("Receiver: %d. received elements: %d. Tag %d. Sender: %d.\n",
           myid, count, statuses[0].MPI_TAG, statuses[0].MPI_SOURCE);

    /* Finalize measuring the time and print it out */
    t1 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    fflush(stdout);

    printf("Time elapsed in rank %2d: %6.3f\n", myid, t1 - t0);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
