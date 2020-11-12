#include <stdio.h>
#include <mpi.h>
#define MAXSIZE 1000
int main(void) {
	int my_rank,size,i;
	int A[MAXSIZE],B[MAXSIZE];
	int cnt=0,result=0;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (my_rank == 0) {
		for (i = 0; i < MAXSIZE; i++) A[i] = i + 1;
	}
	
	MPI_Scatter(A,MAXSIZE/size,MPI_INT,&B, MAXSIZE/size,MPI_INT,0,MPI_COMM_WORLD);
	
	for (i = 0; i <MAXSIZE / size; i++) {
		if (B[i] % 2 != 0) cnt++;
	}

	MPI_Reduce(&cnt, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (my_rank == 0) {
		printf("%d\n", result);
	}
	
	MPI_Finalize();
	return 0;
}