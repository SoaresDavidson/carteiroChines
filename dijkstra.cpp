#include <bits/stdc++.h>
#include "grafo.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;
const ll INF = LLONG_MAX;
using namespace std;

pair<ll,vector<Vertice*>> dijkstra(Grafo* g, Vertice* inicio, Vertice* destino);
Grafo gerar_grafo_aleatorio(int qtdVertices, ll pesoMax, int grau);
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
        if(ve -> grau%2!=0) v.push_back(ve->id);
        
    }
    Vertice* inicio = g.vertices[v[0]];
    Vertice* fim = g.vertices[v[1]];
    auto [distancia, caminho] = dijkstra(&g,inicio,fim);
    cout << distancia << endl;
    for(auto v : caminho){
        cout << v->id << " ";
    }
    return 0;
}


Grafo gerar_grafo_aleatorio(int qtdVertices, ll pesoMax, int grauMax){
    Grafo g;

    for(int i = 0; i < qtdVertices; i++){
        Vertice* v = new Vertice();
        v-> id = i;
        g.adicionar_vertice(v);
    }

    if (qtdVertices <= 1) {
        return g;
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
   
    uniform_int_distribution<ll> dist_peso(1, pesoMax - 1); 
    uniform_int_distribution<int> dist_vertice(0, qtdVertices - 1); 

    for(int i = 0; i < qtdVertices; ++i){
        Vertice* verticeOrigem = g.vertices[i];
        int arestasAdicionadasParaEsteVertice = 0;
        while (arestasAdicionadasParaEsteVertice < grauMax && arestasAdicionadasParaEsteVertice < qtdVertices - 1) {
            int indiceDestino = dist_vertice(rng);
            Vertice* verticeDestino = g.vertices[indiceDestino];

            if (verticeOrigem == verticeDestino) {
                continue;
            }
            ll peso = dist_peso(rng); 
            verticeOrigem->adicionar_aresta(peso, verticeDestino);
            verticeDestino->adicionar_aresta(peso, verticeOrigem);

            arestasAdicionadasParaEsteVertice++;
        }
    }

    return g;
}

pair<ll,vector<Vertice*>> dijkstra(Grafo* g, Vertice* inicio, Vertice* destino){
    priority_queue<pair<ll,Vertice*>,vector<pair<ll,Vertice*>>,greater<pair<ll,Vertice*>>>pq;
    pq.push({0,inicio});
    map<Vertice*,ll>caminho;
    map<Vertice*,Vertice*>caminho_final;
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
                    caminho_final[aresta.destino] = vertice_atual;
                }
            }
        if(vertice_atual==destino) break; //quando o vertice destino for rotulado encerra o algoritmo e retorna
    }
    if(caminho[destino]==INF) return{-1,vector<Vertice*>{}}; //não existe caminho entre esses vertices
    vector<Vertice*>path;
    Vertice* verticeAtual = destino;
    while(verticeAtual!=nullptr and verticeAtual!=inicio){
        path.push_back(verticeAtual);
        verticeAtual = caminho_final[verticeAtual];
    }
    if(verticeAtual == inicio){
        path.push_back((inicio));
    }else{
        return{-1,vector<Vertice*>{}};
    }
    reverse(ALL(path));
    return {caminho[destino],path};//retorna a distancia minima entre dois vertices, junto com o caminho 
}
