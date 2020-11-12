#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define INF 987654321; 

int n, m; 
int start, end; 
int W[1002][1002]; 
int length[1002]; 
int touch[1002]; 
int F[1002]; 

void dijkstra() {
	int min; 
	int vnear = 0; 
	length[start] = 0; 
	for (int i = 1; i <= n; i++) {
		touch[i] = 1; 
	}
	for (int i = 1; i <= n; i++) {
		min = INF;
		for (int j = 1; j <= n; j++) {
			if (F[j] == 0 && length[j] <min) {
				min = length[j];
				vnear = j; 
			}
		}
		F[vnear] = 1;
		
		for (int j = 1; j <= n; j++) {
			
			if (length[j]>length[vnear] + W[vnear][j] && W[vnear][j] != min) {                 
				length[j] = length[vnear] + W[vnear][j];
				
				touch[j] = vnear; 
			}
		}
	}

}

int main() {
	scanf("%d %d", &n, &m); 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			W[i][j] = INF; 
		}
		length[i] = INF; 
		F[i] = 0; 
	}

	for (int i = 1; i <= m; i++) { 
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		
		if (W[a][b] > c) W[a][b] = c;
		
	}
	scanf("%d", &start); 
	scanf("%d", &end);
	dijkstra(); 
	printf("%d", length[end]);			
	
	return 0; 
}


