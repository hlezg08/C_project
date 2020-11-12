#include <string.h> 

#include <stdio.h> 
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS
#define KEY_SIZE    10    // 탐색키의 최대길이  
#define TABLE_SIZE    13    // 해싱 테이블의 크기=소수  
#define equal(e1,e2) (!strcmp(e1.key,e2.key)) // 문자열 비교 

typedef struct
{
	char key[KEY_SIZE];
} element;

typedef struct list
{
	element item;
	list *link;
}list;
list *hash_table[TABLE_SIZE];


// 문자로 된 탐색키를 숫자로 변환 
int transform(char *key)
{
	int number = 0;
	// 간단한 덧셈 방식 사용 자연수 생성 
	while (*key)
		number += *key++;
	return number;
}

// 제산 함수를 사용한 해싱 함수 
int hash_function(char *key)
{
	// 키를 자연수로 변환한 다음 테이블의 크기로 나누어 나머지를 반환 
	return transform(key) % TABLE_SIZE;
}

// 체인법을 이용하여 테이블에 키를 삽입 
void hash_chain_add(element item, list *ht[])
{
	int hash_value = hash_function(item.key);
	list *ptr;
	list *node_before = NULL, *node = ht[hash_value];
	for (; node; node_before = node, node = node->link) {
		if (equal(node->item, item)) {
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}
	ptr = (list *)malloc(sizeof(list));
	ptr->item = item;
	ptr->link = NULL;
	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}

// 체인법을 이용하여 테이블에 저장된 키를 탐색 
void hash_chain_find(element item, list *ht[])
{
	list *node;

	int hash_value = hash_function(item.key);
	for (node = ht[hash_value]; node; node = node->link) {
		if (!strcmp(node->item.key, item.key)) {
			printf("키를 찾았음\n");
			return;
		}
	}
	printf("키를 찾지못했음\n");
}

// 연결리스트 삭제 함수 
void hash_chain_delete(element item, list *ht[])
{
	list *node;
	list *before_node = NULL;
	int hash_value = hash_function(item.key);

	for (node = ht[hash_value]; node; before_node = node, node = node->link)
	{
		if (!strcmp(node->item.key, item.key))
		{
			if (node->link != NULL)
				before_node->link = node->link; // 다음 노드를 연결 

			free(node);
			printf("삭제 완료");
			return;
		}

	}
	printf("키를 찾지못했음\n");
}

// 해싱 테이블의 내용을 출력 
void hash_chain_print(list *ht[])
{
	list *node;
	int i;
	for (i = 0; i<TABLE_SIZE; i++) {
		printf("[%d]->", i);
		for (node = ht[i]; node; node = node->link) {
			printf("%s->", node->item.key);
		}
		printf("\n");
	}
}

// 해싱 테이블을 사용한 예제  
int main()
{
	element tmp;
	int op;
	while (1) {
		printf("원하는 연산을 입력하시오(0=입력, 1=삭제, 2=탐색, 3=종료)=");
		scanf_s("%d", &op);
		if (op == 3) break;
		printf("키를 입력하시오=");
		scanf_s("%s", tmp.key, sizeof(tmp.key));
		if (op == 0) {
			hash_chain_add(tmp, hash_table);
		}
		else if (op == 1)
		{
			hash_chain_delete(tmp, hash_table);
		}
		else if (op == 2)
		{
			hash_chain_find(tmp, hash_table);
		}

		hash_chain_print(hash_table);
	}

	return 0;
}