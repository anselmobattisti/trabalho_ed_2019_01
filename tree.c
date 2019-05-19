#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

TAG* busca(TAG* t, int cod) {
  if (!t) return NULL;

  TAG* aux = t->f;

  while (aux) {
    if (aux->cod == cod) {
      return aux;
    }
    if (tem_filhos(aux)) {
      return busca(aux,cod);
    }
    aux = aux->i;
  }

  return t;
  /*
  if (!t) return NULL;
  TAG* aux = t->f;
  while(aux) {
    TAG* aux2 = aux->f->i;
    while(aux2) {
      if (aux2->cod == cod) {
        printf("------ %d ----%d ----\n",aux2->cod, cod);
        return aux2;
      }
      printf(" (%d, %d) \n",aux->cod,tem_filhos(aux));
      if (tem_filhos(aux)) {
        printf("| %d %d |",aux->cod, cod);
        busca(aux->i, cod);
      }
      aux2 = aux2->i;
    }
    aux = aux->f;
  }
  */
}

void imprimir_status_filhos(TAG *t) {
  if (!t) return;
  imprimir_status_arvore(t);
  TAG* aux = t->f;
  while(aux) {
    imprimir_status_arvore(aux);
    aux = aux->i;
  }
}

void imprimir_status_arvore(TAG *t) {
  printf("\n+----------------------+");
  printf("\n| Cod         : %d",t->cod);
  printf("\n| Tipo        : %s",nome_tipo(t->fig->tipo));
  printf("\n| Filhos      : %d",tem_filhos(t));
  printf("\n| Area        : %.2f",t->fig->area);
  printf("\n| Area Filhos : %.2f", area_filhos(t));
  printf("\n+-----------------------+\n");
}

char* nome_tipo(int tipo) {
  switch (tipo){
    case TIPO_QUADRADO:
      return "q";
      break;
    case TIPO_CIRCULO:
      return "c";
      break;
    default:
      break;
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
    // é o primeiro filho
    t->f = nova_arvore;
  } else {
    ultimo_filho->i = nova_arvore;
  }
  return t;
}

TAG* insere_filho_circulo(TAG *t, int cod, float r) {
  TDADO *c = cria_circulo(r);
  return insere_filho(t,cod,c);
}

TAG* insere_filho_quadrado(TAG *t, int cod, float l) {
  TDADO *q = cria_quadrado(l);
  return insere_filho(t,cod,q);
}

int tem_filhos(TAG *t) {
  if (!t->f) {
    return 0;
  }
  int c = 0;

  TAG *aux = t->f;
  while(aux) {
    //printf("\n -->> %d",aux->cod);
    c++;
    aux = aux->i;
  }
  return c;
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

int tem_irmaos(TAG *t) {
  if (!t->i) {
    return 0;
  }
  return 1;
}

void imprimir_filhos(TAG *t) {
  if (!t) return;
  if (!tem_filhos(t)) {
    printf(".... não");
  } else {
    TAG *aux = t->f;
    while (aux) {
      switch (aux->fig->tipo){
        case TIPO_QUADRADO:
          //TQUADRADO *q = (TQUADRADO*) aux->info->fig;
          printf("Q: L:%.2f A:%.2f",10.0,aux->fig->area);
          break;
        case TIPO_CIRCULO:
          //TQUADRADO *q = (TQUADRADO*) aux->info->fig;
          printf("C: r:%.2f A:%.2f",10.0,aux->fig->area);
          break;
        default:
          printf("não implementado");
          break;
      }
      aux = aux->i;
    }
  }
}