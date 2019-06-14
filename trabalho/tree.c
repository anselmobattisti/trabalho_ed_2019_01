#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "avl.h"

TAG* insere_filho(TAG *t, int cod, void* fig) {
  // cria a nova árvore
  TAG *nova_arvore = (TAG*) malloc(sizeof(TAG));
  nova_arvore->cod = cod;
  nova_arvore->fig = fig;
  nova_arvore->f = NULL;
  nova_arvore->i = NULL;

  // olha para o primeiro filho
  TAG *aux = t->f;
  TAG *ultimo_filho = NULL;
  while (aux) {
    ultimo_filho = aux;
    aux = aux->i; // navega pelos irmãos
  }
  // se for o primeiro filho do nó
  if (ultimo_filho == NULL) {
    // ver o nó vazio
    // printf("vazia");
    // imprimir_status_arvore(t);
    // é o primeiro filho
    t->f = nova_arvore;
  } else {
    // ver quem é o último
    // imprimir_status_arvore(t);
    // imprimir_status_arvore(ultimo_filho);
    // printf("Cod: %d",cod);
    ultimo_filho->i = nova_arvore;
    //imprimir_status_arvore(t->f);
  }
  return nova_arvore;
  // return t;
}

TAG* busca(TAG* t, int cod) {
  if (t->cod == cod) {
    return t;
  }
  if (t->f) {
    TAG* aux = busca(t->f,cod);
    if (aux)
      return aux;
  }
  if (t->i) {
    TAG* aux = busca(t->i,cod);
    if (aux)
      return aux;
  }
}

TAG* buscaPai(TAG* t, int cod) {
  if (t->f) {
    if(t->f->cod == cod){
      printf("Entrou na funcao busca pai. Pai eh %d\n\n", cod);
      return t;
    }
    TAG* aux = buscaPai(t->f,cod);
    if (aux)
      return aux;
  }
  if (t->i) {
    TAG* aux = buscaPai(t->i,cod);
    if (aux)
      return aux;
  }
}
/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  NÃO APAGAR, ESSA FUNÇÃO TBM FUNCIONA
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
TAG* busca_it(TAG* t, int cod) {
  if (t->cod == cod) {
    return t;
  }
  TAG* aux = t->f; // acessa o primeiro filho
  while (aux) {
    if (aux->cod == cod) {
      return aux;
    }
    // caso um nó tenha filhos então é necessário verificar
    // se o elemento que está sendo buscado não está ali dentro
    if (tem_filhos(aux->f)) {
      TAG* x = busca(aux,cod);
      if (x) return x;
    }

    // esse cara nunca está sendo executado
    aux = aux->i; // navega pelos irmãos
  }
}

TAG* cria_arvore(int cod, TDADO* fig) {
  TAG *aux = (TAG*) malloc(sizeof(TAG));
  aux->f = NULL;
  aux->i = NULL;
  aux->cod = cod;
  aux->fig = fig;
  return aux;
}

TDADO *cria_trapezio(float b1, float b2, float h) {
  TTRAPEZIO *t = (TTRAPEZIO*) malloc(sizeof(TTRAPEZIO));
  t->b1 = b1;
  t->b2 = b2;
  t->h = h;
  TDADO *d = (TDADO*) malloc(sizeof(TDADO));
  d->tipo = TIPO_TRAPEZIO;
  d->fig = t;
  d->area = ((b1+b2)/2)*h;
  return d;
}

TDADO *cria_triangulo(float b, float a) {
  TTRIANGULO *t = (TTRIANGULO*) malloc(sizeof(TTRIANGULO));
  t->b = b;
  t->a = a;
  TDADO *d = (TDADO*) malloc(sizeof(TDADO));
  d->tipo = TIPO_TRIANGULO;
  d->fig = t;
  d->area = (b*a)/2;
  return d;
}

TDADO *cria_retangulo(float l, float a) {
  TRETANGULO *r = (TRETANGULO*) malloc(sizeof(TRETANGULO));
  r->l = l;
  r->a = a;
  TDADO *d = (TDADO*) malloc(sizeof(TDADO));
  d->tipo = TIPO_RETANGULO;
  d->fig = r;
  d->area = l*a;
  return d;
}

TDADO *cria_quadrado(float l) {
  TQUADRADO *q = (TQUADRADO*) malloc(sizeof(TQUADRADO));
  q->l = l;
  TDADO *d = (TDADO*) malloc(sizeof(TDADO));
  d->tipo = TIPO_QUADRADO;
  d->fig = q;
  d->area = l*l;
  return d;
}

TDADO *cria_circulo(float r) {
  TCIRCULO *c = (TCIRCULO*) malloc(sizeof(TCIRCULO));
  c->r = r;
  TDADO *d = (TDADO*) malloc(sizeof(TDADO));
  d->tipo = TIPO_CIRCULO;
  d->fig = c;
  d->area = 3.14*(r*r);
  return d;
}

TAG* insere_filho_circulo(TAG *t, int cod, float r) {
  if (!t) return NULL;
  TDADO *c = cria_circulo(r);
  return insere_filho(t,cod,c);
}

TAG* insere_filho_trapezio(TAG *t, int cod, float b1, float b2, float l) {
  if (!t) return NULL;
  TDADO *trap = cria_trapezio(b1, b2, l);
  return insere_filho(t,cod,trap);
}

TAG* insere_filho_quadrado(TAG *t, int cod, float l) {
  if (!t) return NULL;
  TDADO *q = cria_quadrado(l);
  return insere_filho(t,cod,q);
}

TAG* insere_filho_retangulo(TAG *t, int cod, float l, float a) {
  if (!t) return NULL;
  TDADO *r = cria_retangulo(l,a);
  return insere_filho(t,cod,r);
}

TAG* insere_filho_triangulo(TAG *t, int cod, float b, float a) {
  if (!t) return NULL;
  TDADO *tri = cria_triangulo(b,a);
  return insere_filho(t,cod,tri);
}

TAG* altera_filho_quadrado(TAG *t, int cod, float l) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  if (!aux) return NULL;
  TDADO *tc = cria_quadrado(l);
  free(aux->fig);
  aux->fig = tc;
  return aux;
}

TAG* altera_filho_circulo(TAG *t, int cod, float r) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  if (!aux) return NULL;
  TDADO *tc = cria_circulo(r);
  free(aux->fig);
  aux->fig = tc;
  return aux;
}

TAG* altera_filho_retangulo(TAG *t, int cod, float l, float a) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  if (!aux) return NULL;
  TDADO *tc = cria_retangulo(l,a);
  free(aux->fig);
  aux->fig = tc;
  return aux;
}

TAG* altera_filho_triangulo(TAG *t, int cod, float b, float a) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  if (!aux) return NULL;
  TDADO *tc = cria_triangulo(b,a);
  free(aux->fig);
  aux->fig = tc;
  return aux;
}

TAG* altera_filho_trapezio(TAG *t, int cod, float b1, float b2, float h) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  if (!aux) return NULL;
  TDADO *tc = cria_trapezio(b1,b2,h);
  free(aux->fig);
  aux->fig = tc;
  return aux;
}

int tem_filhos(TAG *t) {
  if (!t) return 0;
  if (!t->i) return 1;

  return tem_filhos(t->i)+1;
}

int tem_irmaos(TAG* t) {
  if (!t->i) return 0;
  return 1;
}

char* nome_tipo(int tipo) {
  switch (tipo){
    case TIPO_QUADRADO:
      return "Quadrado";
      break;
    case TIPO_CIRCULO:
      return "Círculo";
      break;
    case TIPO_RETANGULO:
      return "Retângulo";
      break;
    case TIPO_TRIANGULO:
      return "Triângulo";
      break;
    case TIPO_TRAPEZIO:
      return "Trapézio";
      break;
    default:
      break;
  }
}

char* nome_tipo_grafico(int tipo) {
  switch (tipo){
    case TIPO_QUADRADO:
      return "square";
      break;
    case TIPO_CIRCULO:
      return "circle";
      break;
    case TIPO_RETANGULO:
      return "rect";
      break;
    case TIPO_TRIANGULO:
      return "triangle";
      break;
    case TIPO_TRAPEZIO:
      return "trapezium";
      break;
    default:
      return "erro";
      break;
  }
}

float area_filhos(TAG *t) {
  float area_total = 0;
  TAG *aux = t->f;
  while(aux) {
    area_total += aux->fig->area;
    aux = aux->i;
  }
  return area_total;
}

/*
  Tem que passar o busca(t,3)->f

  mesmo caso da impressão, se não fizer isso vai pegar os
  irmaos do nó de origem, quando na verdade só se quer
  os nós internos
*/
float area_total (TAG* t) {
  if (!t) return 0;
  float at = t->fig->area;
  if (t->f) {
    at += area_total(t->f);
  }

  if (t->i) {
    at += area_total(t->i);
  }

  return at;
}

void imprimir_status_filhos(TAG *t) {
  if (!t) return;
  printf("\n===> PAI");
  imprimir_status_arvore(t);
  TAG* aux = t->f;
  int k = 1;
  while(aux) {
    printf("\n===> Filho (%d)\n",k);
    imprimir_status_arvore(aux);
    aux = aux->i;
    k++;
  }
}

char* dimensoes_tipo(TDADO* fig) {
  char* s = (char*) malloc(sizeof(char)*100);
  TQUADRADO *aux_q;
  TCIRCULO *aux_c;
  TRETANGULO *aux_r;
  TTRIANGULO *aux_tri;
  TTRAPEZIO *aux_tra;
  switch (fig->tipo){
      case TIPO_QUADRADO:
        aux_q = fig->fig;
        sprintf(s, "L: %.2f", aux_q->l);
        return s;
        break;
      case TIPO_CIRCULO:
        aux_c = fig->fig;
        sprintf(s, "R: %.2f", aux_c->r);
        return s;
        break;
      case TIPO_RETANGULO:
        aux_r = fig->fig;
        sprintf(s, "L1: %.2f, L2: %.2f", aux_r->l, aux_r->a);
        return s;
        break;
      case TIPO_TRIANGULO:
        aux_tri = fig->fig;
        sprintf(s, "B: %.2f, A: %.2f", aux_tri->b, aux_tri->a);
        return s;
        break;
      case TIPO_TRAPEZIO:
        aux_tra = fig->fig;
        sprintf(s, "B1: %.2f, B2: %.2f, A: %.2f", aux_tra->b1, aux_tra->b2, aux_tra->h);
        return s;
        break;
      default:
        break;
    }
}

void imprimir_status_arvore(TAG *t) {
  if (!t) return;
  printf("\n+-------------------------------------------------+");
  printf("\n| Cod               : %d",t->cod);
  printf("\n| Tipo              : %s",nome_tipo(t->fig->tipo));
  printf("\n| Dimensões         : %s",dimensoes_tipo(t->fig));
  printf("\n| N. Filhos         : %d",tem_filhos(t->f));
  printf("\n| N. Descendentes   : %d",num_descendentes(t->f));
  printf("\n| Área do Nó        : %.2f",t->fig->area);
  printf("\n| Área Descendentes : %.2f", area_total(t->f));
  printf("\n| Área Total        : %.2f",t->fig->area+area_total(t->f));
  printf("\n| Área Apenas Filhos: %.2f", area_filhos(t));
  printf("\n+-------------------------------------------------+\n");
}

void imprime_semi_bonito(TAG *t) {
  printf("\nÁrvore Completa\n----------------\n");
  imprimir_como_dir(t, 1, 0);
  printf("----------------\nTotal de nós: %d\n----------------\n",num_descendentes(t->f)+1);
}

/*
  @todo: ainda não esta legal
*/
void imprimir_como_dir(TAG *t, int nivel, int nao_imprimir) {
  if (!t) return;
  if (t->cod == nao_imprimir) return;
  int passo = 2;
  for (int i = 0; i < nivel; i++) {
    printf("-");
  }

  if (t->cod != nao_imprimir) {
    printf("> %d (%s,%.2f)\n",t->cod,nome_tipo(t->fig->tipo), t->fig->area);
  }

  TAG* aux = t->f; // acessa o primeiro filho

  while (aux) {
    //if (aux->cod == nao_imprimir) return;
    if (tem_filhos(aux->f) && aux->cod != nao_imprimir) {
      imprimir_como_dir(aux,nivel+passo, nao_imprimir);
    } else {
      if (aux->cod == nao_imprimir) {
        nivel -= passo;
      }
      for (int i = 0; i < nivel + passo; i++) {
        printf("-");
      }
      if (aux->cod != nao_imprimir) {
        printf("> %d (%s,%.2f)\n",aux->cod,nome_tipo(aux->fig->tipo), t->fig->area);
      }
    }
    aux = aux->i; // navega pelos irmãos
  }
}

/*
  Recebe como parâmetro primeiro filho de um nó.
  Se quero saber quantos nós estão abaixo do nó 2
  é necessário achar o nós busca(t,2)->f para pegar
  os seus filhos

  O nó PAI não é contato;
*/
int num_descendentes(TAG *t) {
  if (!t) return 0;
  int k = 1;
  if (t->i)
    k += num_descendentes(t->i);
  if (t->f)
    k += num_descendentes(t->f);

  return k;
}

/*
  Só a impressão que muda
*/
void imprime_arvore_generica_como_binaria(TAG* t, char* title) {
  printf("\n --> %s\n",title);
  print2DUtilGen(t,0);
  printf("\n <--\n");
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtilGen(TAG *root, int space){
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 3;

    // Process right child first
    print2DUtilGen(root->f, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 3; i < space; i++)
        printf("-");
    //TAG* aux_node = (TAG*) root->fig;
    printf("->%d\n", root->cod);

    // Process left child
    print2DUtilGen(root->i, space);
}

void gerar_dot_arvore_generica(TAG* t) {
  printf("\nÁrvore no formato DOT.\n");
  printf("-----------------------\n");
  printf("Para visualizar acesse: http://www.webgraphviz.com/ e cole as linhas abaixo.\n");
  printf("-----------------------\n\n");
  printf("digraph  G {  subgraph cluster_legend { {rank=cluster_legend}label = \"Legenda\";N1 [shape=square]N2 [shape=square]I  [shape=square]F  [shape=square]{ rank=same N1 F}{ rank=same N2 I}N1->F [label=\"  Pai\" color=\"red\"]N2->I [label=\"  Irmão\" color=\"blue\"]}\n");

  printf("\n%d[shape=%s]",t->cod,nome_tipo_grafico(t->fig->tipo));
  gerar_dot_arvore_generica_no(t->f, t->cod, 0);
  printf("\n}\n\n\n");
}

void gerar_dot_arvore_generica_no(TAG* t, int pai, int tipo) {

  if (!t) return;

  char* cor = "[color=\"blue\"];";

  if (!tipo)
    cor = "[color=\"red\"];";

  printf("\n%d[shape=%s]",t->cod,nome_tipo_grafico(t->fig->tipo));

  printf("\n%d -> %d  %s",pai, t->cod,cor);

  gerar_dot_arvore_generica_no(t->i, t->cod, 1);
  gerar_dot_arvore_generica_no(t->f, t->cod, 0);
}

void destruir_arvore(TAG* t){
  if(t){
    destruir_arvore(t->f);
    destruir_arvore(t->i);
    free(t->fig->fig);
    free(t->fig);
    free(t);
  }
}

//Nao pode remover raiz. Se cod filho e cod pai sao iguais, entao é raiz. Caso contrário, é Nutella. XD
void retira(TAG* t, TAG* pai, int cod, TAG* novo_pai) {

    if (!t || !pai) return;
    if (t->cod == cod) {

      /*
      // IMPRIIR O PAI E O FILHO NESSA ORDEM
      imprimir_status_arvore(pai);
      imprimir_status_arvore(t);
      */

      // Caso 0, não remover a raiz
      if(t->cod == pai->cod){//éh a raiz
        printf("\n%d eh a raiz! Nao eh possivel mata-la!\n", t->cod);
        return;
      }

      // CASO 1
      // NÃO TEM IRMÃO OU FILHO e É FILHO ÚNICO
      if (t->f == NULL && t->i == NULL) {
        // verificar se é filho único
        // Caso 1a nó é filho único e não tem nem pai nem irmão
        if (pai->f->cod == t->cod) {
          pai->f = NULL;
        } else {
          // CASO 1.b e 1.c CASO 2
          // nesse caso o elemento localizado é o último filho
          TAG *penultimo_filho = NULL;
          TAG *aux = pai->f;
          while (aux->i) {
            penultimo_filho = aux;
            aux = aux->i;
          }

          // sempre haverá pelo menos 1 filho uma vez que
          // se fosse filho único teria sido resolvido no if
          // anterior
          penultimo_filho->i = NULL;
        }
      }

      // CASO 3 - o nó está entre dois irmãos e não tem filhos
      if (t->f == NULL && t->i != NULL) {
        TAG *penultimo_filho = NULL;
        TAG *aux = pai->f;
        while (aux->i && aux->cod != t->cod) {
          penultimo_filho = aux;
          aux = aux->i;
        }
        if (penultimo_filho) {
          penultimo_filho->i = t->i;
        } else {
          pai->f = t->i;
        }
      }


      // CASO 4a - o nó não tem irmãos mas tem filho
      // 1 -> 2 -> 3 e quer apagar o 2 então 1 -> 3
      if (t->f != NULL && t->i == NULL) {
        pai->f = t->f;
      }


      // CASO 5 - o nó  tem irmãos e filhos
      // o pai do nó vai apontar para o primeiro irmão
      // o primeiro filho do nó será colocado no último filho do primeiro irmão
      if (t->f != NULL && t->i != NULL) {
        // aqui só vai entrar SE for passado o código do novo pai
        if (novo_pai != NULL) {
          mover_no_remover(t, pai, novo_pai);
          /*
          // achar o irmão antecessor
          TAG* no_anterior = NULL;
          TAG* aux = novo_pai->f;
          while (aux) {
            no_anterior = aux;
            aux = aux->i;
          }

          // AJUSTE O PONTEIROS DOS FILHOS
          if (!no_anterior) {
            // aponta o pai para o primeiro irmão
            novo_pai->f = t->f;
          } else {
            no_anterior->i = t->f;
          }

          // ajustar a posição onde o nó estava
          // achar o irmão antecessor
          no_anterior = NULL;
          aux = pai->f;
          while (aux) {
            if (aux->cod == t->cod) {
              break;
            }
            no_anterior = aux;
            aux = aux->i;
          }

          // AJUSTE O PONTEIROS DOS FILHOS
          if (!no_anterior) {
            // aponta o pai para o primeiro irmão
            pai->f = t->i;
          } else {
            no_anterior->i = t->i;
          }
          */
        } else {
          // achar o irmão antecessor
          TAG* no_anterior = NULL;
          TAG* aux = pai->f;
          while (aux) {
            if (aux->cod == t->cod) {
              break;
            }
            no_anterior = aux;
            aux = aux->i;
          }

          // AJUSTE O PONTEIROS DOS FILHOS
          if (!no_anterior) {
            // aponta o pai para o primeiro irmão
            pai->f = t->i;
          } else {
            no_anterior->i = t->i;
          }

          // AJUSTA O PONTEIRO DOS IRMÃOS
          // coloca os filhos de t no final do primeiro irmão de t
          TAG* ultimo_filho = NULL;
          aux = pai->f;
          while (aux) {
            ultimo_filho = aux;
            aux = aux->i;
          }
          if (!ultimo_filho) {
            pai->f->i = t->f;
          } else {
            ultimo_filho->i = t->f;
          }
        }
      }

      // efetivamente elimina o nó localizado
      free(t->fig->fig);
      free(t->fig);
      free(t);
      return;
    } else {
      // pesquisa nos filhos e o pai será o próprio t
      if (t->f)
        retira(t->f, t, cod, novo_pai);

      // pesquisa nos irmãos e nesse caso o pai será o pai do nó atual
      if (t->i)
        retira(t->i, pai, cod, novo_pai);
    }
}

void mover_no_remover(TAG* t, TAG* pai, TAG* novo_pai) {
  // achar o irmão antecessor
  TAG* no_anterior = NULL;
  TAG* aux = novo_pai->f;
  while (aux) {
    no_anterior = aux;
    aux = aux->i;
  }

  // AJUSTE O PONTEIROS DOS FILHOS
  if (!no_anterior) {
    // aponta o pai para o primeiro irmão
    novo_pai->f = t->f;
  } else {
    no_anterior->i = t->f;
  }

  // ajustar a posição onde o nó estava
  // achar o irmão antecessor
  no_anterior = NULL;
  aux = pai->f;
  while (aux) {
    if (aux->cod == t->cod) {
      break;
    }
    no_anterior = aux;
    aux = aux->i;
  }

  // AJUSTE O PONTEIROS DOS FILHOS
  if (!no_anterior) {
    // aponta o pai para o primeiro irmão
    pai->f = t->i;
  } else {
    no_anterior->i = t->i;
  }
}

void mover_no(TAG* t, TAG* pai, TAG* novo_pai) {
  // validar
  // verificar se o novo pai não pertence a subarvore de T
  TAG* no_na_sub = NULL;
  no_na_sub = busca(t, novo_pai->cod);
  if (no_na_sub) {
    printf("\nCódigo do novo pai %d NÃO pode ser descendente de %d.\n",novo_pai->cod, t->cod);
    return;
  }

  // verificar se o novo pai já não é o pai
  if (pai->cod == novo_pai->cod) {
    printf("\nO novo pai e o pai atual são os mesmos.\n");
    return;
  }

  // achar o irmão antecessor
  TAG* no_anterior = NULL;
  TAG* aux = novo_pai->f;
  while (aux) {
    no_anterior = aux;
    aux = aux->i;
  }

  // AJUSTE O PONTEIROS DOS FILHOS
  if (!no_anterior) {
    // aponta o pai para o primeiro irmão
    novo_pai->f = t;
  } else {
    no_anterior->i = t;
  }

  // ajustar a posição onde o nó estava
  // achar o irmão antecessor
  no_anterior = NULL;
  aux = pai->f;
  while (aux) {
    if (aux->cod == t->cod) {
      break;
    }
    no_anterior = aux;
    aux = aux->i;
  }

  // AJUSTE O PONTEIROS DOS FILHOS
  if (!no_anterior) {
    // aponta o pai para o primeiro irmão
    pai->f = NULL;
  } else {
    no_anterior->i = NULL;
  }
}

TAG* no_pai(TAG* t, TAG *pai, int cod) {
  if (!t) {
    return NULL;
  }
  if (t->cod == cod) {
    return pai;
  } else {
    if (t->f) {
      // pesquisa nos filhos e o pai será o próprio t
      TAG* x = no_pai(t->f, t, cod);
      if (x) return x;
    }
    // pesquisa nos irmãos e nesse caso o pai será o pai do nó atual
    if (t->i) {
      TAG* x = no_pai(t->i, pai, cod);
      if (x) return x;
    }
  }
}


void export_nodes(TAG* t, TAG* pai) {

  printf("%d",t->cod);
  if (t->cod == pai->cod) {
    printf("/0");
  } else {
    printf("/%d",pai->cod);
  }

  TQUADRADO *aux_q;
  TCIRCULO *aux_c;
  TRETANGULO *aux_r;
  TTRIANGULO *aux_tri;
  TTRAPEZIO *aux_tra;

  switch (t->fig->tipo){
      case TIPO_QUADRADO:
        aux_q = t->fig->fig;
        printf("/QUA %.0f", aux_q->l);
        break;
      case TIPO_CIRCULO:
        aux_c = t->fig->fig;
        printf("/CIR %.0f", aux_c->r);
        break;
      case TIPO_RETANGULO:
        aux_r = t->fig->fig;
        printf("/RET %.0f %.0f", aux_r->l, aux_r->a);
        break;
      case TIPO_TRIANGULO:
        aux_tri = t->fig->fig;
        printf("/TRI %.0f %.0f", aux_tri->b, aux_tri->a);
        break;
      case TIPO_TRAPEZIO:
        aux_tra = t->fig->fig;
        printf("/TRA %.0f %.0f %.0f", aux_tra->b1, aux_tra->b2, aux_tra->h);
      default:
        break;
    }

  printf("\n");
  // pesquisa nos filhos e o pai será o próprio t
  if (t->f)
    export_nodes(t->f, t);

  // pesquisa nos irmãos e nesse caso o pai será o pai do nó atual
  if (t->i)
    export_nodes(t->i, pai);
}

/*
  Imprime uma lista com todos os cod de um detemrinado tipo
*/
void busca_tipo(TAG* t, int tipo) {
  float total = 0;
  printf("\nTodos os nós com o tipo %s.\n",nome_tipo(tipo));
  busca_tipo_rec(t,tipo, &total);
  printf("============\n");
  printf("Área Total: %.2f\n",total);
}

void busca_tipo_rec(TAG* t, int tipo, float* total) {
  if (!t) return;

  if (t->fig->tipo == tipo) {
    *total += t->fig->area;
    printf("--------\n");
    printf("Cód: %d",t->cod);
    printf(" Área: %.2f\n",t->fig->area);
  }


  // pesquisa nos filhos e o pai será o próprio t
  if (t->f)
    busca_tipo_rec(t->f, tipo, total);

  // pesquisa nos irmãos e nesse caso o pai será o pai do nó atual
  if (t->i)
    busca_tipo_rec(t->i, tipo, total);

}