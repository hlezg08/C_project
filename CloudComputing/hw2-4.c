#include <stdio.h>
#include <mpi.h>
#define MAX 100

//병렬 프로그램
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

	//1 column을 columntype으로 정의함
	MPI_Type_vector(MAX, 1, MAX, MPI_DOUBLE, &columntype);
	MPI_Type_commit(&columntype);

	//(100/size)개 column을 newtype으로 정의함
	MPI_Type_vector(MAX, MAX / size, MAX, MPI_DOUBLE, &newtype);
	MPI_Type_commit(&newtype);

	//벽난로 부분 온도값 200도 유지
	for (j = 40; j < 60; j++)
		R[0][j] = 200.0;

	MPI_Bcast(&R[1][1], 1, newtype, 0, MPI_COMM_WORLD);//R배열에 (100/size)개 column만큼 Bcast

	//각 프로세스마다 R배열 온도값 업데이트
	for (k = 0; k < 10000; k++)
		for (i = 1; i <= MAX; i++)
			for (j = 1; j <= MAX; j++)
				R[i][j] = 0.25*(R[i][j - 1] + R[i][j + 1] + R[i - 1][j] + R[i + 1][j]);

	if (rank == 0) {
		//0번째 프로세스는 send&recv 1번 수행
		MPI_Send(&R[1][MAX / size - 1], 1, columntype, 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&R[1][1], 1, columntype, 1, tag, MPI_COMM_WORLD, &status);
	}
	if (rank !=0 && rank !=size-1) { 
		//0번째 프로세스와 마지막 프로세스를 제외한 나머지 프로세스의 경우 
		MPI_Recv(&R[1][MAX / size - 1], 1, columntype, rank-1, tag, MPI_COMM_WORLD, &status);
		MPI_Send(&R[1][1], 1, columntype, rank-1, tag, MPI_COMM_WORLD);

		MPI_Send(&R[1][MAX / size - 1], 1, columntype, rank+ 1, tag, MPI_COMM_WORLD);
		MPI_Recv(&R[1][1], 1, columntype, rank+1, tag, MPI_COMM_WORLD, &status);
		//send&recv를 2번씩 수행, avoid deadlock
	}
	if (rank == size-1) {
		//마지막 프로세스는 send&recv 1번 수행
		MPI_Recv(&R[1][MAX / size - 1], 1, columntype, rank-1, tag, MPI_COMM_WORLD, &status);
		MPI_Send(&R[1][1], 1, columntype, rank - 1, tag, MPI_COMM_WORLD);
	}

	//결과 출력
	if (rank == 0) {
		printf("출력할 구간(m1,m2,n1,n2) : ");
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