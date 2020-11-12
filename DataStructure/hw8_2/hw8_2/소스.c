#include<stdio.h>
#define MAX_VERTICES 8
#define INF 1000L
#define FALSE 0
#define TRUE 1
#define MAX_ELEMENT 200
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
int weight[MAX_VERTICES][MAX_VERTICES] =
{ { 0,3,INF,INF,INF,INF,INF,14 },
{ 3,0,8,INF,INF,INF,INF,10 },
{ INF,8,0,15,2,INF,INF,INF },
{ INF,INF,15,0,INF,INF,INF,INF },
{ INF,INF,2,INF,0,9,4,5 },
{ INF,INF,INF,INF,9,0,INF,INF },
{ INF,INF,INF,INF,4,INF,0,6 },
{ 14,10,INF,INF,5,INF,6,0 } };
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];
typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void build_min_heap(HeapType *h)
{
	int half_size = h->heap_size / 2;
	for (int i = half_size; i >= 1; i--)//leaf Á¦¿ÜÇÑ node
	{
		element temp = h->heap[i];
		int parent = i;
		int child = 2 * i;
		while (child <= h->heap_size)
		{
			if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key)
				child++;
			if (temp.key <= h->heap[child].key) break;
			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}
		h->heap[parent] =temp;
	}
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	} 
	h->heap[parent] =temp;
	return item;
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
		i /= 2;

		if ((h->heap[i].key > h->heap[2 * i].key)) {
			SWAP(h->heap[i].key, h->heap[2 * i].key, temp.key);
		}
		if ((h->heap[i].key > h->heap[2 * i + 1].key)) {
			SWAP(h->heap[i].key, h->heap[2 * i + 1].key, temp.key);
		}
	}
}
void prim(int s,int n) {
	int i,u,v;
	HeapType *heap;
	for (u = 0; u < n; u++) {
		heap->heap[u].key=INF;
		selected[u] = FALSE;
	}
	heap->heap[s].key= 0;

	build_min_heap(&heap);
	for (i = 0; i < n; i++) {
		u = delete_min_heap(&heap).key;
		print("%d ", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF) {
				if (!selected[v] && weight[u][v] < dist[v])
					dist[v] = weight[u][v];
			}
		}
	}
}