#include <iostream>
#include <cstdio>
#include <vector>
#include <mpi.h>



int main(int argc, char** argv[]) {

   int size, rank;
   MPI_Init(&argc, argv);

   MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
   MPI_Comm_size(MPI_COMM_WORLD, &size);
  
   std::vector<int> a(size+100000);
   a[rank] = rank;

   if (rank == 0){
       std::cout << "Hi from process " << rank << ".\n";
       std::cout << "common array value (0) " << a[0] << ".\n";
       MPI_Send(&a, size, MPI_INT, 3, 8089, MPI_COMM_WORLD);
   } else if(rank ==3) {
       MPI_Status status;
       MPI_Recv(&a, size, MPI_INT, 0, 8089, MPI_COMM_WORLD, &status);
       std::cout <<  "Hi I am the third process, and I received " << a[0]  << " from process 0.\n";
   } else {
       std::cout << "Hi we are " << size << " processes. \n";
       std::cout << "common array value (0) " << a[0] << ".\n";
   }
   return 0;
   MPI_Finalize();
}
