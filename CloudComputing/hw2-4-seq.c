#include <stdio.h>
#define MAX 100

//순차 프로그램
void main() {
	double R[MAX + 2][MAX + 2] = { 0.0 };
	int i, j, k, m1, m2, n1, n2;
	
	for (j = 40; j < 60; j++)
		R[0][j] = 200.0;

	for (k = 0; k < 10000; k++)
		for (i = 1; i <= MAX; i++)
			for (j = 1; j <= MAX; j++)
				R[i][j] = 0.25*(R[i][j - 1] + R[i][j + 1] + R[i - 1][j] + R[i + 1][j]);

	printf("출력할 구간(m1,m2,n1,n2) : ");
	scanf("%d %d %d %d", &m1, &m2, &n1, &n2);
	for (i = m1; i <= m2; i++) {
		for (j = n1; j <= n2; j++)
			printf("%7.1f", R[i][j]);
		printf("\n");
	}
}
