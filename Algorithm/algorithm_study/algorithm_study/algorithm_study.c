#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1000001
int sorted[MAX];
int list[MAX];
void merge(int list[], int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	int k = left;
	int l;
	while (i <= mid&& j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) {
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	}
	else {
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	}
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}
int main() {
	
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &list[i]);
	}

	merge_sort(list, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf("%d\n", list[i]);
	}
	return 0;
}