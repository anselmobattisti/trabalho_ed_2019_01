#define TIPO_QUADRADO 1
#define TIPO_CIRCULO 2

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

typedef struct ag {
  int cod;
  TDADO *fig;
  struct ag *f; // lista de filhos
  struct ag *i; // lista de irmãos
}TAG;

TAG* insere_filho_quadrado(TAG *t, int cod, float l);
TAG* insere_filho_circulo(TAG *t, int cod, float r);

int tem_filhos();
int tem_irmaos();


TAG* busca(TAG* t, int cod);

TAG* cria_arvore(int cod, TDADO* fig);

TDADO *cria_quadrado(int l);
TDADO *cria_circulo(float r);

void imprimir_status_arvore(TAG *t);
void imprimir_status_filhos(TAG *t);

void imprimir_filhos(TAG *t);

char* nome_tipo(int tipo);

float area_filhos(TAG *t);