#include <stdio.h>

int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
} //최댓값을 출력하는 함수

void counting_sort(int arr[], int n, int exp)
{
	int output[100]; //정렬된 array
	int i, count[10] = { 0 }; //count array는 각 숫자마다 나타난 빈도수(histogram)(0~9)

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++; //histogram수 하나씩 증가

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1]; //누적 histogram 만들기

	for (i = n - 1; i >= 0; i--) //배열 끝 index에서부터 정렬하기
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i]; //arr에 있던 숫자를 output 배열에 집어넣기
		count[(arr[i] / exp) % 10]--; //histogram수는 하나씩 감소
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i]; 
}

void radix_sort(int arr[], int n)
{
	int max = getMax(arr, n);
	int exp;
	for (exp = 1; max / exp > 0; exp *= 10)
		counting_sort(arr, n, exp); //1의 자리,10의 자리,100의 자리...비교
}

int main()
{
	int arr[] = { 329,457,657,839,436,720,355 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printf("Before sort\n");
	for (int i = 0; i < n; i++)
		printf("%d\n", arr[i]);
	printf("After sort\n");
	radix_sort(arr, n);
	for (int i = 0; i < n; i++)
		printf("%d\n", arr[i]);
	return 0;
}
