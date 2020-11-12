#include <stdio.h>
#include <mpi.h>

int main(void) {
	int rank, size, i,j;
	int A[10][10];

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				A[i][j] = i * 10 + j;
			}
		}
		
	}
	MPI_Bcast(&(A[0][0]), 10 * 10, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 1) {
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				printf("%d ", A[i][j]);
			}
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}