# Ficha P1

## Exercício 1 

### a)

#### Algoritmo 

- Começa no nó que não tem indegrees (indegree == 0).
- "Remove-se" as saídas do vértice já processado
- Processa-se o próximo nó que não tem edges a entrar

Errado, seguindo o algoritmo só existe duas alternativas
> **1.** [1,2,3,4,5,7,6]   
> **2.** [1,2,4,3,6,5,7] 

Seguindo o algoritmo e de forma correta

> **1.** [1,2,5,4,3,7,6]   
> **2.** [1,2,5,4,7,3,6]


## Exercício 3

### a) Strong Connected Components

[1,2,0],[3], [7], [4,5,6]

Um vértice em que não existe edges de saída, ou tem uma edge que se destina a ele mesmo, forma um strong connected component composto por si mesmo.

#### Notas:

**Tree Edge** -  Edge regular de nó pai para o descendente direto.  
**Forward Edge** - Edge de um nó ancestral para um nó descendente não direto.  
**BackWard Edge** - Edge de nó que volta para um nó ancestral.  
**Cross Edge** - Edge que vai de um nó de um ramo para outro nó de outro ramo.