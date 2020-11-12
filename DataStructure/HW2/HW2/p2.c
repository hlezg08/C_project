#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node* next;
}; //Node����ü ����

void printList(struct Node* head){
	struct Node* ptr = head;
	printf("{");
	while (ptr)
	{
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
	printf("}\n");
} //List�� ����ϴ� �Լ�

void push(struct Node** head, int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
} //List�� data �ִ� �Լ�

void MoveNode(struct Node** dest, struct Node** source)
{
	if (*source == NULL)
		return;
	struct Node* newNode = *source;    
	*source = (*source)->next;   
	newNode->next = *dest;        
	*dest = newNode;      
} //Node �ű�� �Լ�

struct Node* SortedMerge(struct Node* a, struct Node* b)
{
	struct Node p;
	p.next = NULL;
	struct Node* tail = &p;

	while (1){
		if (a == NULL){
			tail->next = b;
			break;
		}
		else if (b == NULL){
			tail->next = a;
			break;
		}
		if (a->data <= b->data)
			MoveNode(&(tail->next), &a);
		else
			MoveNode(&(tail->next), &b);
		tail = tail->next;
	}
	return p.next;
} //Merge function�� �����ϰ� ascending order�� �����ϴ� �Լ�

int main(void)
{
	struct Node *a = NULL, *b = NULL;
	push(&a, 25);
	push(&a, 20);
	push(&a, 15);
	push(&a, 10);
	push(&a, 5);
	push(&a, 2);
	push(&a, 1);

	push(&b, 30);
	push(&b, 18);
	push(&b, 15);
	push(&b, 8);
	push(&b, 7);
	push(&b, 3);

	printf("a= ");
	printList(a);

	printf("b= ");
	printList(b);

	struct Node* c = SortedMerge(a, b);
	printf("c= ");
	printList(c);

}