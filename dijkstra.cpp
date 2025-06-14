#include <bits/stdc++.h>
#include "grafo.hpp"
#define ll long long
#define f first;
#define s second;
const ll INF = LLONG_MAX;
using namespace std;
map<Vertice*,ll> dijkstra(Grafo* g, Vertice* inicio);
int main(){
Grafo g;
    int n,m; 
    cin >> n >> m;
    for(int i=0;i <n;i++){
        Vertice* a = new Vertice();
        g.adicionar_vertice(a);
    }

    for(int i = 0;i<m;i++){
        ll inicio,destino,peso; 
        cin >> inicio >> destino >> peso;
        inicio--,destino--;
        g.vertices[inicio]->adicionar_aresta(peso,g.vertices[destino]);
        g.vertices[destino]->adicionar_aresta(peso,g.vertices[inicio]);
    }
    auto distancia = dijkstra(&g,g.vertices[0]);
    for (auto v : g.vertices){
        cout << distancia[v] << " ";
    }
    return 0;
}

map<Vertice*,ll> dijkstra(Grafo* g, Vertice* inicio){
    priority_queue<pair<ll,Vertice*>,vector<pair<ll,Vertice*>>,greater<pair<ll,Vertice*>>>pq;
    pq.push({0,inicio});
    map<Vertice*,ll>caminho;
    for(auto v : g->vertices){
        caminho[v] = INF;
    }
    caminho[inicio] = 0;
    while(!pq.empty()){
        auto [distancia, vertice_atual] = pq.top();
        pq.pop();
        if(distancia < caminho[vertice_atual]) continue;
            for(auto aresta : vertice_atual->arestas){
                if(caminho[aresta.destino] > caminho[vertice_atual] + aresta.peso){
                    caminho[aresta.destino] = caminho[vertice_atual] + aresta.peso;
                    pq.push({caminho[aresta.destino],aresta.destino});
                }
            }
    }
    return caminho;
}
