#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define input_size 1000
typedef struct TreeNode
{
	int value;
	TreeNode * pLeft;
	TreeNode * pRight;
	TreeNode(int val = 0)
	{
		value = val;
		pRight = NULL;
		pLeft = NULL;
	}
}TreeNode;

void insert(TreeNode ** pRoot, int val)
{
	if (*pRoot == NULL)
		*pRoot = new TreeNode(val);
	else if ((*pRoot)->value <= val)
		insert(&((*pRoot)->pRight), val);
	else if ((*pRoot)->value > val)
		insert(&((*pRoot)->pLeft), val);
}

TreeNode *getBST(int * arr, int size)
{
	TreeNode *pRoot = NULL;
	for (int i = 0; i < size; i++)
		insert(&pRoot, arr[i]);
	return pRoot;
}

void inorder(TreeNode *pRoot) {
	if (pRoot &&pRoot->pLeft)
		inorder(pRoot->pLeft);
	if (pRoot)
		printf("%d ", pRoot->value);
	if (pRoot&&pRoot->pRight)
		inorder(pRoot->pRight);
}

int main() {
	int data_maxval = 10000;

	int input[input_size];
	for (int i = 0; i < input_size; i++) {
		input[i] = rand() % (data_maxval + 1);
	}
	TreeNode * pRoot = getBST(input, sizeof(input) / sizeof(int));
	inorder(pRoot);
}
