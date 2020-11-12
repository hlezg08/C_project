#include <stdio.h>
#include <mpi.h>
#define MAX 100

//���� ���α׷�
int main(void) {
	int rank, size, tag = 5;
	double R[MAX + 2][MAX + 2] = { 0.0 };
	int i, j, k, m1, m2, n1, n2;
	
	MPI_Status status;
	MPI_Datatype columntype; 
	MPI_Datatype newtype; 

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//1 column�� columntype���� ������
	MPI_Type_vector(MAX, 1, MAX, MPI_DOUBLE, &columntype);
	MPI_Type_commit(&columntype);

	//(100/size)�� column�� newtype���� ������
	MPI_Type_vector(MAX, MAX / size, MAX, MPI_DOUBLE, &newtype);
	MPI_Type_commit(&newtype);

	//������ �κ� �µ��� 200�� ����
	for (j = 40; j < 60; j++)
		R[0][j] = 200.0;

	MPI_Bcast(&R[1][1], 1, newtype, 0, MPI_COMM_WORLD);//R�迭�� (100/size)�� column��ŭ Bcast

	//�� ���μ������� R�迭 �µ��� ������Ʈ
	for (k = 0; k < 10000; k++)
		for (i = 1; i <= MAX; i++)
			for (j = 1; j <= MAX; j++)
				R[i][j] = 0.25*(R[i][j - 1] + R[i][j + 1] + R[i - 1][j] + R[i + 1][j]);

	if (rank == 0) {
		//0��° ���μ����� send&recv 1�� ����
		MPI_Send(&R[1][MAX / size - 1], 1, columntype, 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&R[1][1], 1, columntype, 1, tag, MPI_COMM_WORLD, &status);
	}
	if (rank !=0 && rank !=size-1) { 
		//0��° ���μ����� ������ ���μ����� ������ ������ ���μ����� ��� 
		MPI_Recv(&R[1][MAX / size - 1], 1, columntype, rank-1, tag, MPI_COMM_WORLD, &status);
		MPI_Send(&R[1][1], 1, columntype, rank-1, tag, MPI_COMM_WORLD);

		MPI_Send(&R[1][MAX / size - 1], 1, columntype, rank+ 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&R[1][1], 1, columntype, rank+1, tag, MPI_COMM_WORLD, &status);
		//send&recv�� 2���� ����, avoid deadlock
	}
	if (rank == size-1) {
		//������ ���μ����� send&recv 1�� ����
		MPI_Recv(&R[1][MAX / size - 1], 1, columntype, rank-1, tag, MPI_COMM_WORLD, &status);
		MPI_Send(&R[1][1], 1, columntype, rank - 1, tag, MPI_COMM_WORLD);
	}

	//��� ���
	if (rank == 0) {
		printf("����� ����(m1,m2,n1,n2) : ");
		scanf("%d %d %d %d", &m1, &m2, &n1, &n2);
		for (i = m1; i <= m2; i++) {
			for (j = n1; j <= n2; j++)
				printf("%7.1f", R[i][j]);
			printf("\n");
		}
	}

	MPI_Finalize();
	return 0;
}