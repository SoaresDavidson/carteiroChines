# Problema do Carteiro Chinês

## Carteiro Chinês  
**Uma implementação e análise de algoritmo**

Trabalho apresentado na disciplina **Teoria e Aplicação em Grafos** – Universidade Federal do Piauí.

---

## Membros do grupo

- Victor Kauan da Silva Miranda  
- Luanderson Carvalho de Oliveira  
- João Pedro Saleh de Sousa  
- Davi Sousa Soares

---

## Objetivo

Neste trabalho, demonstramos uma aplicação do **algoritmo do carteiro chinês em C++** e avaliamos o desempenho computacional do programa.  
Também comparamos os algoritmos de **Hierholzer** e **Fleury** para encontrar ciclos eulerianos, com e sem **heurísticas de emparelhamento**.

---

## Ciclo de Execução

### EMPARELHAMENTO  
Busca o número de emparelhamentos possíveis dos vértices de grau ímpar.

### DIJKSTRA  
Calcula o caminho mínimo entre os vértices emparelhados.

### DUPLICAÇÃO DAS ARESTAS  
Guarda os caminhos encontrados e aplica no grafo original.

### HIERHOLZER OU FLEURY  
Constrói um ciclo euleriano a partir do grafo gerado.

---

## Execução

### O problema do emparelhamento

Em grafos não direcionados, o aumento do número de vértices ímpares eleva a complexidade de forma **duplo fatorial**:

- 4 vértices ímpares → `O(4!!) = 3` emparelhamentos  
- 6 vértices ímpares → `O(6!!) = 15` emparelhamentos  
- 10 vértices ímpares → `O(10!!) = 945` emparelhamentos  
- 24 vértices ímpares → `O(24!) = 316.234.143.255` emparelhamentos

## Heurística para Emparelhamento

Substituímos a comparação linear tradicional por uma sequência baseada em potências de 2:

- Exemplo: o vértice 1 compara com 2, depois com 4, depois com 8, etc., até `n²` (onde `n² < quantidade de vértices`).

---

## Otimização do Dijkstra

### Problema:

Para cada emparelhamento entre vértices ímpares é necessário uma execução do Dijkstra.

### Solução:

Como muitos caminhos se repetem, podemos usar **programação dinâmica** para armazenar os resultados e **evitar recomputações**, trocando esforço computacional por uso de memória.

---

## Comparação: Hierholzer vs Fleury

### Algoritmo de Hierholzer

- Forma ciclos fechados a partir de vértices até percorrer todas as arestas.
- Une os ciclos em um único circuito euleriano.  
- **Complexidade:** `O(V + E)`

### Algoritmo de Fleury

- Evita pontes, a menos que sejam únicas.
- Percorre arestas removendo-as progressivamente.  
- **Complexidade:** `O(E²)`

---

