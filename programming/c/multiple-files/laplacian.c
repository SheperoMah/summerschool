#include "def.h"

void laplacian(LAPFIELD *result, TEMPFIELD *temp){
    int i,j;
    for (i=1; i<NY+1; i++){

       for (j=1; j<NX+1; j++) {
           result->fieldData[i-1][j-1] = (temp->fieldData[i-1][j] - 2* temp->fieldData[i][j] + temp->fieldData[i+1][j])/temp->dx2 + (temp->fieldData[i][j-1] - 2*temp->fieldData[i][j] + temp->fieldData[i][j+1])/temp->dy2;
       }
    }
} 
