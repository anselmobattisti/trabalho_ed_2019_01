#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "avl.h"
#include "./testes/testes.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// árvore principal do programa
TAG *t;
node* avl;

void processar_entrada();
void gerar_arvore_balanceada(TAG* t);
int menu();

int main() {
    processar_entrada();
    menu();

  //printf("\n\nRetirando cod 6...\n\n");
  //retira(t, 6);
  //gerar_dot_arvore_generica(t);

  /*
  processar_entrada();
  imprime_semi_bonito(t);
  imprime_arvore_generica_como_binaria(t,"Bin");
  gerar_arvore_balanceada(t);
  print_tree(avl,"Balanceada");
  //imprimir_status_filhos(t);
  //altera_filho_circulo(t, 2, 10);
  //imprimir_status_filhos(t);
  printf("\n=============\n\n");
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
  */
  return 0;
}

/*
  A partir do arquivo popula a árvore
*/
void processar_entrada() {
  char s[1000];
  static const char filename[] = "entrada.txt";
  FILE *file = fopen ( filename, "r" );
  if ( file == NULL ) {
    printf("Erro ao ler arquivo.");
    return;
  }
  while ( fgets ( s, sizeof s, file ) != NULL ) {
    int cod = 0;
    int pai = 0;
    char *tipo;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    char *pch = strtok (s," /");
    int k = 0;
    while(pch != NULL) {
      if (k == 0)
        cod = atoi(pch);
      if (k == 1)
        pai = atoi(pch);
      if (k == 2)
        tipo = pch;
      if (k == 3)
        v1 = atoi(pch);
      if (k == 4)
        v2 = atoi(pch);
      if (k == 5)
        v3 = atoi(pch);
      pch = strtok (NULL," /");
      k++;
    }
    if (pai == 0) {
      if (strcmp(tipo,"QUA") == 0)
        t = cria_arvore(cod,cria_quadrado(v1));
      if (strcmp(tipo,"CIR") == 0)
        t = cria_arvore(cod,cria_circulo(v1));
      if (strcmp(tipo,"RET") == 0)
        t = cria_arvore(cod,cria_retangulo(v1,v2));
      if (strcmp(tipo,"TRI") == 0)
        t = cria_arvore(cod,cria_triangulo(v1,v2));
      if (strcmp(tipo,"TRA") == 0)
        t = cria_arvore(cod,cria_trapezio(v1,v2,v3));
    }
    if (pai > 0) {
      if(strcmp(tipo,"QUA") == 0)
        insere_filho_quadrado(busca(t,pai),cod,v1);
      if (strcmp(tipo,"CIR") == 0)
        insere_filho_circulo(busca(t,pai),cod,v1);
      if (strcmp(tipo,"RET") == 0)
        insere_filho_retangulo(busca(t,pai),cod,v1,v2);
      if (strcmp(tipo,"TRI") == 0)
        insere_filho_triangulo(busca(t,pai),cod,v1,v2);
      if (strcmp(tipo,"TRA") == 0)
        insere_filho_trapezio(busca(t,pai),cod,v1,v2,v3);
    }
    // descomente se quiser ver os valores de entrada
    // printf("\n %d %d %s %d %d %d \n",cod,pai,tipo,v1,v2,v3);
  }
}

/*
 Percorre a árvore genérica e inserer na árvore AVL
*/
void gerar_arvore_balanceada(TAG* t) {
  if (!t) return;
  avl = insert(avl,t->cod,t);
  if (t->f) {
    gerar_arvore_balanceada(t->f);
  }
  if (t->i) {
    gerar_arvore_balanceada(t->i);
  }
}


//menu de buscar
void menuEditar(){
    int op,v1=0;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Editar os Dados\n\n"COLOR_RESET);
        printf("1 - Editar por um Codigo\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o Codigo a ser Editado: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&v1);
            //Para inserir a Busca e Edição
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle ENTER para continuar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//menu de buscar
void menuRemover(){
    int op,v1=0;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Remover um No\n\n"COLOR_RESET);
        printf("1 - Remover por um Codigo\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o Codigo a ser Removido: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&v1);
            //Para inserir a busca e Remoção
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle ENTER para continuar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//menu de insercoes
void menuBusca(){
    int op,v1=0;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Gerar uma Busca\n\n"COLOR_RESET);
        printf("1 - Buscar por um Codigo\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o Codigo da Busca: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&v1);
            busca(t,v1);
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle ENTER para continuar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//menu de insercoes
void menuInsercoes(){
    int op;
    int pai;
    int cod;
    float v1=0,v2=0,v3=0;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"O Tipo de Insercao\n\n"COLOR_RESET);
        printf("1 - Inserir um Quadrado\n");
        printf("2 - Inserir um Circulo\n");
        printf("3 - Inserir um Retangulo\n");
        printf("4 - Inserir um Triangulo\n");
        printf("5 - Inserir um Trapezio\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o Código do Pai: ");
            scanf("%d",&pai);
            TAG *no_pai = busca(t,pai);
            if (!no_pai) {
              printf(COLOR_RED"O nó %d não foi localizado!"COLOR_RESET,pai);
            } else {
              printf("\nDigite o Código do novo nó: ");
              scanf("%d",&cod);
              // veriica se já existe um nó com esse código
              TAG *novo_no = busca(t,cod);
              if (novo_no) {
                printf(COLOR_RED"Já existe um nó com o código %d!"COLOR_RESET,cod);
              } else {
                printf("\nDigite o Lado do Quadrado: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);

                insere_filho_quadrado(no_pai,cod,v1);
                imprimir_status_filhos(no_pai);
              }
            }
            break;
        case 2:
            printf("\nDigite o Lado do Circulo: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v1);
            //insere_filho_circulo(busca(t,pai),cod,v1);
            break;
        case 3:
            printf("\nDigite o Primeiro Lado do Retangulo: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v1);
            printf("\nDigite o Segundo Lado do Retangulo: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v2);
            //insere_filho_retangulo(busca(t,pai),cod,v1,v2);
            break;
        case 4:
            printf("\nDigite o Primeiro Lado do Triangulo: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v1);
            printf("\nDigite o Segundo Lado do Triangulo: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v2);
            //insere_filho_triangulo(busca(t,pai),cod,v1,v2);
            break;
        case 5:
            printf("\nDigite o Primeiro Lado do Trapezio: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v1);
            printf("\nDigite o Segundo Lado do Trapezio: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v2);
            printf("\nDigite o Terceiro Lado do Trapezio: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%f",&v3);
            //insere_filho_trapezio(busca(t,pai),cod,v1,v2,v3);
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle ENTER para continuar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//menu de impressões
void menuImpressoes(){
    int op;
    int cod_no;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"O Tipo de Impressao\n\n"COLOR_RESET);
        printf("1 - Impressao de status de um nó\n");
        printf("2 - Impressao da arvore generica formato dir\n");
        printf("3 - Impressao da arvore generica formato arvore\n");
        printf("4 - Impressao da arvore Binaria Balanceada\n");
        printf("5 - Gerar DOT para impressao externa (extra)\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o código do nó: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&cod_no);
            TAG *aux = busca(t, cod_no);
            if (!aux) {
              printf(COLOR_RED"O nó %d não foi localizado!"COLOR_RESET,cod_no);
            } else {
              imprimir_status_filhos(aux);
            }
            break;
        case 2:
            imprime_semi_bonito(t);
            break;
        case 3:
            imprime_arvore_generica_como_binaria(t,"Árvore genérica binária");
            break;
        case 4:
            gerar_arvore_balanceada(t);
            print_tree(avl,"Árvore Balanceada (AVL)");
            break;
        case 5:
            gerar_dot_arvore_generica(t);
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle ENTER para continuar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//sobre os integrantes do grupo
void menuSobre(){
    system("clear");
    setbuf(stdin,NULL);
    for(int i=0;i<79;i++)
        printf("%c",'#');
    printf("\n\n");
    printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
    printf(COLOR_RED"Professora Isabel Rosseti\n"COLOR_RESET);
    printf("Integrantes do grupo:\n");
    printf("Andre Montevecchi\n");
    printf("Anselmo Battisti\n");
    printf("Flavio Miranda de Farias\n\n");
    printf("Tecle ENTER para continuar\n\n");
    printf("\n");
    for(int i=0;i<79;i++)
        printf("%c",'#');
    printf(COLOR_BLUE"\n---> "COLOR_RESET);
    setbuf(stdin,NULL);
    getchar();
    setbuf(stdin,NULL);
}
//menu principal
int menu(){
    int op;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Arvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Arvore Generica\n\n"COLOR_RESET);
        printf("1 - Impressoes\n");
        printf("2 - Insercao\n");
        printf("3 - Buscar\n");
        printf("4 - Remover\n");
        printf("5 - Editar\n");
        printf("6 - Gerar Arvore de Busca Balanceada\n");
        printf("9 - Sobre o Grupo\n");
        printf("0 - Para sair\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            menuImpressoes();
            break;
        case 2:
            menuInsercoes();
            break;
        case 3:
            menuBusca();
            break;
        case 4:
            menuRemover();
            break;
        case 5:
            menuEditar();
            break;
        case 6:
            //ATENÇÃO PARA ESTE MENU
            gerar_arvore_balanceada(t);
            printf("\nArvore balanceada Gerada\n");
            imprime_arvore_generica_como_binaria(t,"Bin");
            printf("\nTecle ENTER para continuar\n\n");
            printf("\n");
            for(int i=0;i<79;i++)
                printf("%c",'#');
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
            break;
        case 51:
            processar_testes();
            break;
        case 9:
            menuSobre();
            break;
        case 0:
            system("clear");
            printf(COLOR_CYAN "\nDestruindo arvore generica...\n\n"COLOR_RESET);
            destruir_arvore(t);
            printf(COLOR_CYAN "Arvore destruida com sucesso!\n\n"COLOR_RESET);
            printf(COLOR_BLUE"SAINDO...\n\n"COLOR_RESET);
            exit(0);
        default:
            break;
        }
        setbuf(stdin,NULL);
    }
}
