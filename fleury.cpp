#include <iostream>
#include <bits/stdc++.h>
#include "grafo.hpp"
using namespace std;
//push_back = append, .begin = iterator que aponta pro primeiro

/*
O ALGORITMO EXECUTA UMA Tarjan_DFS, DETERMINANDO OS MENORES TEMPOS
DE DESCOBERTA DE CADA VÉRTICE CONSIDERANDO OS NÓS ADJACENTES EXCETO O NÓ PAI
*/

void Tarjan_DFS(Grafo* g, map<Vertice*, bool>& vis, Vertice* vi, Vertice* v_pai, int tempo, map<Vertice*, Vertice*> pai, map<Vertice*, int> descoberta, map<Vertice*, int> low)
{
    vis[vi] = true;
    descoberta[vi] = low[vi] = tempo++;

    for (Aresta v : vi->arestas) {
        if (v.destino == v_pai) continue;

        if(!vis[v.destino]) {
            pai[v.destino] = vi;
            Tarjan_DFS(g, vis, v.destino, vi, tempo, pai, descoberta, low);
            low[vi] = min(low[vi], low[v.destino]);
        }
        else {
            low[vi] = min(low[vi], descoberta[v.destino]);
        }
    }
}


bool serPonte(Vertice* v, Vertice* u, map<Vertice*, Vertice*> pai, map<Vertice*, int> descoberta, map<Vertice*, int> low)
{
    /*
    SE O LOW DE UM DOS VÉRTICES É MENOR QUE A DESCOBERTA DO OUTRO,
    ISSO QUER DIZER QUE ESTE VÉRTICE QUE TEM TEMPO MENOR PODE SER
    ACESSADO ANTES E AINDA ALCANÇAR O OUTRO, LOGO NÃO É UMA ARESTA DE CORTE
    OU SEJA, PARA SER ARESTA DE CORTE, O VÉRTICE U PRECISA TER O SEU MENOR TEMPO DE
    DESCOBERTA COMO MAIOR QUE O TEMPO DE DESCOBERTA DO VÉRTICE V, QUANDO
    V É PAI DE U (ARESTA V-U), ISSO PORQUE RESULTARIA EM DIZER QUE O VÉRTICE U
    NÃO PODERIA SER ALCANÇADO ANTES DO VÉRTICE V, IMPLICANDO EM UMA ARESTA
    DE CORTE
    */
    if (pai[u] == v)
    {
        return (low[u] > descoberta[v]);
    }
    else if (pai[v] == u)
    {
        return (low[v] > descoberta[u]);
    }
    return false;
}


vector<Vertice*> fleury(Grafo* g, map<Vertice*, bool>& vis, Vertice* vi, Vertice* v_pai, map<Vertice*, Vertice*> pai, int tempo, map<Vertice*, int> descoberta, map<Vertice*, int> low)
{
    Tarjan_DFS(g, vis, vi, v_pai, tempo, pai, descoberta, low);

    stack<Vertice*> pilha;
    vector<Vertice*> ciclo;
    pilha.push(vi);

    while (!pilha.empty()) {
        Vertice* u = pilha.top();

        if (u->isEmpty()) {
            ciclo.push_back(u);
            pilha.pop();
        } else {
            // Encontra o primeiro vizinho
            Vertice* v = u->arestas[0].destino;

            // Verifica se a aresta é ponte
            bool isBridge = serPonte(u, v, pai, descoberta, low);

            // Se não é ponte, remove a aresta
            if (!isBridge || u->arestas.size() == 1)
            {
                // Remove aresta u-v
                u->remover_aresta(v->id);
                v->remover_aresta(u->id);

                pilha.push(v);
            }
            else
                {
                // Se é ponte e há outras opções, procura outra aresta
                bool found = false;
                for (size_t i = 1; i < u->arestas.size(); i++)
                    {
                    v = u->arestas[i].destino;
                    if (!serPonte(u, v, pai, descoberta, low))
                        {
                        // Remove aresta u-v
                        u->remover_aresta(v->id);
                        v->remover_aresta(u->id);

                        pilha.push(v);
                        found = true;
                        break;
                        }
                    }

                // Se todas são pontes, remove a primeira
                if (!found)
                    {
                    v = u->arestas[0].destino;
                    u->remover_aresta(v->id);
                    v->remover_aresta(u->id);

                    pilha.push(v);
                    }
                }
        }
    }

    // Imprime o ciclo euleriano
    cout << "Ciclo Euleriano encontrado: ";
    for (Vertice* v : ciclo) {
        cout << v->id + 1 << " "; // +1 para ajustar a numeração (começa em 1)
    }
    cout << endl;

    return ciclo;
}


int main(){
    int v, a; cin >> v >> a;
    Grafo g(v);
    map<Vertice*, bool> visitados;

    map<Vertice*, Vertice*> pai;
    map<Vertice*, int> descoberta;
    map<Vertice*, int> low;
    int tempo = 0;

    for(int i = 0; i < a; i++){
        ll p;
        int v1, v2; cin >> v1 >> v2 >> p; 
        g.vertices[v1]->adicionar_aresta(p,g.vertices[v2],i);

    }

    fleury(&g, visitados, g.vertices[0], nullptr, pai, tempo, descoberta, low);
}