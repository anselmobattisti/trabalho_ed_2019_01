#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tree.h"
#include "../avl.h"
#include "./testes.h"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

void processar_testes() {
  printf("Casos de teste\n");
  printf("--------------");
  teste_criacao_trapezio();
  teste_criacao_quadrado();
  teste_criacao_retangulo();
  teste_criacao_triangulo();
  teste_criacao_quadrado();
  teste_criacao_circulo();
  getchar();

  teste_criacao_arvore();
  teste_busca();
  teste_tem_filhos();
  teste_num_descendentes();
  getchar();

  // testes de inserção
  teste_insere_filho_trapezio();
  teste_insere_filho_circulo();
  teste_insere_filho_quadrado();
  teste_insere_filho_triangulo();
  teste_insere_filho_retangulo();

  getchar();
  teste_area_total();
  teste_area_filhos();
  teste_dimensoes_tipo();
  teste_retira();
}

void teste_num_descendentes() {
  printf("\nNúmero de Descendentes\n");
  TAG* t = cria_arvore(1,cria_circulo(1));
  insere_filho_circulo(t,2,1);

  TAG* f2 = busca(t,2);
  insere_filho_circulo(f2,3,1);
  insere_filho_circulo(f2,4,1);

  TAG* f3 = busca(t,4);
  insere_filho_circulo(f3,5,1);

  int i = num_descendentes(t);
  if (i == 5) {
    printf(COLOR_GREEN"[OK] -> 1. Nó raiz com 5 descendente.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Erro na raiz com 5 dependentes.\n"COLOR_RESET);
    return;
  }

  i = num_descendentes(f3->f);
  if (i == 1) {
    printf(COLOR_GREEN"[OK] -> 3. Nó com 1 descendente.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Erro 1 dependente.\n"COLOR_RESET);
    return;
  }

  TAG* f5 = busca(t,5);
  i = num_descendentes(f5->f);
  if (i == 0) {
    printf(COLOR_GREEN"[OK] -> 5. Nó com 0 descendentes.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Nó com 0 descendentes.\n"COLOR_RESET);
    return;
  }
}

void teste_tem_filhos() {
  printf("\nTem filhos\n");
  TAG* t = cria_arvore(1,cria_circulo(1));
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
  TAG* t = cria_arvore(1,cria_circulo(1));
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
    printf(COLOR_RED"[ERRO] -> 4. Nó errado localizado.\n"COLOR_RESET);
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
    printf(COLOR_RED"[ERRO] -> 3. Raio do círculo com problema.\n"COLOR_RESET);
  }

  if (c->area > 3.14 && c->area < 3.15) {
    printf(COLOR_GREEN"[OK] -> 4. Área do círculo calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 5. Área do círculo calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_quadrado() {
  printf("\nCriação do Quadrado\n");
  TDADO *q = cria_quadrado(1);
  TQUADRADO *tq = (TQUADRADO*) q->fig;
  if (q) {
    printf(COLOR_GREEN"[OK] -> 1. Quadrado criado com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 2. Erro ao criar quadrado.\n"COLOR_RESET);
    return;
  }

  if (tq->l == 1) {
    printf(COLOR_GREEN"[OK] -> 3. Lado do quadrado ok.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Lado do quadrado com problema.\n"COLOR_RESET);
  }

  if (q->area == 1) {
    printf(COLOR_GREEN"[OK] -> 5. Área do quadrado calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 3. Área do quadrado calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_trapezio() {
  printf("\nCriação do Trapézio\n");
  TDADO *trap = cria_trapezio(1,2,3);
  TTRAPEZIO *tt = (TTRAPEZIO*) trap->fig;
  if (trap) {
    printf(COLOR_GREEN"[OK] -> 1. Trapezio criado com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 2. Erro ao criar trapézio.\n"COLOR_RESET);
    return;
  }

  if (tt->b1 == 1 && tt->b2 == 2 && tt->h == 3) {
    printf(COLOR_GREEN"[OK] -> 3. Lado do trapezio.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 4. Lado do trapezio com problema.\n"COLOR_RESET);
  }

  if (trap->area == 4.50) {
    printf(COLOR_GREEN"[OK] -> 5. Área do trapézio calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 6. Área do trapézio calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_triangulo() {
  printf("\nCriação do Triângulo\n");
  TDADO *tri = cria_triangulo(1,2);
  TTRIANGULO *tt = (TTRIANGULO*) tri->fig;
  if (tri) {
    printf(COLOR_GREEN"[OK] -> 1. Triangulo criado com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 2. Erro ao criar triângulo.\n"COLOR_RESET);
    return;
  }

  if (tt->b == 1 && tt->a == 2) {
    printf(COLOR_GREEN"[OK] -> 3. Lado do triângulo ok.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Lado do triângulo com problema.\n"COLOR_RESET);
  }

  if (tri->area == 1) {
    printf(COLOR_GREEN"[OK] -> 5. Área do triângulo calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Área do triângulo calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_retangulo() {
  printf("\nCriação do Retângulo\n");
  TDADO *ret = cria_retangulo(1,2);
  TRETANGULO *tr = (TRETANGULO*) ret->fig;
  if (ret) {
    printf(COLOR_GREEN"[OK] -> 1. Retêngulo criado com sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERROR] -> 2. Erro ao criar retêngulo.\n"COLOR_RESET);
    return;
  }


  if (tr->l == 1 && tr->a == 2) {
    printf(COLOR_GREEN"[OK] -> 3. Lado do retângulo.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Lado do retângulo com problema.\n"COLOR_RESET);
  }

  if (ret->area == 2) {
    printf(COLOR_GREEN"[OK] -> 5. Área do retângulo calculada sucesso.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 3. Área do retângulo calculada com erro.\n"COLOR_RESET);
  }
}

void teste_criacao_arvore() {
  printf("\nCriação da Árvore\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

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

void teste_insere_filho_trapezio() {
  printf("\nInserção do Trapézio\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

  insere_filho_trapezio(t,2,1,2,3);
  TAG* f = busca(t,2);

  if (f) {
    printf(COLOR_GREEN"[OK] -> 1. Figura inserida.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Figura não inserida.\n"COLOR_RESET);
  }

  if (f->fig->tipo == TIPO_TRAPEZIO) {
    printf(COLOR_GREEN"[OK] -> 3. Tipo correto.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Tipo incorreto.\n"COLOR_RESET);
    return;
  }
}

void teste_insere_filho_circulo() {
  printf("\nInserção do Círculo\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

  insere_filho_circulo(t,2,1);
  TAG* f = busca(t,2);

  if (f) {
    printf(COLOR_GREEN"[OK] -> 1. Figura inserida.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Figura não inserida.\n"COLOR_RESET);
  }

  if (f->fig->tipo == TIPO_CIRCULO) {
    printf(COLOR_GREEN"[OK] -> 3. Tipo correto.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Tipo incorreto.\n"COLOR_RESET);
    return;
  }
}

void teste_insere_filho_quadrado() {
  printf("\nInserção do Quadrado\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

  insere_filho_quadrado(t,2,1);
  TAG* f = busca(t,2);

  if (f) {
    printf(COLOR_GREEN"[OK] -> 1. Figura inserida.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Figura não inserida.\n"COLOR_RESET);
  }

  if (f->fig->tipo == TIPO_QUADRADO) {
    printf(COLOR_GREEN"[OK] -> 3. Tipo correto.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Tipo incorreto.\n"COLOR_RESET);
    return;
  }
}

void teste_insere_filho_triangulo() {
  printf("\nInserção do Triângulo\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

  insere_filho_triangulo(t,2,1,2);
  TAG* f = busca(t,2);

  if (f) {
    printf(COLOR_GREEN"[OK] -> 1. Figura inserida.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Figura não inserida.\n"COLOR_RESET);
  }

  if (f->fig->tipo == TIPO_TRIANGULO) {
    printf(COLOR_GREEN"[OK] -> 3. Tipo correto.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Tipo incorreto.\n"COLOR_RESET);
    return;
  }
}

void teste_insere_filho_retangulo() {
  printf("\nInserção do Retângulo\n");
  TAG* t = cria_arvore(1,cria_circulo(1));

  insere_filho_retangulo(t,2,1,2);
  TAG* f = busca(t,2);

  if (f) {
    printf(COLOR_GREEN"[OK] -> 1. Figura inserida.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Figura não inserida.\n"COLOR_RESET);
  }

  if (f->fig->tipo == TIPO_RETANGULO) {
    printf(COLOR_GREEN"[OK] -> 3. Tipo correto.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Tipo incorreto.\n"COLOR_RESET);
    return;
  }
}

void teste_area_total() {
  printf("\nÁrea Total\n");
  TAG* t = cria_arvore(1,cria_quadrado(1));
  insere_filho_quadrado(t,2,1);
  insere_filho_retangulo(t,3,2,3);

  TAG* f = busca(t,2);
  insere_filho_triangulo(f,4,1,2);

  TAG* f1 = busca(t,4);
  insere_filho_triangulo(f1,5,1,2);

  if (area_total(t) == 10) {
    printf(COLOR_GREEN"[OK] -> 1. Área total vários filhos.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Área total deveria ser 10 e foi %.2f.\n"COLOR_RESET,area_total(t));
  }

  if (area_total(f1) == 2) {
    printf(COLOR_GREEN"[OK] -> 3. Área total com 1 filho .\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Área total deveria ser 1 e foi %.2f.\n"COLOR_RESET,area_total(f1));
  }

  TAG* f2 = busca(t,5);
  if (area_total(f2) == 1) {
    printf(COLOR_GREEN"[OK] -> 5. Área sem filhos .\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Área total deveria ser 0 e foi %.2f.\n"COLOR_RESET,area_total(f2));
  }
}

void teste_area_filhos() {
  printf("\nÁrea dos Filhos\n");
  TAG* t = cria_arvore(1,cria_quadrado(1));
  insere_filho_quadrado(t,2,1);
  insere_filho_retangulo(t,3,2,3);

  TAG* f = busca(t,2);
  insere_filho_triangulo(f,4,1,2);

  TAG* f1 = busca(t,4);
  insere_filho_triangulo(f1,5,1,2);

  if (area_filhos(t) == 7) {
    printf(COLOR_GREEN"[OK] -> 1. Área total com vários filhos.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Área total deveria ser 7 e foi %.2f.\n"COLOR_RESET,area_filhos(t));
  }

  if (area_filhos(f1) == 1) {
    printf(COLOR_GREEN"[OK] -> 3. Área total com 1 filhos.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Área total deveria ser 0 e foi %.2f.\n"COLOR_RESET,area_filhos(f1));
  }

  TAG* f2 = busca(t,5);
  if (area_filhos(f2) == 0) {
    printf(COLOR_GREEN"[OK] -> 3. Área total sem filhos.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Área total deveria ser 0 e foi %.2f.\n"COLOR_RESET,area_filhos(f2));
  }
}

void teste_dimensoes_tipo() {
  printf("\nTestar Dimensões\n");

  TDADO* aux_q = cria_quadrado(1);
  TDADO* aux_c = cria_circulo(1);
  TDADO* aux_r = cria_retangulo(1,2);
  TDADO* aux_tri = cria_triangulo(1,2);
  TDADO* aux_tra = cria_trapezio(1,2,3);

  char s_aux_q[] = "L: 1.00";
  char s_aux_c[] = "R: 1.00";
  char s_aux_r[] = "L1: 1.00, L2: 2.00";
  char s_aux_tri[] = "B: 1.00, A: 2.00";
  char s_aux_tra[] = "B1: 1.00, B2: 2.00, A: 3.00";

  if (strcmp(dimensoes_tipo(aux_q),s_aux_q) == 0) {
    printf(COLOR_GREEN"[OK] -> 1. Quadrado.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 2. Erro quadrado.\n"COLOR_RESET);
  }

  if (strcmp(dimensoes_tipo(aux_c),s_aux_c) == 0) {
    printf(COLOR_GREEN"[OK] -> 3. Círculo.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 4. Erro Círculo.\n"COLOR_RESET);
  }

  if (strcmp(dimensoes_tipo(aux_r),s_aux_r) == 0) {
    printf(COLOR_GREEN"[OK] -> 5. Retângulo.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 6. Erro Retângulo.\n"COLOR_RESET);
  }

  if (strcmp(dimensoes_tipo(aux_tri),s_aux_tri) == 0) {
    printf(COLOR_GREEN"[OK] -> 7. Triângulo.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 8. Erro Triângulo.\n"COLOR_RESET);
  }

  if (strcmp(dimensoes_tipo(aux_tra),s_aux_tra) == 0) {
    printf(COLOR_GREEN"[OK] -> 9. Trapézio.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> 10. Erro Trapézio.\n"COLOR_RESET);
  }
}

void teste_retira() {
  TAG *b = NULL;
  TAG *aux = NULL;

  printf("\nRetirar Elemento\n");
  TAG* t = cria_arvore(1,cria_circulo(1));
  retira(t,t,1);
  // Caso 0, não remover a raiz
  b = busca(t,1);
  if (b) {
    printf(COLOR_GREEN"[OK] -> Não removeu a raiz, CASO 0.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Removou a raiz CASO 0.\n"COLOR_RESET);
  }


  // 1a nó é filho único e não tem nem pai nem irmão
  insere_filho_circulo(t,2,1);
  retira(t,t,2);
  b = busca(t,2);
  if (b == NULL && t->f == NULL) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 1a.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 1a.\n"COLOR_RESET);
  }

  // 1b o nó não tem nem pai e nem irmão mas não é filho único e é o segundo filho
  insere_filho_circulo(t,2,1);
  insere_filho_circulo(t,4,1);
  retira(t,t,4);
  b = busca(t,4);
  aux = busca(t,2);
  if (b == NULL && aux->i == NULL) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 1b.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 1b.\n"COLOR_RESET);
  }

  // 1c o nó não tem nem pai e nem irmão mas não é filho único e é o último filho
  insere_filho_circulo(t,4,1);
  insere_filho_circulo(t,14,1);
  retira(t,t,14);
  b = busca(t,14);
  aux = busca(t,4);
  if (b == NULL && aux->i == NULL) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 1c.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 1c.\n"COLOR_RESET);
  }

  // CASO 2 - elemento não é filho da raiz MAS é filho único como no caso 1a
  insere_filho_circulo(t,14,1);
  insere_filho_circulo(busca(t,2),3,1);
  retira(t,t,3);
  b = busca(t,3);
  aux = busca(t,2);
  if (b == NULL && aux->f == NULL) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 2.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 2.\n"COLOR_RESET);
  }

  // CASO 3 - o nó está entre dois irmãos e não tem filhos
  insere_filho_circulo(busca(t,2),3,1);
  retira(t,t,4);
  b = busca(t,4);
  aux = busca(t,2);
  if (b == NULL && aux->i->cod == 14) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 3.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 3.\n"COLOR_RESET);
  }

  // CASO 4 - o nó não tem irmãos mas tem filho
  // CASO 4a
  retira(t,t,14);
  insere_filho_circulo(t,4,1);
  insere_filho_circulo(t,14,1);
  insere_filho_circulo(busca(t,3),5,1);
  retira(t,t,3);
  b = busca(t,3);
  aux = busca(t,2);
  if (b == NULL && aux->f->cod == 5) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 4a.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 4a.\n"COLOR_RESET);
  }

  // CASO 4b
  retira(t,t,5);
  insere_filho_circulo(busca(t,2),3,1);
  insere_filho_circulo(busca(t,3),5,1);
  insere_filho_circulo(busca(t,5),6,1);
  retira(t,t,5);
  aux = busca(t,3);
  b = busca(t,5);

  if (b == NULL && aux->f->cod == 6) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 4b.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 4b.\n"COLOR_RESET);
  }

  // CASO 5a o nó tem irmão e filhos
  retira(t,t,6);
  insere_filho_circulo(busca(t,3),5,1);
  insere_filho_circulo(busca(t,5),6,1);
  insere_filho_circulo(busca(t,4),16,1);
  retira(t,t,2);
  b = busca(t,2);
  if (b == NULL && t->f->cod == 4) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 5a.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 5a.\n"COLOR_RESET);
  }

  // CASO 5b o nó tem irmão e filhos
  insere_filho_circulo(busca(t,3),50,1);
  insere_filho_circulo(busca(t,3),51,1);
  insere_filho_circulo(busca(t,3),52,1);
  insere_filho_circulo(busca(t,14),53,1);
  retira(t,t,14);

  b = busca(t,14);
  aux = busca(t,4);

  if (b == NULL && aux->i->cod == 3) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 5b.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 5b.\n"COLOR_RESET);
  }

  retira(t,t,5);
  b = busca(t,5);
  aux = busca(t,3);
  if (b == NULL && aux->f->cod == 50) {
    printf(COLOR_GREEN"[OK] -> Removou o CASO 5c.\n"COLOR_RESET);
  } else {
    printf(COLOR_RED"[ERRO] -> Não removou o CASO 5c.\n"COLOR_RESET);
  }

  insere_filho_circulo(busca(t,4),54,1);
  gerar_dot_arvore_generica(t);

  retira(t,t,4);
  gerar_dot_arvore_generica(t);


}