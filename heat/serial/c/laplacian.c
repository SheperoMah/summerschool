#include "heat.h"

void laplacian(field *result, field *temp){
    int i,j;
    double dx2 = temp->dx * temp->dx;
    double dy2 = temp->dy * temp->dy;

    for (i=1; i<result->nx; i++){
       for (j=1; j<result->ny; j++) {
           result->data[i-1][j-1] = (temp->data[i-1][j] - 2* temp->data[i][j] + temp->data[i+1][j])/dx2 + (temp->data[i][j-1] - 2*temp->data[i][j] + temp->data[i][j+1])/dy2;
       }
    }
} 
