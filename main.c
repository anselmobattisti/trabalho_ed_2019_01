#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main() {

  // cria o primeiro nó da árvore
  TAG* big = cria_arvore(1,cria_quadrado(10));

  insere_filho_quadrado(big,2,2);
  insere_filho_circulo(big,3,3);
  insere_filho_quadrado(big,4,4);

  // inserer um quadrado como filho do segundo filho de big
  insere_filho_quadrado(big->f->i,5,5);
  insere_filho_quadrado(big->f->i,6,6);
  insere_filho_circulo(busca(big,3),7,7);
  insere_filho_circulo(busca(big,5),8,8);
  insere_filho_circulo(busca(big,5),9,3);
  insere_filho_circulo(busca(big,9),10,3);

  TAG* b = busca(big,9);
  imprimir_status_filhos(b);

  // insere_filho_quadrado(busca(big,8),9,9);

  // imprimir_status_filhos(big);

  // big = insere_filho_quadrado(big,20);

  // imprimir_filhos(big);

  return 0;
}