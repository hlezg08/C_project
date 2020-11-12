#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 1000
#define true 1
#define false 0

typedef struct TreeNode {
	int weight;
	struct TreeNode *left_child;
	struct TreeNode *right_child;
} TreeNode;

typedef struct {
	TreeNode *ptree;
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// Initialization
void init(HeapType *h) {
	h->heap_size = 0;
}
int is_empty(HeapType *h) {
	if (h->heap_size == 0)
		return true;
	else
		return false;
}
void insert_min_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
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
	h->heap[parent] = temp;
	return item;
}

TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		exit(1);
	}
	node->left_child =left;
	node->right_child = right;
	return node;
}
// Binary tree removal
void destroy_tree(TreeNode *root)
{
	if (root == NULL) return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root);
}
// Huffman code generation
void huffman_tree(int freq[], int n)
{
	int i;
	TreeNode *node, *x;
	HeapType heap;
	element e, e1, e2;
	init(&heap);
	for (i = 0; i<n; i++) {
		node = make_tree(NULL, NULL);
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(&heap, e);
	}
	for (i = 1; i<n; i++) {
		// Delete two nodes with minimum values
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);
		// Merge two nodes
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(&heap, e);
	}
	e= delete_min_heap(&heap); // Final Huffman binary tree
	destroy_tree(e.ptree);
}
void main()
{
	int freq[] = { 15, 12, 8, 6, 4 };
	huffman_tree(freq, 5);
}