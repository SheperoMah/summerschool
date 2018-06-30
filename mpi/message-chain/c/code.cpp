#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <vector>


int main(int argc, char** argv[]) {
   

   int ntasks, myid; 
   MPI_Init(&argc, argv);
   MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &myid);

   
   std::vector<int> message(ntasks);
   message[myid] = myid;
   std::vector<int> receivedMessage(ntasks);

   MPI_Status status;
   if (myid < ntasks-1) {
      int receiver = myid+1;

      std::cout << "I am " << myid  << " and I am sending "<< ntasks << " values with tag [and to] " << receiver << "\n";
      MPI_Sendrecv(&message, ntasks, MPI_INT, receiver, receiver,  &receivedMessage, ntasks, MPI_INT, MPI_PROC_NULL, receiver, MPI_COMM_WORLD, &status);
   }
 if (myid > 0 ) {

       std::cout << " I am " << myid  << " and I received " << receivedMessage[0] << " with tag " << status.MPI_TAG <<". \n"; 

   }
   MPI_Finalize();
   return 0;
}
