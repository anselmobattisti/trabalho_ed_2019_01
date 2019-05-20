#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// árvore principal do programa
TAG *t;

void processar_entrada();

int main() {

  processar_entrada();
  printf("\n=============\n\n");
  imprime_semi_bonito(t);
  imprimir_status_arvore(t);
  /*

  // cria o primeiro nó da árvore
  TAG* big = cria_arvore(1,cria_quadrado(10));

  insere_filho_quadrado(big,2,2);
  insere_filho_circulo(big,3,3);
  insere_filho_circulo(big,5,4);
  insere_filho_quadrado(busca(big,3),4,4);
  insere_filho_quadrado(busca(big,3),8,4);
  insere_filho_quadrado(busca(big,4),7,4);

  TAG *e3 = busca(big,7);
  imprimir_status_filhos(e3);

  // insere_filho_quadrado(busca(big,3), 4, 4);


  insere_filho_quadrado(big->f->i->f,7,1);

  imprimir_status_filhos(big->f->i->f);

  processar_entrada();

  printf("\n----");
  imprimir_status_filhos(busca(t,3));

  // imprimir_status_filhos(t->f->i);
  // imprimir_status_filhos(busca(t,4));
  // imprimir_como_dir(t,1);
  // printf("\n%.2f\n",area_total(t));

  /*

  // cria o primeiro nó da árvore
  TAG* big = cria_arvore(1,cria_quadrado(10));

  insere_filho_quadrado(big,2,2);
  insere_filho_circulo(big,3,3);
  insere_filho_quadrado(big,4,4);

  // inserer um quadrado como filho do segundo filho de big
  insere_filho_quadrado(big->f->i,5,5);
  insere_filho_quadrado(big->f->i,6,6);
  insere_filho_circulo(busca(big,5),8,8);
  insere_filho_circulo(busca(big,5),9,3);
  insere_filho_circulo(busca(big,9),10,3);

  TAG* b = busca(big,11);
  imprimir_status_filhos(b);

  // insere_filho_quadrado(busca(big,8),9,9);

  // imprimir_status_filhos(big);

  // big = insere_filho_quadrado(big,20);

  // imprimir_filhos(big);

  return 0;
  */
}

/*
  A partir do arquivo popula a árvore
*/
void processar_entrada() {
  char s[1000];

  while(fgets(s, 200, stdin)){
    int cod = 0;
    int pai = 0;
    char *tipo;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;

    char *pch = strtok (s," /");
    int k = 0;
    while(pch != NULL) {
      if (k == 0) {
        cod = atoi(pch);
      }
      if (k == 1) {
        pai = atoi(pch);
      }
      if (k == 2) {
        tipo = pch;
      }

      if (k == 3) {
        v1 = atoi(pch);
      }

      if (k == 4) {
        v2 = atoi(pch);
      }

      if (k == 5) {
        v3 = atoi(pch);
      }

      pch = strtok (NULL," /");
      k++;
    }

    if (pai == 0) {
      if (strcmp(tipo,"QUA") == 0) {
        t = cria_arvore(cod,cria_quadrado(v1));
      }
      if (strcmp(tipo,"CIR") == 0) {
        t = cria_arvore(cod,cria_circulo(v1));
      }
      if (strcmp(tipo,"RET") == 0) {
        t = cria_arvore(cod,cria_retangulo(v1,v2));
      }
      if (strcmp(tipo,"TRI") == 0) {
        t = cria_arvore(cod,cria_triangulo(v1,v2));
      }
      if (strcmp(tipo,"TRA") == 0) {
        t = cria_arvore(cod,cria_trapezio(v1,v2,v3));
      }
    }

    if (pai > 0) {
      if(strcmp(tipo,"QUA") == 0) {
        insere_filho_quadrado(busca(t,pai),cod,v1);
      }

      if (strcmp(tipo,"CIR") == 0) {
        insere_filho_circulo(busca(t,pai),cod,v1);
      }

      if (strcmp(tipo,"RET") == 0) {
        insere_filho_retangulo(busca(t,pai),cod,v1,v2);
      }

      if (strcmp(tipo,"TRI") == 0) {
        insere_filho_triangulo(busca(t,pai),cod,v1,v2);
      }

      if (strcmp(tipo,"TRA") == 0) {
        insere_filho_trapezio(busca(t,pai),cod,v1,v2,v3);
      }
    }
    // descomente se quiser ver os valores de entrada
    // printf("\n %d %d %s %d %d %d \n",cod,pai,tipo,v1,v2,v3);
  }
}