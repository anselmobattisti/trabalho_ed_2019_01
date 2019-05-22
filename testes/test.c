#include <stdio.h>
#include <stdlib.h>
#include "../tree.h"
#include "../avl.h"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

TAG *t;
node* avl;

void teste_criacao_arvore();
void teste_criacao_circulo();
void teste_busca();
void teste_tem_filhos();
void teste_num_descendentes();

int main() {
  printf("Casos de teste\n");
  printf("--------------\n");

  teste_criacao_circulo();
  teste_criacao_arvore();
  teste_busca();
  teste_tem_filhos();

}

void teste_num_descendentes() {

}

void teste_tem_filhos() {
  printf("\nTem filhos\n");
  t = cria_arvore(1,cria_circulo(1));
  insere_filho_circulo(t,2,1);

  TAG* f2 = busca(t,2);
  insere_filho_circulo(f2,3,1);
  insere_filho_circulo(f2,4,1);

  TAG* f3 = busca(t,4);
  insere_filho_circulo(f3,5,1);

  int i = tem_filhos(t->f);
  if (i == 1) {
    printf(COLOR_GREEN"[OK] -> 1. Nó com 1 filho computado corretamente.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Erro ao contar 1 filho.\n"COLOR_RESET);
    return;
  }

  i = tem_filhos(f2->f);
  if (i == 2) {
    printf(COLOR_GREEN"[OK] -> 3. Nó com 2 filhos computado corretamente.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Erro ao contar 2 filhos.\n"COLOR_RESET);
    return;
  }

  TAG* f5 = busca(t,5);
  i = tem_filhos(f5->f);
  if (i == 0) {
    printf(COLOR_GREEN"[OK] -> 5. Nó com 0 filhos computado corretamente.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Erro ao contar 0 filhos.\n"COLOR_RESET);
    return;
  }
}

void teste_busca() {
  printf("\nBusca\n");
  t = cria_arvore(1,cria_circulo(1));
  insere_filho_circulo(t,2,1);
  insere_filho_circulo(t,3,1);
  insere_filho_circulo(t,4,1);

  TAG* b1 = busca(t,4);
  if (b1) {
    printf(COLOR_GREEN"[OK] -> 1. Nó localizado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Nenhum nó localizado.\n"COLOR_RESET);
    return;
  }

  if (b1->cod == 4) {
    printf(COLOR_GREEN"[OK] -> 3. Nó correto localizado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[OK] -> 4. Nó errado localizado.\n"COLOR_RESET);
  }

  TAG* b2 = busca(t,5);
  if (!b2) {
    printf(COLOR_GREEN"[OK] -> 5. Nó inexistente não localizado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Nó não existente localizado.\n"COLOR_RESET);
    return;
  }

  insere_filho_circulo(b1,5,1);
  b2 = busca(t,5);
  if (b2) {
    printf(COLOR_GREEN"[OK] -> 6. Filho do filho localizado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 7. Filho do filho não localizado.\n"COLOR_RESET);
    return;
  }

  insere_filho_circulo(b2,6,1);
  TAG *b3 = busca(t,6);
  if (b3) {
    printf(COLOR_GREEN"[OK] -> 6. Filho do filho do filho localizado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 7. Filho do filho do filho não localizado.\n"COLOR_RESET);
    return;
  }

  TAG *b4 = busca(t,1);
  if (b4->cod == 1) {
    printf(COLOR_GREEN"[OK] -> 7. Raiz localizada.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 8. Raiz não localizada.\n"COLOR_RESET);
    return;
  }
}


void teste_criacao_circulo() {
  printf("\nCriação do Círculo\n");
  TDADO *c = cria_circulo(1);
  TCIRCULO *tc = (TCIRCULO*) c->fig;
  if (c) {
    printf(COLOR_GREEN"[OK] -> 1. Círculo criado com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 1. Erro ao criar círculo.\n"COLOR_RESET);
    return;
  }

  if (tc->r == 1) {
    printf(COLOR_GREEN"[OK] -> 2. Raio do círculo ok.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[OK] -> 3. Raio do círculo com problema.\n"COLOR_RESET);
  }

  if (c->area > 3.14 && c->area < 3.15) {
    printf(COLOR_GREEN"[OK] -> 2. Área do círculo calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[OK] -> 3. Área do círculo calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_arvore() {
  printf("\nCriação da Árvore\n");
  t = cria_arvore(1,cria_circulo(1));

  if (!t) {
    printf(COLOR_RED"[ERROR] -> 1. Árvore não foi criada com sucesso.\n"COLOR_RESET);
    return;
  }

  if (t->cod == 1) {
    printf(COLOR_GREEN"[OK] -> 2. Árvore criadao com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 3. Árvore não foi criada com sucesso.\n"COLOR_RESET);
  }
}