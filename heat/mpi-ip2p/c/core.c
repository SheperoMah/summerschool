/* Main solver routines for heat equation solver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>

#include "heat.h"

/* Exchange the boundary values */
/* only start the communication in background */
void exchange_init(field *temperature, parallel_data *parallel)
{   int sendUp, sendDown, receiveUp, receiveDown, sendUpTag, sendDownTag;
    MPI_Request sendUpRequest, sendDownRequest, recvUpRequest, recvDownRequest;


    if (parallel->rank == 0){ 
       /* Upper most rank */
       sendUp = receiveUp = MPI_PROC_NULL;
       sendDown = receiveDown = parallel->nup;
       sendUpTag = 999999;
       sendDownTag = parallel->rank+1;

    } else if( parallel->rank == parallel->size-1){
        /* Lower most rank */
       sendUp = receiveUp = parallel->nup;       
       sendDown = receiveDown = MPI_PROC_NULL;
       sendUpTag = parallel->rank-1;
       sendDownTag = 9999999;

 
    } else {
       /* Intermidate ranks */
       sendUp = receiveUp = parallel->nup;
       sendDown = receiveDown = parallel->ndown;
       sendUpTag = parallel->rank-1;
       sendDownTag = parallel->rank+1;
    }



    // Send to the up, receive from down
    // TODO
    MPI_Isend(&temperature->data[1][0], // the first non-ghost row that I have
              temperature->ny, //count
              MPI_DOUBLE, //datatype
              sendUp, //dest
              sendUpTag, //tag
              MPI_COMM_WORLD, //comm
              &parallel->requests[0]); //request

    MPI_Irecv(&temperature->data[temperature->nx+1][0],
              temperature->ny, //count
              MPI_DOUBLE, //datatype
              receiveDown, //source
              parallel->rank, //tag
              MPI_COMM_WORLD, //comm
              &parallel->requests[1]); //request

    // Send to the down, receive from up
    // TODO
    MPI_Isend(&temperature->data[temperature->nx][0],
               temperature->ny, //count
               MPI_DOUBLE, //type
               sendDown, //dest
               sendDownTag, //tag
               MPI_COMM_WORLD, //comm
               &parallel->requests[2]); //request

   MPI_Irecv(&temperature->data[0][0], 
             temperature->ny, //count
             MPI_DOUBLE, //type
             receiveUp, //source
             parallel->rank, //tag
             MPI_COMM_WORLD, //comm
             &parallel->requests[3]); //request


}


/* Update the temperature values using five-point stencil */
/* update only the border-independent region of the field */
void evolve_interior(field *curr, field *prev, double a, double dt)
{
    int i, j;
    double dx2, dy2;

    /* Determine the temperature field at next time step
     * As we have fixed boundary conditions, the outermost gridpoints
     * are not updated. */
    /* TODO */
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

/* complete the non-blocking communication */
/* TODO */
    void exchange_finalize(parallel_data *parallel)
{
    MPI_Waitall(4, parallel->requests, MPI_STATUS_IGNORE);
}

/* Update the temperature values using five-point stencil */
/* updat:e only the border-dependent regions of the field */
/* TODO */
void evolve_edges(field *curr, field *prev, double a, double dt)
{
    int i, j;
    double dx2, dy2;

}
