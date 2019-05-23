# Trabalho Árvore Genérica

## Lógica

Cada nó da árvore é do tipo TAG (tipo árvore geométrica). Esse nó é composto por dois campos principais, f e i. O campo f indica se aquele nó tem filhos e o compo i indica se o nó tem irmão.

Toda vez que um filho é inserido em um determinado nó, é necessário acessar o ponteiro filhos do nó e a partir dai ir navegado pelo ponteiro i que tem os irmãos.

O nó abaixo possui 3 filhos. Para navegar por todos eles é necessário primeiro acessar a variável f e apartir do segundo elemento deve-se navegar pela lista de irmãos, uma vez que o segundo elemento pode ter filhos, logo, a variável f do primeiro filho representam os seus filhos e não os seus irmãos!

```
===> PAI
+----------------------+
| Cod         : 1
| Tipo        : qua
| Filhos      : 3
| Area        : 16.00
| Area Filhos : 16.00
| Area Total  : 32.00
+-----------------------+

===> Filho (1)

+----------------------+
| Cod         : 2
| Tipo        : tra
| Filhos      : 0
| Area        : 6.00
| Area Filhos : 0.00
| Area Total  : 6.00
+-----------------------+

===> Filho (2)

+----------------------+
| Cod         : 3
| Tipo        : qua
| Filhos      : 0
| Area        : 9.00
| Area Filhos : 0.00
| Area Total  : 9.00
+-----------------------+

===> Filho (3)

+----------------------+
| Cod         : 4
| Tipo        : qua
| Filhos      : 1
| Area        : 1.00
| Area Filhos : 16.00
| Area Total  : 17.00
+-----------------------+
```

## Compilar

```
  gcc -o prog main.c tree.c avl.c
```

Para rodar o programa basta executar

./prog < es.txt

onde es é o arquivo no formato dela

## Casos de Teste

Estão na pasta testes

```
gcc -o prog main_testes.c ../tree.c ../avl.c testes.c
```

## Escopo

Trabalho Computacional: implementação das funções de árvores genéricas no número de filhos, árvores n-árias, e no tipo de informação armazenada, testando com as seguintes figuras geométricas: círculo, quadrado, retângulo, trapézio e triângulo: deve ser permitido ao usuário do sistema:

* 1  - OK (a) buscar figuras geométricas, por meio de um código único;
* 2  - OK (b) imprimir informações relevantes, tanto da árvore, quanto das figuras, incluindo-se sua área;
* 3  - OK (c) inserir novas figuras;
* 4  -(d) retirar figuras, passando seus descendentes para outro pai;
* 5  -(e) destruir a árvore; e
* 6  -(f) alterar as dimensões de figuras;
* 7  - OK transformar a árvore genérica numa árvore binária de busca balanceada, baseando-se no código único;
* 8  - Converter a árvore genérica numa árvore B, baseando-se no código único;
* 9  - OK a entrada será fornecida por meio de arquivos texto. O arquivo texto será composto das seguintes informações, separadas por '/': código único, código único do pai (sendo que a raiz tem código do pai igual a zero) e as figuras geométricas, incluindo seu nome;
* 10 - OK as dimensões das figuras geométricas obedecerão ao seguinte padrão: (a) se a figura for um círculo ou um quadrado, uma única dimensão será informada (ou o raio, ou o lado, respectivamente); (b) se a figura for um triângulo ou um retângulo, as duas dimensões informadas serão a base e a altura; e, por fim, (c) se a figura for um trapézio, três dimensões serão informadas, nessa ordem, base menor, base maior e altura;
* 11 - OK exemplo de arquivo fornecido. PORÉM, SEU CÓDIGO DEVE FUNCIONAR COM QUALQUER ENTRADA QUE SEGUE O PADRÃO SUPRACITADO;
* 12 - A estrutura deve ser totalmente destruída pelo seu programa antes da execução ser finalizada;

## Informações Importante

## O que precisa fazer

* Implementar um menu para chamar as funções (flavio)
* Implementar o remover (andré)
* Implementar a função que transforma essa árvore em uma árvore binária de busca pelos ids (tenho uma ideia)
* Imprimir bonitinho (flavio)
-* Colocar na impressão dos nós os dados dos campos da figura geométrica e não apenas da área (anselmo)-