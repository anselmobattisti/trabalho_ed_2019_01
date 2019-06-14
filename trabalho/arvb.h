typedef struct ArvB{
  void* no_fig;
  int nchaves, folha, *chave;
  struct ArvB **filho;
}TAB;

TAB *Cria(int t);

TAB *Libera(TAB *a);

void ImprimeB(TAB *a, int andar);

TAB *Busca(TAB* x, int ch);

TAB *Inicializa();

TAB *Divisao(TAB *x, int i, TAB* y, int t);

TAB *Insere_Nao_Completo(TAB *x, int k, int t);

TAB *InsereB(TAB *T, int k, int t);

TAB* remover(TAB* arv, int ch, int t);

TAB* retiraB(TAB* arv, int k, int t);

