#include <iostream>
#include <bits/stdc++.h>
#include "grafo.hpp"

using namespace std;


void dfs(Grafo *g, int v, Vertice* &pai, vector<Vertice*> &sequencia, vector<vector<Vertice*>> &ciclos, vector<vector<int>> &vis) {
    Vertice* Vertice = g->vertices[v];
    for (Aresta aresta : Vertice->arestas) {
        int w = aresta.destino->id;
        if (vis[Vertice->id][w] <= 0) continue;
        vis[Vertice->id][w] -= 1;
        vis[w][Vertice->id] -= 1;
        if (Vertice->grau == 0) return;

        if (pai == nullptr) pai = Vertice;

        sequencia.push_back(Vertice);


        if (pai->id == w){
            sequencia.push_back(pai);
            ciclos.push_back(sequencia);
            sequencia.clear();
            pai = nullptr;
        }

        dfs(g, w, pai, sequencia, ciclos, vis);
    }
}

vector<Vertice*> hierholzer(Grafo* g){
    int tamanho = g->vertices.size()/2;
    vector<vector<Vertice*>> ciclos;
    vector<Vertice*> sequencia;
    Vertice* pai = nullptr;
    vector<vector<int>> vis(tamanho, vector<int>(tamanho, 0));

    for (Vertice* v : g->vertices){
        for (Aresta a : v->arestas){
            vis[v->id][a.destino->id]++;
        }
    }
    dfs(g, 0, pai, sequencia, ciclos, vis);

    vector<Vertice*> euleriano;
    for (auto& i : ciclos){
        if (euleriano.empty()){
            euleriano.insert(euleriano.begin(), i.begin(), i.end());
            continue;
        }

        auto it = find(euleriano.begin(), euleriano.end(), i[0]);
        euleriano.insert(it+1, i.begin()+1, i.end());
        i.clear();
    }
    if (!sequencia.empty()) throw runtime_error("O grafo não é euleriano!");
    return euleriano;
}

int main(){
    int v, a; cin >> v >> a;
    Grafo grafo = Grafo(v);

    for (int i = 0; i < v; i++){
        Vertice* novo = new Vertice(i);
        grafo.adicionar_vertice(novo);
    }

    for(int i = 0;i < a; i++){
        int v1, v2; cin >> v1 >> v2; v1--;v2--;
        grafo.vertices[v1]->adicionar_aresta(1, grafo.vertices[v2], i);
        grafo.vertices[v2]->adicionar_aresta(1, grafo.vertices[v1], i);
    }

    vector<Vertice*> resultado = hierholzer(&grafo);
    for(auto i : resultado){
        cout << i->id+1 << " ";
    }
    return 0;

}

// 6 10
// 1 2
// 1 3
// 2 3
// 2 4
// 2 5
// 3 4
// 3 5
// 4 5
// 4 6
// 5 6

// 6 12
// 1 2
// 2 3
// 3 6
// 6 5
// 5 4
// 4 1
// 1 5
// 2 6
// 5 3
// 1 2
// 3 5
// 5 6

// 6 7
// 0 1 
// 1 2 
// 1 4 
// 2 3 
// 5 4 
// 3 5 
// 4 5 

// 6 10
// 1 2 
// 1 2
// 2 3
// 2 5 
// 3 4 
// 4 6 
// 4 6
// 5 6
// 5 6
// 4 5 