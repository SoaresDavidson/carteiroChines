#include <iostream>
#include <bits/stdc++.h>
#include "grafo.hpp"

using namespace std;

vector<vector<Vertice*>> ciclos;
vector<Vertice*> sequencia;
Vertice* pai = nullptr;

void dfs(Grafo *g, int v){
    Vertice* Vertice = g->vertices[v];
    for (auto& aresta : Vertice->arestas) {
        if (pai == nullptr) pai = Vertice;
        int w = aresta.destino->id;

        if (Vertice->grau == 0) return;

        sequencia.push_back(Vertice);
        Vertice->remover_aresta(w);
        g->vertices[w]->remover_aresta(Vertice->id);
            

        if (pai->id == w){
            sequencia.push_back(pai);
            ciclos.push_back(sequencia);
            sequencia.clear();
            // cout << "ciclo!" << endl;
            pai = nullptr;
        }

        // cout << v+1 << " vai para " << w+1 << endl;
        dfs(g, w);
    }
}

vector<Vertice*> hierholzer(Grafo* g){
    dfs(g, 0);

    vector<Vertice*> euleriano;
    for (auto i : ciclos){
        if (euleriano.empty()){
            euleriano.insert(euleriano.begin(), i.begin(), i.end());
            continue;
        }

        auto it = find(euleriano.begin(), euleriano.end(), i[0]);
        // if (it == euleriano.end()) continue;
        euleriano.insert(it+1, i.begin()+1, i.end());
    }

    return euleriano;
}

int main(){
    int v, a; cin >> v >> a;
    Grafo grafo = Grafo();

    for (int i = 0; i < v; i++){
        Vertice* novo = new Vertice();
        novo->id = i;
        grafo.adicionar_vertice(novo);
    }

    for(int i = 0;i < a; i++){
        int v1, v2; cin >> v1 >> v2; v1--;v2--;
        grafo.vertices[v1]->adicionar_aresta(1, grafo.vertices[v2]);
        grafo.vertices[v2]->adicionar_aresta(1, grafo.vertices[v1]);
    }
    pai = 0;
    dfs(&grafo, 0);

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