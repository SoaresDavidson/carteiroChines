#ifndef GRAFO_H
#define GRAFO_H
#define ll long long 
#include <algorithm>
#include <vector>
#include <fstream>
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
    int id = 0;
    Aresta(ll p, Vertice* d, int _id) : peso(p), destino(d), id(_id) {}
    Aresta() : peso(0), destino(nullptr), id(-1){}
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
     * @brief Procura uma aresta específica pelo seu ID em uma coleção de arestas.
     *
     * Esta função realiza uma busca linear em uma coleção de arestas (um membro da classe,
     * chamado 'arestas') para encontrar aquela que corresponde a um ID fornecido.
     *
     * @param idProcurado O identificador inteiro da aresta que se deseja localizar.
     *
     * @return Retorna uma cópia do objeto Aresta se o ID for encontrado.
     * Se nenhuma aresta com o ID especificado for encontrada após percorrer
     * toda a coleção, retorna um objeto Aresta vazio (construído por padrão),
     * sinalizando que a busca falhou.
     */
    Aresta findArestaById(int idProcurado) {
    for (auto aresta : arestas) {
        if (aresta.id == idProcurado) {
            return aresta;
        }
    }

    return {};
}
    Aresta findArestaById(int idProcurado) {
        for (auto aresta : arestas) {           
            if (aresta.id == idProcurado) {      
                return aresta;                  
            }
        }
        return {};  
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
    void adicionar_aresta(ll peso, Vertice* destino, int id)
    {
        Aresta aresta(peso, destino,id);
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
     * @brief Verifica se o grafo é conexo utilizando uma Busca em Profundidade (DFS).
     *
     * Um grafo é considerado conexo se existe um caminho entre qualquer par de seus vértices.
     * A função implementa um algoritmo de travessia (DFS) a partir de um vértice inicial
     * para contar quantos vértices são alcançáveis. Se todos os vértices forem alcançados,
     * o grafo é conexo.
     *
     * @return bool - Retorna 'true' se o grafo for conexo e 'false' caso contrário.
     */
    bool Conexo() {
        if (ordem == 0) return true;

        std::unordered_set<int> visitados;

        std::stack<int> pilha;

        pilha.push(0);
        visitados.insert(0);

        while (!pilha.empty()) {

            int atual_id = pilha.top();
            pilha.pop();

            for (Aresta aresta : vertices[atual_id]->arestas) {
                Vertice* vizinho = aresta.destino;

                if (visitados.find(vizinho->id) == visitados.end()) {
                    visitados.insert(vizinho->id); 
                    pilha.push(vizinho->id);       
                }
            }
        }

        return (visitados.size() == static_cast<size_t>(ordem));
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
    int qtdArestas(){
        int qtd = 0;
         for(auto vertice : vertices){
            qtd+=vertice->arestas.size();
         }
         return qtd;
    }

    /*
    * @brief Salva a estrutura atual do grafo em um arquivo de texto.
    * Esta função permite persistir os dados do grafo (vértices e arestas)
    * para que possam ser recarregados ou analisados posteriormente.
    *
    * @param nome_arquivo Uma string constante representando o nome do arquivo
    * onde o grafo será salvo.
    */
    void salvar_grafo(const string& nome_arquivo)
    {
        ofstream arquivo(nome_arquivo);

        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo para escrita!" << endl;
            return;
        }

        arquivo << this->ordem << " " << qtdArestas() << endl;

        for (auto vertice : this->vertices) 
        {
            for (auto aresta : vertice->arestas) 
            {
                arquivo << vertice->id << " "
                        << aresta.destino->id << " "
                        << aresta.peso << endl;
            }
        }
        
        arquivo << endl;
        arquivo.close();
    }
    
    /*
    * @brief Calcula a soma total dos pesos de todas as arestas do grafo.
    * Projetado para grafos não-direcionados onde cada aresta é representada
    * duas vezes na lista de adjacências.
    *
    * @return ll (long long) - A soma total dos pesos de todas as arestas únicas.
    */
    ll calcular_peso()
    {
        ll sum = 0;
        for(auto vertice : this->vertices)
        {
            for(auto arestas : vertice->arestas)
            {
                sum += arestas.peso;
            }
        }
        return sum / 2;
    }

};
#endif