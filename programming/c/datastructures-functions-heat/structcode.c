#include <stdio.h>

#define NX 6//256
#define NY 6//256

typedef struct{
    int nx;
    int ny;
    double dx;
    double dy;
    double dx2;
    double dy2;   
    double fieldData[NX+2][NY+2]; 
} tempField;

typedef struct{
    int nx;
    int ny;
    double dx;
    double dy;
    double dx2;
    double dy2;
    double fieldData[NX][NY];
} laplacianField;

void initalize_fieldData(tempField *temp, 
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


void laplacian_matrix(laplacianField *result, tempField *temp){
    int i,j;
    for (i=1; i<NY+1; i++){

       for (j=1; j<NX+1; j++) {
           result->fieldData[i-1][j-1] = (temp->fieldData[i-1][j] - 2* temp->fieldData[i][j] + temp->fieldData[i+1][j])/temp->dx2 + (temp->fieldData[i][j-1] - 2*temp->fieldData[i][j] + temp->fieldData[i][j+1])/temp->dy2;
       }
    } 
}



int main () {

    tempField field2d;
    field2d.nx = 258;
    field2d.ny = 258;
    field2d.dx = 0.01;
    field2d.dy = 0.01;
    field2d.dx2 = field2d.dx * field2d.dx;
    field2d.dy2 = field2d.dy * field2d.dy;
    initalize_fieldData(&field2d, 20.0, 70.0, 80.0, 5.0, 0.0); 


    laplacianField lapField2d;
    laplacian_matrix(&lapField2d, &field2d);
    
    int i,j;
    for (i=0; i<NY; i++){
        for (j=0; j<NX; j++) {
            printf("%f ", lapField2d.fieldData[i][j]);
        }
        printf("\n");
    }
    return 0;
}
