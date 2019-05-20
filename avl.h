typedef struct node
{
	int data;
  void* no_fig;
	struct node *left,*right;
	int ht;
}node;

node *insert(node *,int,void*);
void preorder(node *);
void inorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);

void print_tree(node* t, char* title);
void print2DUtil(node *root, int space);