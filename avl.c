#include<stdio.h>
#include<stdlib.h>
#include "avl.h"
#include "tree.h"

node * insert(node *T,int x, void* no_fig)
{
	if(T==NULL)
	{
		T=(node*)malloc(sizeof(node));
		T->data=x;
    T->no_fig = no_fig;
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(x > T->data)		// insert in right subtree
		{
			T->right=insert(T->right,x,no_fig);
			if(BF(T)==-2)
				if(x>T->right->data)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(x<T->data)
			{
				T->left=insert(T->left,x,no_fig);
				if(BF(T)==2)
					if(x < T->left->data)
						T=LL(T);
					else
						T=LR(T);
			}

		T->ht=height(T);

		return(T);
}

int height(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);

	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;

	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;

	if(lh>rh)
		return(lh);

	return(rh);
}

node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);

	return(y);
}

node * RR(node *T)
{
	T=rotateleft(T);
	return(T);
}

node * LL(node *T)
{
	T=rotateright(T);
	return(T);
}

node * LR(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);

	return(T);
}

node * RL(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}

int BF(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);

	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;

	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;

	return(lh-rh);
}

void preorder(node *T)
{
	if(T!=NULL)
	{
		printf("%d(Bf=%d)",T->data,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}

void inorder(node *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		printf("%d(Bf=%d)",T->data,BF(T));
		inorder(T->right);
	}
}


void print_tree(node* t, char* title) {
  printf("\n --> %s",title);
  print2DUtil(t,0);
  printf("\n <--\n");
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(node *root, int space){
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 3; i < space; i++)
        printf(" ");
    TAG* aux_node = (TAG*) root->no_fig;
    printf("%d, %s\n", root->data,nome_tipo(aux_node->fig->tipo));

    // Process left child
    print2DUtil(root->left, space);
}

void free_avl(node *T) {
  if (T) {
    free_avl(T->left);
    free_avl(T->right);
    free(T);
  }
}