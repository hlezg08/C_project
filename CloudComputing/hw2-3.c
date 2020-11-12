#include <stdio.h>
#include <mpi.h>

int main(void) {
	int rank, size, i, j;
	int A[5][5];
	int B[5][5];
	int tag = 5;
	MPI_Status status;
	MPI_Datatype columntype;
	
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			A[i][j] = 0;
		}
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			B[i][j] = 0;
		}
	}

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if (rank == 0) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				A[i][j] = i*5+j;
			}
		}
	}
	if (rank == 1) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				B[i][j] = i * 5 + j+50;
			}
		}
	}
	MPI_Type_vector(5,1,5,MPI_INT,&columntype);
	MPI_Type_commit(&columntype);
	if(rank==0)
		MPI_Send((&A[0][3]), 1, columntype, 1, tag, MPI_COMM_WORLD);
	
	if (rank == 1) {
		MPI_Recv((&B[0][4]), 1, columntype, 0, tag, MPI_COMM_WORLD, &status);
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 5; j++) {
				printf("%d ", B[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}