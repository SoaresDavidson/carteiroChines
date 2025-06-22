#include <bits/stdc++.h>
#include "grafo.hpp"
#include "solve.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;
using namespace std;

int main(){
Grafo g = gerar_grafo_aleatorio(789,12,4);
g.imprimir_grafo();
    // int n,m; 
    // cin >> n >> m;
    // for(int i=0;i <n;i++){
    //     Vertice* a = new Vertice();
    //     a -> id = i;
    //     g.adicionar_vertice(a);
    // }

    // for(int i = 0;i<m;i++){
    //     ll inicio,destino,peso; 
    //     cin >> inicio >> destino >> peso;
    //     // inicio--,destino--;
    //     g.vertices[inicio]->adicionar_aresta(peso,g.vertices[destino]);
    //     g.vertices[destino]->adicionar_aresta(peso,g.vertices[inicio]);
    // }
    vector<int>v;
    for(auto ve : g.vertices){
        if(v.size() == 2) break;
        if(ve -> grau%2 != 0) v.push_back(ve->id);
        
    }
    Vertice* inicio = g.vertices[v[0]];
    Vertice* fim = g.vertices[v[1]];
    auto [distancia, caminho] = dijkstra(&g,inicio,fim);
    cout << "Distancia: "<<distancia << endl;
    cout <<fim->grau << endl;
    // cout << caminho.size() << endl;
    cout << "Pesos: ";
    for(auto aresta : caminho){
        cout << aresta.peso << " ";
    }
    duplicar_arestas(inicio,caminho);
    cout << endl;
    cout <<fim->grau << endl;
    for(auto aresta : inicio->arestas){
        cout << aresta.destino->id << " ";
    }
    
    return 0;
}
