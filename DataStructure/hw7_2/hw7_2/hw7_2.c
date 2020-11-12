#define BUCKETS 10
#define DIGITS 4

#include <stdio.h>
typedef int element;
int digits(int k)
{
	int i = 0;
	while (k != 0)
	{
		k = k / 10;
		i++;
	}
	return i;
}
void radix_sort(int A[], int n)
{
	int i, b, d, factor = 1;
	
	for (i = 1; i <= n; i++) {
		counting_sort(A, B, i);
	}
}
void counting_sort(int A[], int B[], int k) {
	int i, j;
	int C[1000];
	for (i = 0; i < k - 1; i++) {
		C[i] = 0;
	}
	for (j = 0; j < n - 1; j++) {
		C[A[j]] += 1;
	}
	for (i = 1; i < k - 1; i++) {
		C[i] = C[i] + C[i - 1];
	}
	for (j = n - 1; j = 1; j--) {
		B[C[A[j]]] = A[j];
		C[A[j]] -= 1;
	}
}
int main() {
	int list[] = { 329,457,657,839,436,720,355 };
	printf("before sort\n");
	for (int i = 0; i < 7; i++) {
		printf("%d\n", list[i]);
	}
	printf("after sort\n");
	radix_sort(list, 7);
	for (int i = 0; i < 7; i++) {
		printf("%d\n", list[i]);
	}
}