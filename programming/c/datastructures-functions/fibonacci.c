#include <stdio.h>



int add_one_to_both(int *a, int *b){
    (*a)++;
    (*b)++;
    return 0;
}




int main(int argc, char *argv[])
{
    // declare array and loop variable
    int f[20];
    int i;

    // initialize necessary array elements and write the for loop

    printf("First 20 Fibonacci numbers are:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", f[i]);
    }

    printf("\n");

    return 0;
}
