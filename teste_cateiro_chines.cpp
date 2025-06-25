#include <bits/stdc++.h>
#include "grafo.hpp"
#include "solve.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;

using namespace std;


int main(){
    // int qtdVertices,qtdArestas; 

    // cout << "Informe a quantidade de vertices e a de Arestas" <<endl;
    // cin >> qtdVertices >> qtdArestas;
    // Grafo grafo;

    // //adicionando os N vertices no grafo
    // for(int i=0;i <qtdVertices;i++){
    //     Vertice* a = new Vertice();
    //     a -> id = i;
    //     grafo.adicionar_vertice(a);
    // }

    // cout << "Insira: (vertice inicial vertice final peso) o primeiro vertice comeca no 0" << endl;
    // //recebendo as arestas e construindo o grafo
    // for(int i = 0;i<qtdArestas;i++){
    //     ll inicio,destino,peso; 
    //     cin >> inicio >> destino >> peso;
    //     grafo.vertices[inicio]->adicionar_aresta(peso,grafo.vertices[destino]);
    //     grafo.vertices[destino]->adicionar_aresta(peso,grafo.vertices[inicio]);
    // }
    Grafo grafo = gerar_grafo_aleatorio(120,20,3);
    cout << "Grafo original"<< endl;
    grafo.imprimir_grafo(); 

    vector<Vertice*> vertices_impares = impares(&grafo);

    if(vertices_impares.size()%2!=0) {
        cout << "Nao da pra aplicar o carteiro chines" << endl;
        return 0;
    }

    vector<vector<pair<Vertice*, Vertice*>>> emparelhamentos_gerados;

    emparelhamentos(&vertices_impares,&emparelhamentos_gerados);

    ll peso_total = LLONG_MAX;
    vector<pair<Vertice*,vector<Aresta>>>dup;

    for(auto emparelhamento : emparelhamentos_gerados){
        ll soma_peso = 0;
        vector<pair<Vertice*,vector<Aresta>>>duplicar;
       for(auto [vertice1,vertice2] : emparelhamento){

            auto [peso,arestas] = dijkstra(&grafo,vertice1,vertice2);
            soma_peso+=peso;
            duplicar.push_back({vertice1,arestas});

            if(soma_peso > peso_total) break;
       } 
       if(soma_peso < peso_total){
            peso_total = soma_peso;
            dup = duplicar;
       }
    }

    for(auto  [vertice_inicial,aresta] : dup){
        duplicar_arestas(vertice_inicial, aresta);
    }
    cout << "Grafo final"<< endl;
    grafo.imprimir_grafo();
    cout << "caminho euleriano: " << endl;
    vector<Vertice*> resultado = hierholzer(&grafo);
    for(auto i : resultado){
        cout << i->id+1 << " ";
    }
}
//grafo que eu mandei no grupo 
// 6 7
// 0 1 2
// 1 2 1
// 1 4 4
// 2 3 3
// 3 4 6
// 3 5 1
// 4 5 2