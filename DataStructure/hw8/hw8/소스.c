#include <stdio.h>

#define MAX_ELEMENT 200
#define true 1
#define false 0
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
typedef struct{
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType *h) {
	h->heap_size = 0;
}
int is_empty(HeapType *h) {
	if (h->heap_size == 0)
		return true;
	else
		return false;
}

void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);
	// The process of comparing with the parent node as it traverses the tree
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}
void build_min_heap(HeapType *h)
{
	int half_size = h->heap_size / 2;
	for (int i = half_size; i >= 1; i--)
	{
		element temp = h->heap[i];
		int parent = i;
		int child = 2 * i;
		while (child <= h->heap_size)
		{
			if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key)
				child++;
			if (temp.key <= h->heap[child].key) break;
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		h->heap[parent] =temp;
	}
}
void decrease_key_min_heap(HeapType *h, int i, element item) {
	element temp;
	if (item.key >= h->heap[i].key) {
		fprintf(stderr, "new key is not larger than current key");
		exit(1);
	}
	h->heap[i].key = item.key;
	while ((i > 1) && (h->heap[i / 2].key > h->heap[i].key)) {
		SWAP(h->heap[i].key, h->heap[i / 2].key, temp.key);
		i /=2;

		if ((h->heap[i].key > h->heap[2 * i].key)) {
			SWAP(h->heap[i].key, h->heap[2 * i].key, temp.key);
		}
		if ((h->heap[i].key > h->heap[2 * i + 1].key)) {
			SWAP(h->heap[i].key, h->heap[2 * i+1].key, temp.key);
		}
	}
	
	
}
void print_heap(HeapType *h) {
	for (int i = 1; i < h->heap_size+1; i++) {
		printf("%d ", h->heap[i]);
	}
}
int main() {
	element e1 = {1}, e2 = {4}, e3 = { 2}, e4 = { 7}, e5 = {5};
	element e6 = {3}, e7 = {3}, e8 = {7}, e9 = {8}, e10 = {9};
	element e11 = { 3 };
	HeapType heap;
	init(&heap);

	insert_min_heap(&heap, e1);
	insert_min_heap(&heap, e2);
	insert_min_heap(&heap, e3);
	insert_min_heap(&heap, e4);
	insert_min_heap(&heap, e5);
	insert_min_heap(&heap, e6);
	insert_min_heap(&heap, e7);
	insert_min_heap(&heap, e8);
	insert_min_heap(&heap, e9);
	insert_min_heap(&heap, e10);

	decrease_key_min_heap(&heap,4,e11);
	build_min_heap(&heap);
	print_heap(&heap);
}