/* Main solver routines for heat equation solver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>

#include "heat.h"

/* Exchange the boundary values */
void exchange(field *temperature, parallel_data *parallel)
{   int sendDown, sendUp, receiveDown, receiveUp, sendUpTag, sendDownTag;
    if (parallel->rank == 0){

        sendDown = parallel->ndown;
        receiveUp = MPI_PROC_NULL; 
        receiveDown = parallel->ndown;
        sendUp = MPI_PROC_NULL;
        sendUpTag = 999;
        sendDownTag= parallel->rank+1;
        
    } else if (parallel->rank == parallel->size-1 ) {

        sendUp = parallel->nup;
        receiveDown = MPI_PROC_NULL;
        receiveUp = parallel->nup;
        sendDown = MPI_PROC_NULL; 
        sendUpTag = parallel->rank-1;
        sendDownTag = 999;          
   } else {
        sendUp = parallel->nup;
        receiveUp = parallel->nup;
        sendDown = parallel->ndown;
        receiveDown = parallel->ndown;
        sendUpTag = parallel->rank-1;
        sendDownTag = parallel->rank+1;
   }

    
    /* TODO start: implement halo exchange */
    // Send to the up, receive from down
    MPI_Sendrecv(&temperature->data[1][0], //sendbuf
                 temperature->ny, // sendcount
                 MPI_DOUBLE, // sendtype
                 sendUp, // dest
                 sendUpTag, //sendtag
                 &temperature->data[temperature->nx+1][0], // recvBuf
                 temperature->ny, // recvcount
                 MPI_DOUBLE, // recvtype
                 receiveDown, // source
                 parallel->rank,  // rectag
                 MPI_COMM_WORLD, // comm
                 MPI_STATUS_IGNORE); // status

    // Send to the down, receive from up
    MPI_Sendrecv(&temperature->data[temperature->nx+1][0], //sendbuf
                 temperature->ny, // sendcount
                 MPI_DOUBLE, // sendtype
                 sendDown, // dest
                 sendDownTag, //sendtag
                 &temperature->data[0][0], // recvBuf
                 temperature->ny, // recvcount
                 MPI_DOUBLE, // recvtype
                 receiveUp, // source
                 parallel->rank,  // rectag
                 MPI_COMM_WORLD, // comm
                 MPI_STATUS_IGNORE); // status

    /* TODO end */
  
}


/* Update the temperature values using five-point stencil */
void evolve(field *curr, field *prev, double a, double dt)
{
    int i, j;
    double dx2, dy2;

    /* Determine the temperature field at next time step
     * As we have fixed boundary conditions, the outermost gridpoints
     * are not updated. */
    dx2 = prev->dx * prev->dx;
    dy2 = prev->dy * prev->dy;
    for (i = 1; i < curr->nx + 1; i++) {
        for (j = 1; j < curr->ny + 1; j++) {
            curr->data[i][j] = prev->data[i][j] + a * dt *
                               ((prev->data[i + 1][j] -
                                 2.0 * prev->data[i][j] +
                                 prev->data[i - 1][j]) / dx2 +
                                (prev->data[i][j + 1] -
                                 2.0 * prev->data[i][j] +
                                 prev->data[i][j - 1]) / dy2);
        }
    }
}


