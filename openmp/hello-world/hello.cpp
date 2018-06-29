#include <cstdio>
#include <iostream>
#include <omp.h>

int main(int argc, char *argv[]) {
    int omp_rank;
   #pragma omp parallel private(omp_rank)
   {
   omp_rank = omp_get_thread_num();
    std::cout << "Hello world!" << omp_rank << "\n";
   }
   return 0;
}
