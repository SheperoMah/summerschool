#include <iostream>
#include <cstdio>
#include <mpi.h>
#include <vector>


int main(int argc, char** argv[]) {
   

   int ntasks, myid; 
   MPI_Init(&argc, argv);
   MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &myid);

   
   std::vector<int> receivedMessage(ntasks);

   MPI_Status status;

   if(myid ==  0) { 
          int receiver = myid+1;
          std::vector<int> message(ntasks, myid);

          std::cout << "I am " << myid  << " and I am sending "<< message[0] << " values with tag [and to] " << receiver << "\n";
          MPI_Send(&message, ntasks, MPI_INT, receiver, receiver, MPI_COMM_WORLD);
   } else if (myid < ntasks-1 && myid >0){   
          int receiver = myid+1;
          std::vector<int> message(ntasks, myid);

          std::cout << "I am " << myid  << " and I am sending "<< message[0] << " values with tag [and to] " << receiver << "\n";
          MPI_Sendrecv(&message, ntasks, MPI_INT, receiver, receiver,
                       &receivedMessage, ntasks, MPI_INT, myid-1, myid,
                       MPI_COMM_WORLD, &status);
          std::cout << "I am " << myid  << " and I received from " << status.MPI_SOURCE<< " with tag " << status.MPI_TAG <<". \n";
  } else { 
          MPI_Recv(&receivedMessage, ntasks, MPI_INT, myid-1, myid, MPI_COMM_WORLD, &status);
          std::cout << "I am " << myid  << " and I received from " << status.MPI_SOURCE << " with tag " << status.MPI_TAG <<". \n";
 
   }

   MPI_Finalize();
   return 0;
}
