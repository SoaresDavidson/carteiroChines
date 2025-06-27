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
    // Grafo grafo(qtdVertices);

    // // //adicionando os N vertices no grafo
    // // for(int i=0;i <qtdVertices;i++){
    // //     Vertice* a = new Vertice();
    // //     a -> id = i;
    // //     grafo.adicionar_vertice(a);
    // // }

    // cout << "Insira: (vertice inicial vertice final peso) o primeiro vertice comeca no 0" << endl;
    // //recebendo as arestas e construindo o grafo
    // for(int i = 0;i<qtdArestas;i++){
    //     ll inicio,destino,peso; 
    //     cin >> inicio >> destino >> peso;
    //     grafo.vertices[inicio]->adicionar_aresta(peso,grafo.vertices[destino],i);
    // }
    int qtdVertices = 40;
    // // map<pair<int,int>,pair<ll,vector<Aresta>>>dp;
    pair<ll,vector<int>> dp[qtdVertices][qtdVertices];
    for(int i = 0;i < qtdVertices; i++)
    {
        for(int j = 0; j < qtdVertices;j++) dp[i][j] = {-1,vector<int>{}};
    }
    Grafo grafo = gerar_grafo_aleatorio(qtdVertices,12,6);
    if(!grafo.Conexo())
    {
        cout << "Nao é Conexo essa porra" << endl;
        return 0;
    }
    cout << "Grafo original"<< endl;
    grafo.imprimir_grafo(); 

    vector<Vertice*> vertices_impares = impares(&grafo);
    cout << "Quantidade de vertices impares: " << vertices_impares.size() << endl;

    if(vertices_impares.size()%2!=0) 
    {
        cout << "Nao da pra aplicar o carteiro chines" << endl;
        return 0;
    }
    // grafo.salvar_grafo("grafos.txt");
    vector<vector<pair<Vertice*, Vertice*>>> emparelhamentos_gerados;
    ll peso_inicio = grafo.calcular_peso();
    emparelhamentos(&vertices_impares,&emparelhamentos_gerados);
    cout << "Peso do Grafo inicial: " << peso_inicio << endl;
    ll peso_total = LLONG_MAX;
    vector<pair<Vertice*,vector<int>>>dup;

    for(auto emparelhamento : emparelhamentos_gerados)
    {
        ll soma_peso = 0;
        vector<pair<Vertice*,vector<int>>>duplicar;

       for(auto [vertice_inicial,vertice_final] : emparelhamento)
       {
            if(dp[vertice_inicial->id][vertice_final->id].first == -1)
            {
                auto[peso,arestas] = dijkstra(&grafo,vertice_inicial,vertice_final);

                dp[vertice_inicial->id][vertice_final->id] = {peso,arestas};

                dp[vertice_final->id][vertice_inicial->id] = {peso,arestas};

                soma_peso+=peso;

                duplicar.push_back({vertice_inicial,arestas});

            } else {

                ll peso = dp[vertice_inicial->id][vertice_final->id].first;
                vector<int>arestas =dp[vertice_inicial->id][vertice_final->id].second;
                soma_peso+=peso;
                duplicar.push_back({vertice_inicial,arestas});

            }
            

            if(soma_peso > peso_total) break;
       } 

       if(soma_peso < peso_total)
       {
            peso_total = soma_peso;
            dup = duplicar;
       }
    }

    for(auto  [vertice_inicial,aresta] : dup)
    {
        duplicar_arestas(vertice_inicial, aresta);
    }

    cout << "Peso arestas " << peso_total << "+" << peso_inicio << endl;
    cout << "Peso calculado " << grafo.calcular_peso() << endl;
    cout << "Grafo final"<< endl;

    // grafo.salvar_grafo("grafos.txt");

    grafo.imprimir_grafo();
    // vector<Vertice*> caminho_hier = hierholzer(&grafo);
    // cout << "caminho euleriano feito usando hierholzer: " << endl;
    // imprimir_caminho(caminho_hier);
    vector<Vertice*> caminho_fleury = fleury(&grafo,grafo[0]);
    cout << "caminho euleriano feito usando fleury: " << endl;
    imprimir_caminho(caminho_fleury);
    
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