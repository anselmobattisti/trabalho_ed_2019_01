#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "tree.h"

void free_avl(no* t){
    if( t != NULL ){
        free_avl( t->esq );
        free_avl( t->dir );
        free( t );
    }
}

/*
no* busca(int e, no* t){
    if( t == NULL ) return NULL;
    if( e < t->info ) return busca( e, t->esq );
    if( e > t->info ) return busca( e, t->dir );
    return t;
}
*/

static int calc_alt( no* n ){
    if( n == NULL ) return -1;
    return n->alt;
}


static int max( int l, int r){
    return l > r ? l: r;
}


static no* rot_dir( no* k2 ){
    no* k1 = NULL;
    k1 = k2->esq;
    k2->esq = k1->dir;
    k1->dir = k2;
    k2->alt = max( calc_alt( k2->esq ), calc_alt( k2->dir ) ) + 1;
    k1->alt = max( calc_alt( k1->esq ), k2->alt ) + 1;
    return k1; /* nova raiz */
}


static no* rot_esq( no* k1 ){
    no* k2;
    k2 = k1->dir;
    k1->dir = k2->esq;
    k2->esq = k1;
    k1->alt = max( calc_alt( k1->esq ), calc_alt( k1->dir ) ) + 1;
    k2->alt = max( calc_alt( k2->dir ), k1->alt ) + 1;
    return k2;  /* nova raiz */
}


static no* rot_esq_dir( no* k3 ){
    k3->esq = rot_esq( k3->esq );
    return rot_dir( k3 );
}


static no* rot_dir_esq( no* k1 ){
    k1->dir = rot_dir( k1->dir );
    return rot_esq( k1 );
}

no* insere(int e, no* t, void* no_fig){
    if( t == NULL ){
        t = (no*)malloc(sizeof(no));
        if( t == NULL ){
            fprintf (stderr, "Out of memory!!! (insere)\n");
            exit(1);
        }
        else{
            t->info = e;
            t->alt = 0;
            t->no_fig = no_fig;
            t->esq = t->dir = NULL;
        }
    }
    else if( e < t->info ){
        t->esq = insere( e, t->esq , no_fig);
        if( calc_alt( t->esq ) - calc_alt( t->dir ) == 2 )
            if( e < t->esq->info )
                t = rot_dir( t );
            else
                t = rot_esq_dir( t );
    }
    else if( e > t->info ){
        t->dir = insere( e, t->dir, no_fig);
        if( calc_alt( t->dir ) - calc_alt( t->esq ) == 2 )
            if( e > t->dir->info )
                t = rot_esq( t );
            else
                t = rot_dir_esq( t );
    }
    t->alt = max( calc_alt( t->esq ), calc_alt( t->dir ) ) + 1;
    return t;
}

int FB(no *T){
    int lh,rh;
    if(T==NULL) return(0);
    if(T->esq==NULL) lh=0;
    else lh=1+T->esq->alt;
    if(T->dir==NULL) rh=0;
    else rh=1+T->dir->alt;
    return(lh-rh);
}

void imprime_aux(no *a, int andar){
  if(a){
      int j;
      imprime_aux(a->esq,andar+1);
      for(j=0; j<=andar; j++) printf("   ");

      TAG* aux_node = (TAG*) a->no_fig;
      printf("%d (%s)\n", a->info, nome_tipo(aux_node->fig->tipo));
      //printf("%d\n", a->info);

      imprime_aux(a->dir,andar+1);
  }
}


void imprime(no *a){
  imprime_aux(a, 1);
}

static int min( int l, int r){
    return l < r ? l: r;
}

void print_tree(no* t, char* title) {
  printf("\n --> %s\n",title);
  imprime_aux(t,0);
  printf("\n <--\n");
}

void print_tree_ordenado(no* t) {
    if(t){
        print_tree_ordenado(t->esq);
        printf("%d ",t->info);
        print_tree_ordenado(t->dir);
    }
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(no *root, int space){
    // Base case
    if (root == NULL)
        return;
    // Increase distance between levels
    space += 3;
    // Process right child first
    print2DUtil(root->dir, space);
    // Print current node after space
    // count
    //printf("\n");
    for (int i = 3; i < space; i++)
        printf(" -");
    TAG* aux_node = (TAG*) root->no_fig;
    printf("> %d (%s)\n", root->info, nome_tipo(aux_node->fig->tipo));
    // Process left child
    print2DUtil(root->esq, space);
}

void gerar_dot_arvore_avl(no* t) {
  printf("\nÁrvore no formato DOT.\n");
  printf("-----------------------\n");
  printf("Para visualizar acesse: http://www.webgraphviz.com/ e cole as linhas abaixo.\n");
  printf("-----------------------\n\n");
  printf("digraph  G { \n");

  TAG* aux_node = (TAG*) t->no_fig;
  printf("\n%d[shape=%s]", t->info, nome_tipo_grafico(aux_node->fig->tipo));
  gerar_dot_arvore_avl_no(t, t->info);
  printf("\n}\n\n\n");
}

void gerar_dot_arvore_avl_no(no* t, int pai) {

  if (!t) return;

  if (t->info != pai) {
    TAG* aux_node = (TAG*) t->no_fig;
    printf("\n%d[shape=%s]",t->info,nome_tipo_grafico(aux_node->fig->tipo));
    printf("\n%d -> %d ",pai, t->info);
  }

  gerar_dot_arvore_avl_no(t->esq, t->info);
  gerar_dot_arvore_avl_no(t->dir, t->info);
}