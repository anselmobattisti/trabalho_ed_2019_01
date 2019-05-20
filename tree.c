#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

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
    if (tem_filhos(aux)) {
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

TDADO *cria_quadrado(int l) {
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

TAG* altera_filho_circulo(TAG *t, int cod, float r) {
  if (!t) return NULL;
  TAG* aux = busca(t,cod);
  TDADO *tc = cria_circulo(r);
  aux->fig = tc;
  return aux;
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

int tem_filhos(TAG *t) {
  if (!t->f) {
    return 0;
  }
  int c = 0;

  TAG *aux = t->f;
  while(aux) {
    c++;
    aux = aux->i;
  }
  return c;
}

int tem_irmaos(TAG *t) {
  if (!t->i) {
    return 0;
  }
  return 1;
}

char* nome_tipo(int tipo) {
  switch (tipo){
    case TIPO_QUADRADO:
      return "qua";
      break;
    case TIPO_CIRCULO:
      return "cir";
      break;
    case TIPO_RETANGULO:
      return "ret";
      break;
    case TIPO_TRIANGULO:
      return "tri";
      break;
    case TIPO_TRAPEZIO:
      return "tra";
      break;
    default:
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

void imprimir_status_arvore(TAG *t) {
  if (!t) return;
  printf("\n+----------------------+");
  printf("\n| Cod               : %d",t->cod);
  printf("\n| Tipo              : %s",nome_tipo(t->fig->tipo));
  printf("\n| N. Filhos         : %d",tem_filhos(t));
  printf("\n| N. Descendentes   : %d",num_descendentes(t->f));
  printf("\n| Área do Nó        : %.2f",t->fig->area);
  printf("\n| Área Só Filhos    : %.2f", area_filhos(t));
  printf("\n| Área Descendentes : %.2f", area_total(t->f));
  printf("\n+-----------------------+\n");
}

void imprime_semi_bonito(TAG *t) {
  printf("\nÁrvore Completa\n----------------\n");
  imprimir_como_dir(t, 1);
  printf("----------------\nTotal: %d\n----------------\n",num_descendentes(t->f)+1);
}

/*
  @todo: ainda não esta legal
*/
void imprimir_como_dir(TAG *t, int nivel) {
  int passo = 2;
  for (int i = 0; i < nivel; i++) {
    printf("-");
  }
  printf("> %d (%s,%.2f)\n",t->cod,nome_tipo(t->fig->tipo), t->fig->area);

  TAG* aux = t->f; // acessa o primeiro filho

  while (aux) {
    if (tem_filhos(aux)) {
      imprimir_como_dir(aux,nivel+passo);
    } else {
      for (int i = 0; i < nivel + passo; i++) {
        printf("-");
      }
      printf("> %d (%s,%.2f)\n",aux->cod,nome_tipo(aux->fig->tipo), t->fig->area);
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