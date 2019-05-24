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

void edita_figura(int fig, int cod, TAG *no){
    float v1, v2, v3;
    TAG *novo;
    if(fig==1){
        printf("\nDigite o Lado do Quadrado: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        altera_filho_quadrado(no,cod,v1);
    }
    if(fig==2){
        printf("\nDigite o Lado do Círculo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        altera_filho_circulo(no,cod,v1);
    }
    if(fig==3){
        printf("\nDigite o Primeiro Lado do Retângulo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        printf("\nDigite o Segundo Lado do Retângulo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v2);
        altera_filho_retangulo(no,cod,v1,v2);
    }
    if(fig==4){
        printf("\nDigite o Primeiro Lado do Triângulo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        printf("\nDigite o Segundo Lado do Triângulo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v2);
        altera_filho_triangulo(no,cod,v1,v2);
    }
    if(fig==5){
        printf("\nDigite a Base Menor do Trapézio: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        printf("\nDigite a Base Maior do Trapézio: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v2);
        printf("\nDigite a Altura do Trapézio: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v3);
        altera_filho_trapezio(no,cod,v1,v2,v3);
    }
    imprimir_status_filhos(no);
    printf(COLOR_BLUE"\nO nó com o código "COLOR_GREEN"%d "COLOR_BLUE"foi Alterado!\n"COLOR_RESET,cod);
}
//menu de editar
void menuEditar(){
    int op1,op2,cod=0;
    while(op1!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Editar os Dados\n\n"COLOR_RESET);
        printf("1 - Para Editar\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op1);
        switch(op1){
        case 1:
            printf("\nDigite o Código da Busca: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&cod);
            TAG *aux = busca(t,cod);
            imprimir_status_arvore(aux);
            if(aux) {
                setbuf(stdin,NULL);
                printf(COLOR_GREEN"\nEscolha uma das opções\n\n"COLOR_RESET);
                printf("1 - Alterar para um Quadrado\n");
                printf("2 - Alterar para um Círculo\n");
                printf("3 - Alterar para um Retângulo\n");
                printf("4 - Alterar para um Triângulo\n");
                printf("5 - Alterar para um Trapézio\n");
                printf("0 - Para retornar\n\n");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%d",&op2);
                switch(op2){
                    case 0:
                        menu();
                        break;
                    default:
                        edita_figura(op2,cod,aux);
                        break;
                }
            } else
                printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,cod);
            break;
        case 0:
            menu();
            break;
        default:
            break;
        }
        printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}

void remover_no(TAG *no, int cod){

    //ANDRÉ, PODE CHAMAR SUA FUNÇÃO AQUI PRA SEGUIR O ESQUEMA DOS OUTROS MENUS SE PREFERIR

    if(no){
        printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"foi Removido!\n"COLOR_RESET,cod);
    }else{
        printf(COLOR_RED"\nNão foi possivel Remover o nó com o código "COLOR_GREEN"%d\n"COLOR_RESET,cod);
    }
}
//menu de remover
void menuRemover(){
    int op,cod;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Remover um Nó\n\n"COLOR_RESET);
        printf("1 - Para Remover\n");
        printf("0 - Para retornar\n\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\nDigite o Código a ser Removido: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%d",&cod);
                TAG *aux = busca(t,cod);
                if(aux){
                  imprimir_status_arvore(aux);
                  remover_no(aux,cod);
                } else
                     printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,cod);
                break;
            case 0:
                menu();
                break;
            default:
                break;
        }
        printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n");
        printf(COLOR_BLUE"---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
//menu de busca
void menuBusca(){
    int op,cod;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Gerar uma Busca\n\n"COLOR_RESET);
        printf("1 - Para Buscar por um Nó\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\nDigite o Código da Busca: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%d",&cod);
                TAG *aux = busca(t,cod);
                if(aux)
                    imprimir_status_arvore(busca(t,cod));
                else
                     printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,cod);
                break;
            case 0:
                menu();
                break;
            default:
                break;
        }
        printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        setbuf(stdin,NULL);
        getchar();
        setbuf(stdin,NULL);
    }
}
void insere_figura(int fig){
    int pai, cod;
    float v1, v2, v3;
    printf("\nDigite o Código do Pai: ");
    printf(COLOR_BLUE"\n---> "COLOR_RESET);
    scanf("%d",&pai);
    TAG *no_pai = busca(t,pai);
    if (!no_pai)
        printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,pai);
    else {
        printf("\nDigite o Código do novo nó: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&cod);
        // veriica se já existe um nó com esse código
        TAG *novo_no = busca(t,cod);
        if (novo_no)
            printf(COLOR_RED"\nJá existe um nó com o código "COLOR_GREEN"%d"COLOR_RESET,cod);
        else {
            if(fig==1){
                printf("\nDigite o Lado do Quadrado: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                insere_filho_quadrado(no_pai,cod,v1);
            }
            if(fig==2){
                printf("\nDigite o Lado do Círculo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                insere_filho_circulo(no_pai,cod,v1);
            }
            if(fig==3){
                printf("\nDigite o Primeiro Lado do Retângulo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                printf("\nDigite o Segundo Lado do Retângulo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v2);
                insere_filho_retangulo(no_pai,cod,v1,v2);
            }
            if(fig==4){
                printf("\nDigite o Primeiro Lado do Triângulo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                printf("\nDigite o Segundo Lado do Triângulo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v2);
                insere_filho_triangulo(no_pai,cod,v1,v2);
            }
            if(fig==5){
                printf("\nDigite a Base Menor do Trapézio: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                printf("\nDigite a Base Maior do Trapézio: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v2);
                printf("\nDigite a Altura do Trapézio: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v3);
                insere_filho_trapezio(no_pai,cod,v1,v2,v3);
            }
            imprimir_status_filhos(no_pai);
        }
    }
}
//menu de insercoes
void menuInsercoes(){
    int op;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"O Tipo de Inserção\n\n"COLOR_RESET);
        printf("1 - Para Inserir um Quadrado\n");
        printf("2 - Para Inserir um Círculo\n");
        printf("3 - Para Inserir um Retângulo\n");
        printf("4 - Para Inserir um Triângulo\n");
        printf("5 - Para Inserir um Trapézio\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 0:
            menu();
            break;
        default:
            insere_figura(op);
            break;
        }
        printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
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
    int op, cod_no;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"O Tipo de Impressão\n\n"COLOR_RESET);
        printf("1 - Para Impressão de status de um nó\n");
        printf("2 - Para Impressão da árvore generica formato dir\n");
        printf("3 - Para Impressão da árvore generica formato arvore\n");
        printf("4 - Para Impressão da árvore Binaria Balanceada\n");
        printf("5 - Para Gerar DOT para impressão externa (extra)\n");
        printf("0 - Para retornar\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
        case 1:
            printf("\nDigite o código do nó: ");
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            scanf("%d",&cod_no);
            TAG *aux = busca(t, cod_no);
            if (!aux)
              printf(COLOR_RED"O nó %d não foi localizado!"COLOR_RESET,cod_no);
            else
              imprimir_status_filhos(aux);
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
        printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
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
    printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
    printf(COLOR_RED"Professora Isabel Rosseti\n"COLOR_RESET);
    printf("Integrantes do grupo:\n");
    printf("Andre Montevecchi\n");
    printf("Anselmo Battisti\n");
    printf("Flávio Miranda de Farias\n\n");
    printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
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
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Árvore Genérica\n\n"COLOR_RESET);
        printf("1 - Impressões\n");
        printf("2 - Inserção\n");
        printf("3 - Buscar\n");
        printf("4 - Remover\n");
        printf("5 - Editar\n");
        printf("6 - Gerar Árvore de Busca Balanceada\n");
        printf("9 - Sobre o Grupo\n");
        printf("0 - Para sair\n\n");
        printf("\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
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
            gerar_arvore_balanceada(t);
            print_tree(avl,"Árvore Balanceada (AVL)");
            printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
            for(int i=0;i<79;i++)
                printf("%c",'#');
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
            break;
        case 9:
            menuSobre();
            break;
        case 0:
            system("clear");
            printf(COLOR_CYAN "\nDestruindo arvore genérica...\n\n"COLOR_RESET);
            destruir_arvore(t);
            printf(COLOR_CYAN "Árvore destruida com sucesso!\n"COLOR_RESET);
            printf(COLOR_BLUE"\nSAINDO...\n\n"COLOR_RESET);
            exit(0);
        case 51:
          processar_testes();
          break;
        default:
            break;
        }
        setbuf(stdin,NULL);
    }
}
