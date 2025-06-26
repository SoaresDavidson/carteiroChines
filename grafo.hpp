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
    Vertice(int _id) : id(_id) {};
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

    Vertice* operator[](int indice) {
        if (indice < 0 || indice >= vertices.size()) {
            throw std::out_of_range("Índice de vértice fora dos limites do grafo.");
        }
        return vertices[indice];
    }

     const Vertice* operator[](int indice) const {
        if (indice < 0 || indice >= vertices.size()) {
            throw std::out_of_range("Índice de vértice fora dos limites do grafo.");
        }
        return vertices[indice];
    }

    Grafo(int qtdVertices) {
        criar_grafo(qtdVertices);
    }
    
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

    void criar_grafo(int qtd){
        for(int i = 0; i < qtd; i++)
        {
            Vertice* a = new Vertice(i);
            a -> id = i;
            this->adicionar_vertice(a);
        }
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


    Grafo(const Grafo& outro) {
        std::map<Vertice*, Vertice*> mapa_vertices_orig_para_novo; // Mapeia Vertice* original -> Vertice* novo

        // 1. Criar e adicionar novos objetos Vertice à cópia
        for (Vertice* v_original : outro.vertices) {
            Vertice* v_novo = new Vertice(v_original->id); // Cria novo vértice com o mesmo ID
            this->adicionar_vertice(v_novo);               // Adiciona-o ao novo grafo
            mapa_vertices_orig_para_novo[v_original] = v_novo; // Armazena o mapeamento
        }

        // 2. Copiar as arestas e ajustar seus destinos para os novos vértices
        for (Vertice* v_original : outro.vertices) {
            Vertice* v_novo = mapa_vertices_orig_para_novo[v_original]; // Pega o novo vértice correspondente
            v_novo->grau = v_original->grau; // Copia o grau (se não for calculado ao adicionar arestas)
            
            for (const Aresta& aresta_original : v_original->arestas) {
                // Encontra o ponteiro para o novo vértice de destino correspondente
                Vertice* destino_novo = mapa_vertices_orig_para_novo[aresta_original.destino];
               
                v_novo->arestas.push_back(Aresta(aresta_original.peso, destino_novo));
                v_novo->grau++; // Se adicionar_aresta não atualiza o grau
            }
        }
        this->ordem = outro.ordem; // Copia a ordem total
    }

    // --- Operador de Atribuição de Cópia (Deep Copy) ---
    /*
     * @brief Operador de atribuição de cópia para realizar uma cópia profunda.
     *
     * Permite que um objeto Grafo seja atribuído a outro (ex: `grafo2 = grafo1;`).
     * Garante que o grafo de destino se torne uma cópia independente do grafo de origem,
     * gerenciando corretamente a memória do grafo de destino existente.
     *
     * @param outro O objeto Grafo a ser copiado.
     * @return Uma referência ao objeto Grafo atual (*this) após a atribuição.
     */
    Grafo& operator=(const Grafo& outro) {
        if (this == &outro) { // Previne auto-atribuição (ex: `g = g;`)
            return *this;
        }

        // 1. Libera a memória dos vértices existentes no grafo atual (para evitar vazamento)
        for (Vertice* v : vertices) {
            delete v;
        }
        vertices.clear();
        this->ordem = 0; // Reinicia a ordem

        // 2. Reutiliza a lógica do construtor de cópia para criar a cópia profunda
        std::map<Vertice*, Vertice*> mapa_vertices_orig_para_novo;

        for (Vertice* v_original : outro.vertices) {
            Vertice* v_novo = new Vertice(v_original->id);
            this->adicionar_vertice(v_novo);
            mapa_vertices_orig_para_novo[v_original] = v_novo;
        }

        for (Vertice* v_original : outro.vertices) {
            Vertice* v_novo = mapa_vertices_orig_para_novo[v_original];
            v_novo->grau = v_original->grau; // Copia o grau
            for (const Aresta& aresta_original : v_original->arestas) {
                Vertice* destino_novo = mapa_vertices_orig_para_novo[aresta_original.destino];
                // Recria a aresta no novo vértice
                v_novo->arestas.push_back(Aresta(aresta_original.peso, destino_novo));
                v_novo->grau++; // Se adicionar_aresta não é usado ou não atualiza grau
            }
        }
        this->ordem = outro.ordem;
        return *this; // Retorna referência para permitir encadeamento (a = b = c;)
    }
};
#endif