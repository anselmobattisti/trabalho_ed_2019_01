#define TIPO_QUADRADO 1
#define TIPO_CIRCULO 2
#define TIPO_RETANGULO 3
#define TIPO_TRIANGULO 4
#define TIPO_TRAPEZIO 5

typedef struct dado {
  int tipo;
  void* fig;
  float area;
}TDADO;

typedef struct quadrado {
  float l;
}TQUADRADO;

typedef struct circulo {
  float r;
}TCIRCULO;

typedef struct retangulo {
  float l;
  float a;
}TRETANGULO;

typedef struct triangulo {
  float b;
  float a;
}TTRIANGULO;

typedef struct trapezio {
  float b1;
  float b2;
  float h;
}TTRAPEZIO;

typedef struct ag {
  int cod;
  TDADO *fig;
  struct ag *f; // lista de filhos
  struct ag *i; // lista de irmãos
}TAG;

/*
Cria uma nova árvore. Para cada filho inserido é necessário
criar a sua árvore uma vez que cada nó pode ter
seus próprios filhos
*/
TAG* cria_arvore(int cod, TDADO* fig);

/*
  Retorna o número de filhos, se 0 não tem filhos
*/
int tem_filhos();
/*
@todo precisa ser feita
*/
int tem_irmaos();

/*
  Cria um objetivo do tipo quadrado
*/
TDADO *cria_quadrado(float l);

/*
  Insere em uma determinada árvore um novo nó que é um quadrado
*/
TAG* insere_filho_quadrado(TAG *t, int cod, float l);

TDADO *cria_circulo(float r);
TAG* insere_filho_circulo(TAG *t, int cod, float r);
TAG* altera_filho_circulo(TAG *t, int cod, float r);

TDADO *cria_retangulo(float l, float a);
TAG* insere_filho_retangulo(TAG *t, int cod, float l, float a);

TDADO *cria_triangulo(float b, float a);
TAG* insere_filho_triangulo(TAG *t, int cod, float b, float a);

TDADO *cria_trapezio(float b1, float b2, float h);
TAG* insere_filho_trapezio(TAG *t, int cod, float b1, float b2, float h);

TAG* busca(TAG* t, int cod);
TAG* busca_it(TAG* t, int cod);

void busca_tipo(TAG* t, int tipo);
void busca_tipo_rec(TAG* t, int tipo, float* total);


/*
Dado um nó da árvore ele imprime os dados
do nó e dos seus filhos
*/
void gerar_dot_arvore_generica(TAG* t);
/*
  o tipo indica se o próximo nó é um pai ou filho
  usado para criar setas com cores diferentes.
*/
void gerar_dot_arvore_generica_no(TAG* t, int pai, int tipo);
void imprimir_status_arvore(TAG *t);
void imprimir_status_filhos(TAG *t);

/*
nao_imprimir indica o codigo do pai que não precisa ser impresso
*/
void imprimir_como_dir(TAG *t, int nivel, int nao_imprimir);
void imprime_arvore_generica_como_binaria(TAG* t, char* title);
void print2DUtilGen(TAG *root, int space);

/*
  Função auxiliar que retorna o nome do tipo da figura
*/
char* nome_tipo(int tipo);

/*
  Soma todas as áreas dos nós filhos (apenas o primeiro nível)
  de um determinado nó
*/
float area_filhos(TAG *t);

/*
  Retorna a área total de todas as figuras da árvre
*/
float area_total (TAG* t);

/*
  Imprime em formato de árvore de diretório
*/
void imprime_semi_bonito(TAG *t);

int num_descendentes(TAG *t);

/*
Destroi a arvore todinha
*/
void destruir_arvore(TAG *t);

/*
Removendo um nó
*/
void retira(TAG*t, TAG*pai, int cod, TAG* novo_pai);
void mover_no_remover(TAG* t, TAG* pai, TAG* novo_pai);
void mover_no(TAG* t, TAG* pai, TAG* novo_pai);
char* dimensoes_tipo(TDADO* fig);


TAG* altera_filho_quadrado(TAG *t, int cod, float l);
TAG* altera_filho_circulo(TAG *t, int cod, float r);
TAG* altera_filho_retangulo(TAG *t, int cod, float l, float a);
TAG* altera_filho_triangulo(TAG *t, int cod, float b, float a);
TAG* altera_filho_trapezio(TAG *t, int cod, float b1, float b2, float h);

/*
Dado um nó encontra quem é o seu pai;
*/
TAG* no_pai(TAG* t, TAG *pai, int cod);

/*
Gera a árvore atual no mesmo formato da importação
*/
void export_nodes(TAG* t, TAG* pai);

char* nome_tipo_grafico(int tipo);