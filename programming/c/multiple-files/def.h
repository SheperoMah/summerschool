#ifndef DEF_H_
#define DEF_H_
#define NX 6
#define NY 6

typedef struct{
    int nx;
    int ny;
    double dx;
    double dy;
    double dx2;
    double dy2;   
    double fieldData[NX+2][NY+2]; 
} TEMPFIELD;

typedef struct{
    int nx;
    int ny;
    double dx;
    double dy;
    double dx2;
    double dy2;
    double fieldData[NX][NY];
} LAPFIELD;
#endif
