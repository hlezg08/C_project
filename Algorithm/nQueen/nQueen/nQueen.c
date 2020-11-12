#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int col[15];
int n;
int result = 0;

typedef enum {
	false = 0,
	true = 1
}bool;

bool promising(int i) {
	int j = 1;
	while (j<i&&true) {
		if (col[i] == col[j] || abs(col[i] - col[j]) == abs(i - j)) {
			return false;
		}
		j++;
	}
	return true;
}
void queens(int i) {
	int j;
	if (promising(i)) {
		if (i == n) {
			result += 1;
			for (j = 1; j <= n; j++) {
				printf("%d ", col[j]);
			}
			printf("\n");		
		}
		else {
			for (j = 1; j <= n; j++) {
				col[i + 1] = j;
				queens(i + 1);
			}
		}
	}
	
}

int main() {
	scanf("%d", &n);
	queens(0);
	return 0;
}