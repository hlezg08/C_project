#include <stdio.h>

int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
} //�ִ��� ����ϴ� �Լ�

void counting_sort(int arr[], int n, int exp)
{
	int output[100]; //���ĵ� array
	int i, count[10] = { 0 }; //count array�� �� ���ڸ��� ��Ÿ�� �󵵼�(histogram)(0~9)

	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++; //histogram�� �ϳ��� ����

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1]; //���� histogram �����

	for (i = n - 1; i >= 0; i--) //�迭 �� index�������� �����ϱ�
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i]; //arr�� �ִ� ���ڸ� output �迭�� ����ֱ�
		count[(arr[i] / exp) % 10]--; //histogram���� �ϳ��� ����
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i]; 
}

void radix_sort(int arr[], int n)
{
	int max = getMax(arr, n);
	int exp;
	for (exp = 1; max / exp > 0; exp *= 10)
		counting_sort(arr, n, exp); //1�� �ڸ�,10�� �ڸ�,100�� �ڸ�...��
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
