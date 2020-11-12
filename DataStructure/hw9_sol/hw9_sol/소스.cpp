#include <string.h> 

#include <stdio.h> 
#include <stdlib.h> 
#define _CRT_SECURE_NO_WARNINGS
#define KEY_SIZE    10    // Ž��Ű�� �ִ����  
#define TABLE_SIZE    13    // �ؽ� ���̺��� ũ��=�Ҽ�  
#define equal(e1,e2) (!strcmp(e1.key,e2.key)) // ���ڿ� �� 

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


// ���ڷ� �� Ž��Ű�� ���ڷ� ��ȯ 
int transform(char *key)
{
	int number = 0;
	// ������ ���� ��� ��� �ڿ��� ���� 
	while (*key)
		number += *key++;
	return number;
}

// ���� �Լ��� ����� �ؽ� �Լ� 
int hash_function(char *key)
{
	// Ű�� �ڿ����� ��ȯ�� ���� ���̺��� ũ��� ������ �������� ��ȯ 
	return transform(key) % TABLE_SIZE;
}

// ü�ι��� �̿��Ͽ� ���̺� Ű�� ���� 
void hash_chain_add(element item, list *ht[])
{
	int hash_value = hash_function(item.key);
	list *ptr;
	list *node_before = NULL, *node = ht[hash_value];
	for (; node; node_before = node, node = node->link) {
		if (equal(node->item, item)) {
			fprintf(stderr, "�̹� Ž��Ű�� ����Ǿ� ����\n");
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

// ü�ι��� �̿��Ͽ� ���̺� ����� Ű�� Ž�� 
void hash_chain_find(element item, list *ht[])
{
	list *node;

	int hash_value = hash_function(item.key);
	for (node = ht[hash_value]; node; node = node->link) {
		if (!strcmp(node->item.key, item.key)) {
			printf("Ű�� ã����\n");
			return;
		}
	}
	printf("Ű�� ã��������\n");
}

// ���Ḯ��Ʈ ���� �Լ� 
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
				before_node->link = node->link; // ���� ��带 ���� 

			free(node);
			printf("���� �Ϸ�");
			return;
		}

	}
	printf("Ű�� ã��������\n");
}

// �ؽ� ���̺��� ������ ��� 
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

// �ؽ� ���̺��� ����� ����  
int main()
{
	element tmp;
	int op;
	while (1) {
		printf("���ϴ� ������ �Է��Ͻÿ�(0=�Է�, 1=����, 2=Ž��, 3=����)=");
		scanf_s("%d", &op);
		if (op == 3) break;
		printf("Ű�� �Է��Ͻÿ�=");
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