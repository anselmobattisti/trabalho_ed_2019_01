#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../tree.h"
#include "../avl.h"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

TAG *t;
node* avl;

// criação das figuas
void teste_criacao_circulo();
void teste_criacao_triangulo();
void teste_criacao_retangulo();
void teste_criacao_quadrado();
void teste_criacao_trapezio();

void teste_criacao_arvore();

// inserção as figuras
void teste_insere_filho_trapezio();
void teste_insere_filho_circulo();
void teste_insere_filho_quadrado();
void teste_insere_filho_triangulo();
void teste_insere_filho_retangulo();

void teste_busca();
void teste_tem_filhos();
void teste_num_descendentes();

int main() {
  printf("Casos de teste\n");
  printf("--------------");

  teste_criacao_trapezio();
  teste_criacao_quadrado();
  teste_criacao_retangulo();
  teste_criacao_triangulo();
  teste_criacao_quadrado();
  teste_criacao_circulo();

  teste_criacao_arvore();

  teste_busca();
  teste_tem_filhos();
  teste_num_descendentes();

  // testes de inserção
  teste_insere_filho_trapezio();
  teste_insere_filho_circulo();
  teste_insere_filho_quadrado();
  teste_insere_filho_triangulo();
  teste_insere_filho_retangulo();

}

void teste_num_descendentes() {
  printf("\nNúmero de Descendentes\n");
  t = cria_arvore(1,cria_circulo(1));
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

void teste_insere_filho_trapezio() {
  printf("\nInserção do Trapézio\n");
  t = cria_arvore(1,cria_circulo(1));

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
  t = cria_arvore(1,cria_circulo(1));

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
  t = cria_arvore(1,cria_circulo(1));

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
  t = cria_arvore(1,cria_circulo(1));

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
  t = cria_arvore(1,cria_circulo(1));

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

