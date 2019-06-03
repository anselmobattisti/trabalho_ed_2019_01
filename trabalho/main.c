#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "avl.h"
#include "arvb.h"
#include "../testes/testes.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

TAG *a;
node* avl;
TAB *b;

void processar_entrada();
void gerar_arvore_balanceada(TAG* a);
void gerar_arvore_b(TAG* a);

int menu();

int main() {
    processar_entrada();
    menu();
    return 0;
}

/*
  A partir do arquivo popula a árvore
*/void processar_entrada() {
  TAG* ret_inserir = NULL;
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
      if (a) {
        printf(COLOR_RED"\n\n* "COLOR_RESET"A árvore não pode ter duas raízes.\n"COLOR_RESET);
        exit(1);
      } else {
        if (strcmp(tipo,"QUA") == 0) {
          a = cria_arvore(cod,cria_quadrado(v1));
        }
        if (strcmp(tipo,"CIR") == 0)
          a = cria_arvore(cod,cria_circulo(v1));
        if (strcmp(tipo,"RET") == 0)
          a = cria_arvore(cod,cria_retangulo(v1,v2));
        if (strcmp(tipo,"TRI") == 0)
          a = cria_arvore(cod,cria_triangulo(v1,v2));
        if (strcmp(tipo,"TRA") == 0)
          a = cria_arvore(cod,cria_trapezio(v1,v2,v3));
      }
    }

    if (pai > 0) {
      TAG* existe_no = busca(a,cod);
      if (existe_no) {
        //imprimir_status_arvore(existe_no);
        printf(COLOR_RED"\n\n* "COLOR_RESET"ERRO, O nó %d já existe na árvore.\n"COLOR_RESET,cod);
        exit(1);
      } else {
        if(strcmp(tipo,"QUA") == 0)
          ret_inserir = insere_filho_quadrado(busca(a,pai),cod,v1);
        if (strcmp(tipo,"CIR") == 0)
          ret_inserir = insere_filho_circulo(busca(a,pai),cod,v1);
        if (strcmp(tipo,"RET") == 0)
          ret_inserir = insere_filho_retangulo(busca(a,pai),cod,v1,v2);
        if (strcmp(tipo,"TRI") == 0)
          ret_inserir = insere_filho_triangulo(busca(a,pai),cod,v1,v2);
        if (strcmp(tipo,"TRA") == 0)
          ret_inserir = insere_filho_trapezio(busca(a,pai),cod,v1,v2,v3);

        if (!ret_inserir) {
        printf(COLOR_RED"\n\nErro na leitura do arquivo de entrada!"COLOR_RESET);
        printf("\nNão foi possível inserir o nó"COLOR_YELLOW" %d,"COLOR_RESET" pois o nó pai "COLOR_YELLOW"%d "COLOR_RESET"não existe na árvore."COLOR_RESET,pai,cod);
        printf(COLOR_BLUE"\nReinicie a aplicação ao corrigir o erro.\n\n"COLOR_RESET);
        exit(1);
        }
      }
    }
    ret_inserir = NULL;
  }
}

/*
 Percorre a árvore genérica e inserer na árvore AVL
*/
void gerar_arvore_balanceada(TAG* a) {
  if (!a) return;
  avl = insert(avl,a->cod,a);
  if (a->f) {
    gerar_arvore_balanceada(a->f);
  }
  if (a->i) {
    gerar_arvore_balanceada(a->i);
  }
}

/*
 Percorre a árvore genérica e inserer na árvore B
*/
void gerar_arvore_b(TAG* a) {
    if (!a) return;
        b = InsereB(b,a->cod,2);
        //ArvB = insert(ArvB,t->cod,t);
    if (a->f)
        gerar_arvore_b(a->f);
    if (a->i)
        gerar_arvore_b(a->i);
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
        printf("\nDigite o Raio do Círculo: ");
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
        printf("\nDigite a Base do Triângulo: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%f",&v1);
        printf("\nDigite a Altura do Triângulo: ");
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
            TAG *aux = busca(a,cod);
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
                TAG *aux = busca(a,cod);
                int cod_novo_pai = 0;
                if(aux){
                  // se o nó tem filho e tem irmãos então temos que escolher quem será o novo pai
                  TAG* t_novo_pai = NULL;
                  if (aux->f != NULL && aux->i != NULL) {
                    // Vamor perguntar pro cara o ID do novo pai!
                    while (!t_novo_pai && cod_novo_pai != -1) {
                      printf("\nO novo pai pode ser um dos nós abaixo\n");
                      imprimir_como_dir(a,1,cod);
                      printf("------------\n");
                      printf("\nO nó %d possui filhos, digite o código do novo pai: ",aux->cod);
                      scanf("%d",&cod_novo_pai);
                      if (cod_novo_pai != aux->cod) {
                        t_novo_pai = busca(a,cod_novo_pai);
                        if (!t_novo_pai && cod_novo_pai != -1) {
                          printf(COLOR_RED"Código do novo pai dos filhos de %d não encontrado, digite o novo código ou -1 para voltar."COLOR_RESET,aux->cod);
                        }
                        // verifica se o novo pai não está na subárvore do nó que será removido
                        TAG* no_na_sub = busca(aux->f, cod_novo_pai);
                        if (no_na_sub) {
                          t_novo_pai = NULL;
                          printf(COLOR_RED"Código do novo pai NÃO pode ser descendente de %d."COLOR_RESET,aux->cod);
                        }
                      } else {
                        printf(COLOR_RED"Código novo pai não pode ser ele mesmo."COLOR_RESET);
                      }
                    }
                  }
                  // tentando mover os filhos dele para ele mesmo
                  if (cod_novo_pai == cod) {
                      printf(COLOR_RED"Código novo pai não pode ser ele mesmo."COLOR_RESET);
                  } else {
                    if (cod_novo_pai != -1) {
                      // imprimir_status_arvore(t_novo_pai);
                      printf("\nAntes da remoção de %d.",cod);
                      imprime_semi_bonito(a);
                      retira(a, a, cod, t_novo_pai);
                      printf("\nDepois da remoção de %d.",cod);
                      imprime_semi_bonito(a);
                    } else {
                      printf("\nVocê não escolheu o novo pai.");
                    }
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

//menu de remover
void menuMover(){
    int op,cod;
    TAG* pai_aux = NULL;
    int cod_novo_pai = 0;
    while(op!='0'){
        setbuf(stdin,NULL);
        system("clear");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf("\n\n");
        printf(COLOR_YELLOW"Trabalho sobre Árvores de EDA - 2019.1\n\n"COLOR_RESET);
        printf(COLOR_RED"Digite o valor do menu a baixo para: "COLOR_RESET);
        printf(COLOR_GREEN"Remover um Nó\n\n"COLOR_RESET);
        printf("1 - Para Mover\n");
        printf("0 - Para retornar\n\n");
        for(int i=0;i<79;i++)
            printf("%c",'#');
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&op);
        switch(op){
            case 1:
                printf("\nDigite o Código do Nó a ser Movido: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%d",&cod);
                TAG *aux = busca(a,cod);

                if (a->cod == aux->cod) {
                  printf(COLOR_RED"\nA raiz não pode ser movida.\n"COLOR_RESET);
                  break;
                }
                cod_novo_pai = 0;
                // acha o pai do nó que foi digitado
                pai_aux = no_pai(a,a,cod);
                if(aux){
                  // se o nó tem filho e tem irmãos então temos que escolher quem será o novo pai
                  TAG* t_novo_pai = NULL;
                  // Vamor perguntar pro cara o ID do novo pai!
                  while (!t_novo_pai && cod_novo_pai != -1) {
                    printf("\nO novo pai pode ser um dos nós abaixo\n");
                    imprimir_como_dir(a,1,cod);
                    printf("------------\n");
                    printf("\nDigite o Código do Novo Pai (ou -1 para voltar): ");
                    scanf("%d",&cod_novo_pai);

                    if (cod_novo_pai != aux->cod) {
                      t_novo_pai = busca(a,cod_novo_pai);
                      if (!t_novo_pai && cod_novo_pai != -1) {
                        printf(COLOR_RED"Código do novo pai dos filhos de %d não encontrado, digite o novo código ou -1 para voltar."COLOR_RESET,aux->cod);
                      }
                      // verifica se o novo pai não está na subárvore do nó que será removido
                      TAG* no_na_sub = busca(aux, cod_novo_pai);
                      if (no_na_sub) {
                        t_novo_pai = NULL;
                        printf(COLOR_RED"Código do novo pai NÃO pode ser descendente de %d."COLOR_RESET,aux->cod);
                      }
                    } else {
                      printf(COLOR_RED"Código novo pai não pode ser ele mesmo."COLOR_RESET);
                    }
                  }
                  if (cod_novo_pai == cod || pai_aux->cod == cod_novo_pai) {
                      printf(COLOR_RED"Código novo pai não pode ser ele mesmo 2."COLOR_RESET);
                  } else {
                    if (cod_novo_pai != -1) {
                      mover_no(aux, pai_aux, t_novo_pai);
                      // imprimir_status_arvore(t_novo_pai);
                      // printf("\nAntes da remoção de %d.",cod);
                      //printf("aaaaaa");
                      //TAG* pai_aux = no_pai(a, a,cod);
                      //printf("!dddddddd");
                      //imprimir_status_arvore(aux);
                      //imprimir_status_arvore(pai_aux);
                      //imprimir_status_arvore(t_novo_pai);
                      //imprime_semi_bonito(a);
                      //imprime_semi_bonito(a);
                    } else {
                      printf("\nVocê não escolheu o novo pai.");
                    }
                  }
                } else {
                  printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,cod);
                }
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
                TAG *aux = busca(a,cod);
                if(aux)
                    imprimir_status_arvore(busca(a,cod));
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
    TAG *no_pai = busca(a,pai);
    if (!no_pai)
        printf(COLOR_RED"\nO nó com o código "COLOR_GREEN"%d "COLOR_RED"não foi localizado!\n"COLOR_RESET,pai);
    else {
        printf("\nDigite o Código do novo nó: ");
        printf(COLOR_BLUE"\n---> "COLOR_RESET);
        scanf("%d",&cod);
        // veriica se já existe um nó com esse código
        TAG *novo_no = busca(a,cod);
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
                printf("\nDigite o Raio do Círculo: ");
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
                printf("\nDigite a Base do Triângulo: ");
                printf(COLOR_BLUE"\n---> "COLOR_RESET);
                scanf("%f",&v1);
                printf("\nDigite a Altura do Triângulo: ");
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
        printf("2 - Para Impressão da árvore completa (formato hierárquico)\n");
        printf("3 - Para Impressão da árvore generica\n");
        //printf("4 - Para Impressão da árvore Binaria Balanceada (AVL)\n");
        //printf("5 - Para Impressão da árvore B\n");
        printf("4 - Para Gerar DOT para impressão externa (extra)\n");
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
            TAG *aux = busca(a, cod_no);
            if (!aux)
              printf(COLOR_RED"O nó %d não foi localizado!"COLOR_RESET,cod_no);
            else
              imprimir_status_filhos(aux);
            break;
        case 2:
            imprime_semi_bonito(a);
            break;
        case 3:
            imprime_arvore_generica_como_binaria(a,"Árvore Genérica");
            break;
            /*
        case 4:
            free_avl(avl);
            avl = NULL;
            gerar_arvore_balanceada(a);
            print_tree(avl,"Árvore Balanceada (AVL)");
            break;
        case 5:
            Libera(b);
            b = NULL;
            gerar_arvore_b(a);
            printf("\nÁrvore B Completa\n----------------\n");
            ImprimeB(b,0);
            printf("----------------\nTotal de nós: %d\n----------------\n",num_descendentes(a->f)+1);
            break;*/
        case 4:
            gerar_dot_arvore_generica(a);
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
        printf("  1 - Imprimir\n");
        printf("  2 - Inserir\n");
        printf("  3 - Buscar\n");
        printf("  4 - Remover\n");
        printf("  5 - Editar\n");
        printf("  6 - Gerar Árvore AVL\n");
        printf("  7 - Gerar Árvore B\n");
        printf("  8 - Mover Nó da Árvore\n");
        printf("  9 - Sobre o Grupo\n");
        printf(" 10 - Exportar\n");
        printf("  0 - Para sair\n\n");
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
        // case 6:
        //     print_tree(avl,"Árvore Binária de Busca\n");
        //     printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
        //     for(int i=0;i<79;i++)
        //         printf("%c",'#');
        //     printf(COLOR_BLUE"\n---> "COLOR_RESET);
        //     setbuf(stdin,NULL);
        //     getchar();
        //     setbuf(stdin,NULL);
        //     break;
        case 6:
            free_avl(avl);
            avl = NULL;
            gerar_arvore_balanceada(a);
            print_tree(avl,"Árvore Balanceada (AVL)\n");
            printf("----------------\nTotal de nós: %d\n----------------\n",num_descendentes(a->f)+1);
            printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
            for(int i=0;i<79;i++)
                printf("%c",'#');
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
            break;
        case 7:
            Libera(b);
            b = NULL;
            gerar_arvore_b(a);
            printf("\nÁrvore B Completa\n----------------\n");
            ImprimeB(b,0);
            printf("----------------\nTotal de nós: %d\n----------------\n",num_descendentes(a->f)+1);
            printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
            for(int i=0;i<79;i++)
                printf("%c",'#');
            printf(COLOR_BLUE"\n---> "COLOR_RESET);
            setbuf(stdin,NULL);
            getchar();
            setbuf(stdin,NULL);
            break;
        case 8:
            menuMover();
        case 9:
            menuSobre();
            break;
        case 51:
            system("clear");
            processar_testes();
            break;
        case 10:
          system("clear");
          printf(COLOR_GREEN"Árvore exporta no mesmo formato do arquivo de entrada\n\n"COLOR_RESET);
          setbuf(stdin,NULL);
          export_nodes(a,a);
          printf("\nTecle "COLOR_YELLOW"ENTER"COLOR_RESET" para continuar\n\n");
          getchar();
          break;
        case 0:
            system("clear");
            printf(COLOR_CYAN "Destruindo arvore genérica..."COLOR_RESET);
            destruir_arvore(a);
            printf(COLOR_CYAN "\nÁrvore destruida com sucesso!\n"COLOR_RESET);
            printf(COLOR_BLUE"\nSAINDO...\n\n"COLOR_RESET);
            exit(0);
        default:
            break;
        }
        setbuf(stdin,NULL);
    }
}
