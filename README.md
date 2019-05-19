# Trabalho Árvore Genérica

## Lógica

Cada nó da árvore é do tipo TAG (tipo árvore geométrica). Esse nó é composto por dois campos principais, f e i. O campo f indica se aquele nó tem filhos e o compo i indica se o nó tem irmão.

Toda vez que um filho é inserido em um determinado nó, é necessário acessar o ponteiro filhos do nó e a partir dai ir navegado pelo ponteiro i que tem os irmãos.

O nó abaixo possui 3 filhos. Para navegar por todos eles é necessário primeiro acessar a variável f e apartir do segundo elemento deve-se navegar pela lista de irmãos, uma vez que o segundo elemento pode ter filhos, logo, a variável f do primeiro filho representam os seus filhos e não os seus irmãos!

+----------------------+
| Cod         : 1
| Tipo        : q
| Filhos      : 3
| Area        : 16.00
| Area Filhos : 71.80
| Area Total  : 87.80
+-----------------------+


## Compilar

`` gcc -o prog main.c tree.c

Para rodar o programa basta executar

./prog < es.txt

onde es é o arquivo no formato dela

## Escopo

## Informações Importante

