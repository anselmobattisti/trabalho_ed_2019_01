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

`` gcc -o prog main.c tree.c

Para rodar o programa basta executar

./prog < es.txt

onde es é o arquivo no formato dela

## Escopo

## Informações Importante

## O que precisa fazer

* Implementar um menu para chamar as funções (flavio)
* Implementar o remover (andré)
* Implementar a função que transforma essa árvore em uma árvore binária de busca pelos ids (tenho uma ideia)
* Imprimir bonitinho (flavio)