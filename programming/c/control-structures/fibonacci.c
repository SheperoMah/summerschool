#include <stdio.h>

int main(int argc, char *argv[])
{
    int f0, f1, f2;

    // initialize variables and write the while loop
    // Remember to update all variables within the loop
    f0 = 0;
    f1 = 1;
    int i = 1;
    int f1Old;
    while (i < 100) {
        f1Old = f1;
        f1 += f0;
        f0 = f1Old;
        printf("%d\n", f1);
        i++;
    }
    return 0;
}
