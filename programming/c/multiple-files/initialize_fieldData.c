#include "def.h"

void initialize_field_data(TEMPFIELD *temp, 
                     double leftBound,
                     double rightBound, 
                     double upperBound, 
                     double lowerBound,
                     double middleValue){
    int i,j;
    /* assign middle values */
    for (i=1; i < NY+1; i++) {
       for (j = 1; j < NX+1; j++) {
           temp->fieldData[i][j] = middleValue;
       }
    }
    /* assign upper and lower bounds*/
    for (j=0; j < NX+2; j++) {
        temp->fieldData[0][j] = upperBound;
        temp->fieldData[NY+1][j] = lowerBound;
    }
    /* assign right and left bounds */
    for (i=0; i < NX+2; i++) {
        temp->fieldData[i][0] = leftBound;
        temp->fieldData[i][NX+1] = rightBound;
    }

}

