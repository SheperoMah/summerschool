/* Main solver routines for heat equation solver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "heat.h"
#include "laplacian.h"

/* Update the temperature values using five-point stencil */
void evolve(field *curr, field *prev, double a, double dt)
{
    int i, j;
    double dx2, dy2;
    field lapField;
    printf("test1");
    laplacian(&lapField, curr);

    printf("laplacian done!");
    /* Determine the temperature field at next time step
     * As we have fixed boundary conditions, the outermost gridpoints
     * are not updated. */
    dx2 = prev->dx * prev->dx;
    dy2 = prev->dy * prev->dy;
    


    
    /* TODO: Add update loops for computing the new field values
             of 'curr' using field 'prev' */
    for (i=1; i < curr->nx-5; i++){
        for (j=1; j< curr->ny-5; j++){
            curr->data[i][j] = prev->data[i][j] + dt * a * lapField.data[i][j] * curr->data[i][j];
        }
    }
}


