#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main() {

  // cria o primeiro nó da árvore
  TAG* big = cria_arvore(1,cria_quadrado(10));

  big = insere_filho_quadrado(big,2,2);
  big = insere_filho_quadrado(big,3,3);
  big = insere_filho_quadrado(big,4,4);

  // inserer um quadrado como filho do segundo filho de big
  insere_filho_quadrado(big->f->i,5,5);
  insere_filho_quadrado(big->f->i,6,6);

  imprimir_status_filhos(big);

  // big = insere_filho_quadrado(big,20);

  // imprimir_filhos(big);

  return 0;
}