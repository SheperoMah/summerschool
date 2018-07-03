#include <iostream>
#include <cstdio>
#include <vector>
#include <omp.h>
#include <mpi.h>
#include <vector>

 
int main (int argc, char** argv[]) 
{
  int provided, myrank, thread_num, procSize, i;
  MPI_Request rqst[2];
  MPI_Status stats[2];
   

  MPI_Init_thread(&argc, argv, MPI_THREAD_MULTIPLE, &provided);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &procSize);


  std::vector<int> vect(50,1);//= {101, 102, 103, 201, 202, 203, 301, 302, 303, 401, 402, 403};
  std::vector<int> recvBuf(50,-1);

  if(myrank < procSize-1) {
    MPI_Isend(&vect[0], myrank, MPI_INT, myrank+1, 9090, MPI_COMM_WORLD, &rqst[0]);
  }
  if (myrank > 0) {
    MPI_Irecv(&recvBuf[0], myrank-1, MPI_INT, myrank, 9090, MPI_COMM_WORLD, &rqst[1]);
  MPI_Wait(&rqst[0], MPI_STATUS_IGNORE);
  MPI_Wait(&rqst[1], MPI_STATUS_IGNORE);
  } else { 
    MPI_Wait(&rqst[0], MPI_STATUS_IGNORE);
  }

  //MPI_Waitall(2, rqst, stats);
  for (i=0; i<myrank-1; i++){ printf("%d", recvBuf[i]); }
  printf("\n");

  #pragma omp parallel
  {
    thread_num = omp_get_thread_num();
    printf("Hi there! thread %d in process %d.\n", thread_num, myrank);
  }

  MPI_Finalize();
}
