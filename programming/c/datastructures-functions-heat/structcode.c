#include <stdio.h>

#define NX 256
#define NY 256

typedef struct{
    int nx;
    int ny;
    double dx;
    double dy;
    double dx2;
    double dy2;   
    double fieldData[NX+2][NY+2]; 
} tempField;



tempField initalize_fieldData(tempField temp, 
                              double leftBound,
                              double rightBound,
                              double upperBound,
                              double lowerBound,
                              double middleValue){
    int i,j;
    /* assign middle values */
    for (i=1; i < NY+1; i++) {
        for (j = 1; j < NX+1; j++) {
            temp.fieldData[i][j] = middleValue;
        }
    }
    /* assign upper and lower bounds*/
    for (j=0; j < NX+2; j++) {
        temp.fieldData[0][j] = upperBound;
        temp.fieldData[NY+1][j] = lowerBound;
    }
    /* assign right and left bounds */
    for (i=0; i < NX+2, i++) {
        temp.fieldData[i][0] = leftBound;
           tem 
    }



    return temp;
}

int main () {

    tempField field2d;
    field2d.nx = 258;
    field2d.ny = 258;
    field2d.dx = 0.01;
    field2d.dy = 0.01;
    field2d.dx2 = field2d.dx * field2d.dx;
    field2d.dy2 = field2d.dy * field2d.dy;
    

    return 0;
}
