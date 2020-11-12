#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1 //TRUE와 FALSE 식별자 선언

typedef int element;
typedef struct {
	element data;
	struct ListNode* link;
}ListNode; //ListNode구조체 생성

typedef struct {
	ListNode* head; //Head pointer
	ListNode *tail; //Tail pointer
	int length; // # of nodes
}ListType;
ListType list1; 

void init(ListType *list) {
	if (list == NULL)
		return;

	list->length = 0;
	list->head = NULL;
} //List 초기화

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
} //error 메시지 출력하는 함수

int is_empty(ListType *list) {
	return list->length == 0;
} //list안에 아무것도 없을때 개수가 0임을 반환

int get_length(ListType *list) {
	return list->length;
} //list의 data개수 반환시키는 함수

void insert_node(ListNode** phead, ListNode* p, ListNode* new_node) {
	if (*phead == NULL) {
		*phead = new_node;
		(*phead)->link = NULL;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
} //node 값을 삽입하는 함수

void remove_node(ListNode** phead, ListNode* p, ListNode* removed) {
	if (*phead == NULL) return;
	if (p == NULL) {
		*phead = (ListNode*)(*phead)->link;
	}
	else {
		p->link = removed->link;
	}
	free(removed); 
} //node 값을 삭제하는 함수

ListNode* get_node_at(ListType *list, int pos) {
	if (list->head == NULL) return NULL;
	else if (pos < 0 || pos > list->length) return NULL;

	ListNode *p = list->head;
	int i;
	for (i = 0; i<pos; i++)
		p = (ListNode*)p->link;
	return p;
}

void add(ListType *list, int pos, element data) {
	if (pos < 0 || pos > list->length) return;

	ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
	new_node->data = data;
	new_node->link = NULL;

	ListNode *p;
	p = get_node_at(list, pos - 1);
	insert_node(&(list->head), p, new_node);
	list->length++;
} //data 추가하는 함수

void add_last(ListType* list, element data) {
	add(list, get_length(list), data);
}

void add_first(ListType* list, element data) {
	add(list, 0, data);
}

void delete(ListType *list, int pos) {
	if (is_empty(list) || pos > list->length) return;
	if (list->head == NULL) return;

	ListNode *p = get_node_at(list, pos - 1);
	remove_node(&(list->head), p, p != NULL ? (ListNode*)p->link : NULL);
	list->length--;
}//data값 삭제하는 함수

void delete_last(ListType* list) {
	delete(list, get_length(list)-1);
}

void delete_first(ListType* list) {
	delete(list, 0);
}
element get_entry(ListType *list, int pos) {
	ListNode *p;
	if (pos >= list->length) error("Position error");
		p = get_node_at(list, pos);
	return p->data;
}

void display(ListType *list) {
	int i;
	ListNode *p = list->head;
	printf("(");
	for (i = 0; i<get_length(list); i++) {
		printf("%d ", p->data);
		p = (ListNode*)p->link;
	}
	printf(")\n");
} //list 출력함수

int is_in_list(ListType *list, element item) {
	ListNode *p = list->head;
	while (p) {
		if (p->data == item)
			return TRUE;
		p = (ListNode*)p->link;
	}
	return FALSE;
} //특정값이 list안에 있는지 판별하는 함수

int main() {
	ListType list1;
	init(&list1);
	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);

	delete(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);

	printf("%s\n", is_in_list(&list1, 20) == TRUE ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));
}