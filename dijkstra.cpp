#include <bits/stdc++.h>
#include "grafo.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;
const ll INF = LLONG_MAX;
using namespace std;
//cabeçalho para as funções 
/*
 * @brief Calcula a menor distância e o caminho (sequência de arestas) entre dois vértices em um grafo.
 *
 * Este método implementa o algoritmo de Dijkstra para encontrar o caminho mais curto
 * de um vértice inicial até um vértice destino em um grafo com pesos não-negativos.
 * Se o vértice destino for inalcançável a partir do vértice inicial, a distância
 * retornada será INF (infinito) e o vetor de arestas estará vazio.
 *
 * @param g Ponteiro para o objeto Grafo onde a busca será realizada.
 * @param inicio Ponteiro para o vértice inicial da busca.
 * @param destino Ponteiro para o vértice destino da busca.
 * @return Um `std::pair` onde:
 * - O `first` (long long) é a distância mínima do vértice inicial ao destino.
 * Retorna -1 se não houver caminho (destino inalcançável).
 * - O `second` (std::vector<Aresta>) é o caminho como uma sequência de arestas
 * do vértice inicial ao destino. Retorna um vetor vazio se não houver caminho.
 */
pair<ll,vector<Aresta>> dijkstra(Grafo* g, Vertice* inicio, Vertice* destino);

/*
 * @brief Gera um grafo aleatório com um número especificado de vértices e características de arestas.
 *
 * Esta função cria um grafo onde os vértices são numerados de 0 a `qtdVertices - 1`.
 * As arestas são adicionadas aleatoriamente entre os vértices, com pesos aleatórios
 * dentro de um limite e tentando atingir um grau máximo aproximado para cada vértice.
 * O grafo gerado é não direcionado, ou seja, se uma aresta (u, v) existe, (v, u) também existe.
 * A geração de números aleatórios é baseada em `std::mt19937` para maior robustez.
 *
 * @param qtdVertices O número total de vértices a serem criados no grafo.
 * @param pesoMax O valor máximo (exclusivo) para o peso das arestas (pesos serão de 1 a pesoMax-1).
 * @param grau O grau máximo aproximado que cada vértice tentará ter. Devido à aleatoriedade e
 * à prevenção de laços e arestas paralelas, o grau real pode variar.
 * @return Um objeto Grafo que representa o grafo aleatoriamente gerado.
 */
Grafo gerar_grafo_aleatorio(int qtdVertices, ll pesoMax, int grau);

/*
 * @brief Adiciona uma cópia de uma sequência de arestas a partir de um vértice.
 *
 * Esta função percorre o vetor de arestas fornecido e adiciona cada uma dessas arestas
 * ao vértice `inicio`. Isso pode ser útil para replicar um subcaminho ou um conjunto
 * específico de conexões em um grafo existente. Note que o grau do vértice 'inicio'
 * será aumentado para cada aresta adicionada.
 *
 * @param inicio Ponteiro para o vértice de onde as arestas serão adicionadas.
 * @param arestas Um `std::vector` de objetos Aresta a serem adicionados ao vértice `inicio`.
 */
void duplicar_arestas(Vertice* inicio, vector<Aresta> arestas);

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

pair<ll,vector<Aresta>> dijkstra(Grafo* g, Vertice* inicio, Vertice* destino){
    priority_queue<pair<ll,Vertice*>,vector<pair<ll,Vertice*>>,greater<pair<ll,Vertice*>>>pq;//modifica a estrutura para ordenar do menor para o maior
    pq.push({0,inicio});
    map<Vertice*,ll>caminho;
    map<Vertice*,pair<Vertice*,Aresta>>caminho_final;
    for(auto v : g->vertices){
        caminho[v] = INF;
    }
    caminho[inicio] = 0;
    while(!pq.empty()){
        auto [distancia, vertice_atual] = pq.top();
        pq.pop();
        if(distancia < caminho[vertice_atual]) continue;//caso a distancia já encontrada para o vertice_atual já seja a menor continua
            for(auto aresta : vertice_atual->arestas){
                if(caminho[aresta.destino] > caminho[vertice_atual] + aresta.peso){
                    caminho[aresta.destino] = caminho[vertice_atual] + aresta.peso;
                    pq.push({caminho[aresta.destino],aresta.destino});
                    caminho_final[aresta.destino] = {vertice_atual,aresta};
                }
            }
        if(vertice_atual==destino) break; //quando o vertice destino for rotulado encerra o algoritmo e retorna
    }
    if(caminho[destino]==INF) return{-1,vector<Aresta>{}}; //não existe caminho entre esses vertices
    vector<Aresta>path;
    Vertice* verticeAtual = destino;
    
    while(verticeAtual!=nullptr and verticeAtual!=inicio){
        Aresta aresta_atual = caminho_final[verticeAtual].s;
        verticeAtual = caminho_final[verticeAtual].f;
        path.push_back(aresta_atual);
    }

    reverse(ALL(path));//inverte o vector para condizer com o caminho real percorrido do vertice inicio ao vertice fim
    return {caminho[destino],path};//retorna a distancia minima entre dois vertices, junto com o caminho 
}

void duplicar_arestas(Vertice* inicio, vector<Aresta> arestas){
    inicio->adicionar_aresta(arestas[0].peso,arestas[0].destino);
    arestas[0].destino->adicionar_aresta(arestas[0].peso,inicio);
        for(int i = 0;i < arestas.size()-1;i++){
        arestas[i].destino -> adicionar_aresta(arestas[i+1].peso,arestas[i+1].destino);
        arestas[i+1].destino -> adicionar_aresta(arestas[i+1].peso,arestas[i].destino);
    }
}