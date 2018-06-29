#include "heat.h"

void initialize_field_data(field *temp, 
                     double leftBound,
                     double rightBound, 
                     double upperBound, 
                     double lowerBound,
                     double middleValue){
    int i,j;
    /* assign middle values for a field of (nx+2) * (ny+2) */
    for (i=1; i < temp->nx+1; i++) {
       for (j = 1; j < temp->ny+1; j++) {
           temp->data[i][j] = middleValue;
       }
    }
    /* assign upper and lower bounds*/
    for (j=0; j < temp->nx+1; j++) {
        temp->data[0][j] = upperBound;
        temp->data[temp->ny+1][j] = lowerBound;
    }
    /* assign right and left bounds */
    for (i=0; i < temp->ny+1; i++) {
        temp->data[i][0] = leftBound;
        temp->data[i][temp->nx+1] = rightBound;
    }

}

