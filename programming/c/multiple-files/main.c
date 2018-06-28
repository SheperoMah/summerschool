#include <stdio.h>
#include "laplacian.h"
#include "initialize_fieldData.h"
#include "def.h"




int main () {

    TEMPFIELD field2d;
    field2d.nx = 258;
    field2d.ny = 258;
    field2d.dx = 0.01;
    field2d.dy = 0.01;
    field2d.dx2 = field2d.dx * field2d.dx;
    field2d.dy2 = field2d.dy * field2d.dy;
    initialize_field_data(&field2d, 20.0, 70.0, 80.0, 5.0, 0.0); 


    LAPFIELD lapField2d;
    laplacian(&lapField2d, &field2d);
    
    int i,j;
    for (i=0; i<NY; i++){
        for (j=0; j<NX; j++) {
            printf("%f ", lapField2d.fieldData[i][j]);
        }
        printf("\n");
    }
    return 0;
}
