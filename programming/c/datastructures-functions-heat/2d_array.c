#include <stdio.h>
#include <stdlib.h>



#define NX 258
#define NY 258

int main(void)
{
    int i, j;
    // Add here the definition for array with name 'array'
    // of size NX times NY (258x258)
    double heatArray[258][258];
    // Initialize first the zeros
    for (i=1; i<257; i++) {
        for (j=1; j<257; j++){
            heatArray[i][j] = (double) 0;
        }    
    }
    

    // Initial conditions for left and right
    for (i=0; i<258; i++) {
        heatArray[i][0] = (double) 20;
        heatArray[i][257] = (double) 70;
    }
    // and top and bottom boundaries
    

    for (j=0; j<258; j++){
        heatArray[0][j] = (double) 85;
        heatArray[257][j] = (double) 5;
    }
    return 0;


}
