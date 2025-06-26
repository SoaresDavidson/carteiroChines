#ifndef GRAFO_H
#define GRAFO_H
#define ll long long 
#include <algorithm>
#include <vector>
using namespace std;
class Vertice;



/*
 * @brief Representa uma conexão (aresta) entre dois vértices em um grafo.
 *
 * A classe Aresta armazena o peso associado à conexão e um ponteiro para
 * o vértice de destino da aresta.
 */
class Aresta {
public:
    ll peso;
    Vertice* destino; 
    Aresta(ll p, Vertice* d) : peso(p), destino(d) {}
    Aresta() : peso(0), destino(nullptr) {}
};


/*
 * @brief Representa um nó individual dentro de uma estrutura de grafo.
 *
 * A classe Vertice armazena um identificador único, gerencia as arestas que
 * partem dele para outros vértices e mantém o controle do seu grau.
 */
class Vertice {
public:
    int id;
    vector<Aresta> arestas;
    int grau = 0;
    Vertice() {}
    void aumentar_grau(){
        grau++;
    }

    /*
     * @brief Adiciona uma nova aresta a partir deste vértice.
     *
     * Cria e adiciona uma nova aresta que conecta este vértice a um 'destino'
     * específico com um 'peso' definido. Automaticamente incrementa o grau do vértice.
     *
     * @param peso O peso associado à aresta.
     * @param destino Um ponteiro para o vértice de destino da aresta.
     */
    void adicionar_aresta(ll peso, Vertice* destino)
    {
        Aresta aresta(peso, destino);
        arestas.push_back(aresta);
        aumentar_grau();
    }
    

    /*
     * @brief Busca por uma aresta específica com base no ID do vértice de destino.
     *
     * Percorre as arestas deste vértice para encontrar uma que tenha o vértice de destino
     * com o 'id' especificado.
     *
     * @param id O ID do vértice de destino da aresta a ser encontrada.
     * @return Um ponteiro para a Aresta encontrada, ou 'nullptr' se a aresta não existir.
     */
    Aresta* find_aresta(int id)
    {

        if (arestas.empty()) return nullptr;

        for (auto &i : arestas)
        {
            if (i.destino->id == id){
                return &i;
            }
        }
        return nullptr;
    }


    /*
     * @brief Verifica se esse vertice possui arestas.
     *
     * Retorna True caso exista pelo menos uma aresta ligada nesse vertice
     * caso contrário retorna False
     */
    bool isEmpty(){
        return arestas.empty();
    }

    /*
     * @brief Remove uma aresta específica deste vértice.
     *
     * Remove a aresta que tem como destino o vértice com o 'id' especificado.
     * O grau do vértice é decrementado. Lança um erro se a aresta não for encontrada.
     *
     * @param id O ID do vértice de destino da aresta a ser removida.
     * @throws std::runtime_error Se a aresta com o ID de destino especificado não for encontrada.
     */
    void remover_aresta(int id){

        for (size_t i = 0; i < arestas.size(); i++)
        {
            if (arestas[i].destino->id == id)
            {
                arestas.erase(arestas.begin() + i);
                grau--;
                return;
            }
        }

        throw runtime_error("você está tentando remover uma aresta que não existe");
    }
};



/*
 * @brief Representa uma estrutura de grafo, gerenciando seus vértices e operações básicas.
 *
 * Esta classe encapsula a coleção de vértices de um grafo e fornece funcionalidades
 * essenciais para sua manipulação e visualização. Ela é responsável por manter a ordem
 * do grafo (número de vértices) e garantir a liberação adequada da memória dos vértices
 * quando o grafo é destruído.
 */
class Grafo {
public:
    vector<Vertice*> vertices;
    int ordem = 0;
    Grafo() {}
    
    ~Grafo() {
        for (Vertice* v : vertices) 
        {
            delete v;
        }
        vertices.clear();
    }


     /*
     * @brief Adiciona um novo vértice ao grafo.
     *
     * Adiciona o ponteiro para o objeto Vertice fornecido à coleção de vértices
     * do grafo e incrementa a contagem da ordem do grafo.
     *
     * @param v Um ponteiro para o objeto Vertice a ser adicionado.
     */
    void adicionar_vertice(Vertice* v)
    {
        vertices.push_back(v);
        ordem++;
    }



    /*
     * @brief Imprime uma representação textual do grafo.
     *
     * Percorre cada vértice do grafo e suas arestas associadas, imprimindo seus IDs
     * e os IDs dos vértices de destino com seus respectivos pesos.
     */
    void imprimir_grafo(){
        for(auto vertice : vertices){
            cout << vertice->id << " ";
            for(auto aresta : vertice->arestas){
                cout << "{"<<aresta.destino->id << ",peso:" << aresta.peso << "}";
            }
            cout << endl;
        }
    }
};
#endif