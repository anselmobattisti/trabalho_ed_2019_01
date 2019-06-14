typedef struct no{
    int info;
    struct no*  esq;
    struct no*  dir;
    int alt;
    void* no_fig;
}no;

void print_tree(no* t, char* title);
void free_avl(no* t);
no* insere(int e, no* t, void* no_fig);
void print2DUtil(no *root, int space);
void print_tree_ordenado(no* t);

void gerar_dot_arvore_avl(no* t);
void gerar_dot_arvore_avl_no(no* t, int pai);