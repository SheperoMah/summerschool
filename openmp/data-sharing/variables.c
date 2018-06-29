#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    int var1 = 1, var2 = 2;

    /* TODO:
     *   Test the effect of different data sharing clauses here
     */
    #pragma omp parallel shared(var1, var2)
    {
        printf("Region 1: var1=%i, var2=%i\n", var1, var2);
        var1++;
        int r = rand() % 1000; /* random number between 0 and 100 */
        sleep(r/1000);
        var2++;
        printf("After Modification in region 1: var1=%i, var2=%i\n", var1, var2);
        printf("r = %d",r);
    }
    printf("After region 1: var1=%i, var2=%i\n\n", var1, var2);

    return 0;
}
