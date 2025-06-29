#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include "grafo.hpp"
#include "solve.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;

using namespace std;

using namespace std::chrono;

int main(){
    int N = 10;
    int iteracoes = 10;
    int tempo_medio = 0;
    cout << "Quantas execucoes vai ter esse codigo" << endl;

    
    Grafo* grafo = gerar_grafo_aleatorio(10,12,2);
    grafo->salvar_grafo("grafo.txt");
    
    while(N--)
    {
        ifstream arquivo("grafo.txt"); // abre o arquivo
        if (!arquivo.is_open()) 
        {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }
        auto inicio = high_resolution_clock::now();

        int qtdVertices,qtdArestas; 
        cout << "Informe a quantidade de vertices e a de Arestas" <<endl;
        arquivo >> qtdVertices >> qtdArestas;
        Grafo* grafo = new Grafo(qtdVertices);

        cout << "Insira: (vertice inicial vertice final peso) o primeiro vertice comeca no 0" << endl;
        //recebendo as arestas e construindo o grafo
        for(int i = 0;i<qtdArestas;i++){
            ll comeco,destino,peso; 
            arquivo >> comeco >> destino >> peso;
            grafo->vertices[comeco]->adicionar_aresta(peso,grafo->vertices[destino],i);
        }

        pair<ll,vector<int>> dp[qtdVertices][qtdVertices];

        for(int i = 0;i < qtdVertices; i++)
        {
            for(int j = 0; j < qtdVertices;j++) dp[i][j] = {-1,vector<int>{}};
        }

        if(!grafo->Conexo())
        {
            cout << "Nao eh Conexo essa porra" << endl;
            delete grafo;
            continue;
        }

        cout << "Grafo original"<< endl;
        grafo->imprimir_grafo(); 

        vector<Vertice*> vertices_impares = impares(grafo);
        cout << "Quantidade de vertices impares: " << vertices_impares.size() << endl;

        if(vertices_impares.size()%2!=0) 
        {
            cout << "Nao da pra aplicar o carteiro chines" << endl;
            return 0;
        }

        vector<vector<pair<Vertice*, Vertice*>>> emparelhamentos_gerados;
        ll peso_inicio = grafo->calcular_peso();
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
                    auto[peso,arestas] = dijkstra(grafo,vertice_inicial,vertice_final);

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
        cout << "Peso calculado " << grafo->calcular_peso() << endl;
        cout << "Grafo final"<< endl;

        // grafo.salvar_grafo("grafos.txt");

        grafo->imprimir_grafo();
        
        auto fim = high_resolution_clock::now();
        auto duracao = duration_cast<milliseconds>(fim - inicio);
        caminho_euleriano(grafo,true);
        cout << "Tempo de execucao: " << duracao.count() << " ms" << endl;
        tempo_medio+=duracao.count();
        delete grafo;
        arquivo.close();
        
    }
    cout << "Tempo de execucao medio foi: " << tempo_medio/iteracoes << endl;
    return 0;
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