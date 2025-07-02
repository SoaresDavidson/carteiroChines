#ifndef SOLVE_H
#define SOLVE_H
#include <bits/stdc++.h>
#include "grafo.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;

using namespace std;

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
Grafo* gerar_grafo_aleatorio(int qtdVertices, ll pesoMax, int grauMax, int quantidadeVerticesImpares) {
    while(true) {
        Grafo* g = new Grafo(qtdVertices);
        if (qtdVertices <= 1) return g;

        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<ll> dist_peso(1, pesoMax - 1); 
        uniform_int_distribution<int> dist_vertice(0, qtdVertices - 1); 
        
        int id = 0;
        for(int i = 0; i < qtdVertices; ++i) {
            Vertice* verticeOrigem = g->vertices[i];
            
            while ((verticeOrigem->grau < grauMax) || verticeOrigem->isEmpty()) {
                int indiceDestino = dist_vertice(rng);
                Vertice* verticeDestino = g->vertices[indiceDestino];

                if(verticeOrigem->grau >= grauMax or (verticeOrigem->isEmpty()==false and verticeDestino->grau >= grauMax)) break;
                if (verticeOrigem == verticeDestino) continue;

                ll peso = dist_peso(rng); 
                verticeOrigem->adicionar_aresta(peso, verticeDestino, id);
                verticeDestino->adicionar_aresta(peso, verticeOrigem, id++);
            }
        }

        // Verificar se o grafo atende aos requisitos de vértices ímpares
        int countImpares = 0;
        for(int i = 0; i < qtdVertices; ++i) {
            if(g->vertices[i]->grau % 2 != 0) {
                countImpares++;
            }
        }

        if(!g->Conexo() || countImpares != quantidadeVerticesImpares) {
            delete g;
            continue;
        } else {
            return g;
        }
    }
}

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
 * - O `second` (std::vector<int>) é o caminho como uma sequência de arestas
 * do vértice inicial ao destino. Retorna um vetor vazio se não houver caminho.
 */
pair<ll,vector<int>> dijkstra(Grafo* g, Vertice* inicio, Vertice* destino)
{
    ll INF = LLONG_MAX;
    priority_queue<pair<ll,Vertice*>,vector<pair<ll,Vertice*>>,greater<pair<ll,Vertice*>>>pq;//modifica a estrutura para ordenar do menor para o maior
    pq.push({0,inicio});
    map<Vertice*,ll>caminho;

    map<Vertice*,pair<Vertice*,int>>caminho_final;

    for(auto v : g->vertices)
    {
        caminho[v] = INF;
    }

    caminho[inicio] = 0;
    while(!pq.empty())
    {

        auto [distancia, vertice_atual] = pq.top();
        pq.pop();

        if(distancia < caminho[vertice_atual]) continue;//caso a distancia já encontrada para o vertice_atual já seja a menor continua

            for(auto aresta : vertice_atual->arestas)
            {
                if(caminho[aresta.destino] > caminho[vertice_atual] + aresta.peso)
                {
                    caminho[aresta.destino] = caminho[vertice_atual] + aresta.peso;
                    pq.push({caminho[aresta.destino],aresta.destino});
                    caminho_final[aresta.destino] = {vertice_atual,aresta.id};
                }

            }

        if(vertice_atual==destino) break; //quando o vertice destino for rotulado encerra o algoritmo e retorna
    }

    if(caminho[destino]==INF) return{-1,vector<int>{}}; //não existe caminho entre esses vertices
    vector<int>path;
    Vertice* verticeAtual = destino;
    
    while(verticeAtual!=nullptr and verticeAtual!=inicio)
    {

        int aresta_atual = caminho_final[verticeAtual].s;
        verticeAtual = caminho_final[verticeAtual].f;
        path.push_back(aresta_atual);

    }

    reverse(ALL(path));//inverte o vector para condizer com o caminho real percorrido do vertice inicio ao vertice fim
    return {caminho[destino],path};//retorna a distancia minima entre dois vertices, junto com o caminho 
}



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
void duplicar_arestas(Vertice* inicio,  vector<int> ids_arestas) 
{
    if (!inicio || ids_arestas.empty()) return;

    Vertice* atual = inicio;
    int novo_id = 100; 

    for (size_t i = 0; i < ids_arestas.size(); ++i) {
        
        Aresta aresta_original = atual->findArestaById(ids_arestas[i]);
        atual->adicionar_aresta(aresta_original.peso, aresta_original.destino, novo_id);
        aresta_original.destino->adicionar_aresta(aresta_original.peso, atual, novo_id);
        
        novo_id++;
        atual = aresta_original.destino;
    }
}


/*
 * @brief Encontra vértices com grau ímpar em um grafo.
 *
 * Esta função percorre todos os vértices de um grafo fornecido e identifica aqueles
 * cujo grau (número de conexões) é um número ímpar. Ela retorna uma coleção
 * desses vértices.
 *
 * @param grafo Ponteiro para o objeto Grafo a ser analisado. Espera-se que o Grafo
 * contenha uma coleção de ponteiros para Vertice, e que cada Vertice
 * possua um membro 'grau' que represente seu número de arestas.
 * @return Um 'std::vector' de ponteiros para Vertice, contendo apenas os vértices
 * que possuem grau ímpar no grafo.
 */
vector<Vertice*> impares(Grafo* grafo)
{
    vector<Vertice*> retorno;
    ll i = (*grafo).vertices.size();
    for (auto v: grafo->vertices)
    {
        if (v->grau % 2)
        {
            retorno.push_back(v);
        }
    }
    return retorno;
}



/*
 * @brief Gera todos os emparelhamentos possíveis a partir de um conjunto de vértices.
 *
 * Esta função recursiva explora todas as combinações de emparelhamento entre os vértices restantes.
 * Um emparelhamento é uma coleção de pares de vértices, onde cada vértice aparece em no máximo um par.
 * A função constrói e armazena todos esses emparelhamentos completos no vetor 'resultado'.
 *
 * @param restantes Ponteiro para um vetor de Vertice* contendo os vértices ainda não emparelhados
 * na chamada recursiva atual.
 * @param resultado Ponteiro para um vetor de vetores de pares de Vertice*. Este parâmetro acumula
 * todos os emparelhamentos completos encontrados.
 * @param emparelhamentoAtual Ponteiro para um vetor de pares de Vertice*. Representa o emparelhamento
 * que está sendo construído na iteração atual da recursão. É inicializado
 * como um novo vetor vazio por padrão na primeira chamada.
 */
void emparelhamentos(vector<Vertice*>* restantes, vector<vector<pair<Vertice*, Vertice*>>>* resultado, vector<pair<Vertice*, Vertice*>>* emparelhamentoAtual = new vector<pair<Vertice*, Vertice*>>())
{
    //Recebe um vetor de vetores de pares de vértices e o preenche com cada emparelhamento possível
    if ((*restantes).empty())
    {
        (*resultado).push_back(*emparelhamentoAtual);
        return;
    }


    Vertice* u = (*restantes)[0];

    for (auto v: *restantes)
    {
  
        if (v == u) continue;
        vector<pair<Vertice*, Vertice*>> novo_Emparelhamento = *emparelhamentoAtual;
        novo_Emparelhamento.push_back(make_pair(u, v));
        vector<Vertice*> novosRestantes = *restantes;
 
        novosRestantes.erase(remove_if(novosRestantes.begin(), novosRestantes.end(), [&](Vertice* x)
    {
        return x == u || x == v;
    }), novosRestantes.end());

    emparelhamentos(&novosRestantes, resultado, &novo_Emparelhamento);
    }
}



/*
@brief Gera uma fração dos emparelhamentos possíveis a partir de um conjunto de vértices.*
Esta função recursiva explora algumas das combinações de emparelhamento entre os vértices restantes, evitando enumeração completa
e tornando o cálculo da emparelhamento máximo de custo mínimo mais rápido.
O iterador das possibilidades é multiplicado por 2 em vez de seguir uma progressão linear, por isso existe a redução de respostas.
A função constrói e armazena todos esses emparelhamentos completos no vetor 'resultado'.

@param restantes Ponteiro para um vetor de Vertice* contendo os vértices ainda não emparelhados
na chamada recursiva atual.
@param resultado Ponteiro para um vetor de vetores de pares de Vertice*. Este parâmetro acumula
todos os emparelhamentos completos encontrados.
@param emparelhamentoAtual Ponteiro para um vetor de pares de Vertice*. Representa o emparelhamento
que está sendo construído na iteração atual da recursão. É inicializado
como um novo vetor vazio por padrão na primeira chamada.
*/
void heuristica_emparelhamento(vector<Vertice*>* restantes, vector<vector<pair<Vertice*, Vertice*>>>* resultado, vector<pair<Vertice*, Vertice*>>* emparelhamentoAtual = new vector<pair<Vertice*, Vertice*>>())
{
    //Recebe um vetor de vetores de pares de vértices e o preenche com cada emparelhamento possível
    if ((*restantes).empty())
    {
        (*resultado).push_back(*emparelhamentoAtual);
        return;
    }

    //cout << "Existem vertices restantes. Executando" << endl;

    Vertice* u = (*restantes)[0];
    int size = restantes->size();
/*
    if (size <= 4)
    {
        for (auto v: *restantes)
        {
            cout << "Entrou no loop de vertices" << endl;
            if (v == u) continue;
            vector<pair<Vertice*, Vertice*>> novo_Emparelhamento = *emparelhamentoAtual;
            novo_Emparelhamento.push_back(make_pair(u, v));
            vector<Vertice*> novosRestantes = *restantes;
            cout << "Fez novo emparelhamento" << endl;
            novosRestantes.erase(remove_if(novosRestantes.begin(), novosRestantes.end(), [&](Vertice* x)
        {
            return x == u || x == v;
        }), novosRestantes.end());
        cout << "Vai chamar a proxima recursao" << endl;
        emparelhamentos(&novosRestantes, resultado, &novo_Emparelhamento);
        }
    }
*/
  
        for (size_t i = 1; i < size; i*= 2)
        {
            auto v = (*restantes)[i];
            //cout << "Entrou no loop de vertices" << endl;
            if (v == u) continue;
            vector<pair<Vertice*, Vertice*>> novo_Emparelhamento = *emparelhamentoAtual;
            novo_Emparelhamento.push_back(make_pair(u, v));
            vector<Vertice*> novosRestantes = *restantes;
            //cout << "Fez novo emparelhamento" << endl;
            novosRestantes.erase(remove_if(novosRestantes.begin(), novosRestantes.end(), [&](Vertice* x)
        {
            return x == u || x == v;
        }), novosRestantes.end());
        //cout << "Vai chamar a proxima recursao" << endl;
        emparelhamentos(&novosRestantes, resultado, &novo_Emparelhamento);
        }
    
}


void dfs(Grafo *g, int v,Vertice* pai, vector<Vertice*> sequencia, vector<vector<Vertice*>> ciclos){
    Vertice* Vertice = g->vertices[v];
    for (auto& aresta : Vertice->arestas) 
    {
        if (pai == nullptr) pai = Vertice;
        int w = aresta.destino->id;

        if (Vertice->grau == 0) return;

        sequencia.push_back(Vertice);
        Vertice->remover_aresta(w);
        g->vertices[w]->remover_aresta(Vertice->id);
            

        if (pai->id == w)
        {
            sequencia.push_back(pai);
            ciclos.push_back(sequencia);
            sequencia.clear();
            // cout << "ciclo!" << endl;
            pai = nullptr;
        }

        // cout << v+1 << " vai para " << w+1 << endl;
        dfs(g, w,pai,sequencia,ciclos);
    }
}



/*
 * @brief Constrói um circuito Euleriano em um grafo utilizando uma abordagem similar ao algoritmo de Hierholzer.
 *
 * Esta função primeiro realiza uma Busca em Profundidade (DFS) no grafo para identificar ciclos.
 * Em seguida, ela "costura" esses ciclos encontrados para formar um único circuito Euleriano
 * que percorre todas as arestas do grafo exatamente uma vez, retornando ao ponto de partida.
 *
 * Pré-condição:
 * - O grafo 'g' deve ser conexo (excluindo vértices isolados).
 * - Todos os vértices do grafo 'g' devem ter grau par para que um circuito Euleriano exista.
 * - A função 'dfs' e a variável global/membro 'ciclos' devem estar corretamente implementadas
 * e acessíveis, onde 'ciclos' é preenchido com os ciclos encontrados pela DFS.
 *
 * @param g Ponteiro para o objeto Grafo no qual o circuito Euleriano será encontrado.
 * @return Um 'std::vector' de ponteiros para Vertice que representa a sequência ordenada
 * de vértices no circuito Euleriano. Retorna um vetor vazio se nenhum circuito for encontrado
 * ou se as pré-condições não forem satisfeitas.
 */
vector<Vertice*> hierholzer(Grafo* g)
{   
    vector<vector<Vertice*>> ciclos;
    vector<Vertice*> sequencia;
    Vertice* pai = nullptr;
    dfs(g, 0,pai,sequencia,ciclos);

    vector<Vertice*> euleriano;
    for (auto i : ciclos)
    {
        if (euleriano.empty())
        {
            euleriano.insert(euleriano.begin(), i.begin(), i.end());
            continue;
        }

        auto it = find(euleriano.begin(), euleriano.end(), i[0]);
        // if (it == euleriano.end()) continue;
        euleriano.insert(it+1, i.begin()+1, i.end());
    }

    return euleriano;
}

void Tarjan_DFS(Grafo* g, map<Vertice*, bool>& vis, Vertice* vi, Vertice* v_pai, int tempo, map<Vertice*, Vertice*> pai, map<Vertice*, int> descoberta, map<Vertice*, int> low)
{
    vis[vi] = true;
    descoberta[vi] = low[vi] = tempo++;

    for (Aresta v : vi->arestas) {
        if (v.destino == v_pai) continue;

        if(!vis[v.destino]) {
            pai[v.destino] = vi;
            Tarjan_DFS(g, vis, v.destino, vi, tempo, pai, descoberta, low);
            low[vi] = min(low[vi], low[v.destino]);
        }
        else {
            low[vi] = min(low[vi], descoberta[v.destino]);
        }
    }
}


bool serPonte(Vertice* v, Vertice* u, map<Vertice*, Vertice*> pai, map<Vertice*, int> descoberta, map<Vertice*, int> low)
{
    /*
    SE O LOW DE UM DOS VÉRTICES É MENOR QUE A DESCOBERTA DO OUTRO,
    ISSO QUER DIZER QUE ESTE VÉRTICE QUE TEM TEMPO MENOR PODE SER
    ACESSADO ANTES E AINDA ALCANÇAR O OUTRO, LOGO NÃO É UMA ARESTA DE CORTE
    OU SEJA, PARA SER ARESTA DE CORTE, O VÉRTICE U PRECISA TER O SEU MENOR TEMPO DE
    DESCOBERTA COMO MAIOR QUE O TEMPO DE DESCOBERTA DO VÉRTICE V, QUANDO
    V É PAI DE U (ARESTA V-U), ISSO PORQUE RESULTARIA EM DIZER QUE O VÉRTICE U
    NÃO PODERIA SER ALCANÇADO ANTES DO VÉRTICE V, IMPLICANDO EM UMA ARESTA
    DE CORTE
    */
    if (pai[u] == v)
    {
        return (low[u] > descoberta[v]);
    }
    else if (pai[v] == u)
    {
        return (low[v] > descoberta[u]);
    }
    return false;
}




/*
 * @brief Implementa uma variação do Algoritmo de Fleury para encontrar um Circuito/Caminho Euleriano.
 *
 * O Algoritmo de Fleury busca um caminho ou circuito que visita cada aresta de um grafo
 * exatamente uma vez. Esta função utiliza informações de pontes (arestas de corte)
 * obtidas por uma execução prévia do algoritmo de Tarjan (ou similar DFS) para garantir
 * que o caminho/circuito permaneça conexo enquanto é construído.
 *
 * Pré-condições:
 * - O grafo 'g' deve ser conectado (excluindo vértices isolados).
 * - Para um Circuito Euleriano, todos os vértices devem ter grau par.
 * - Para um Caminho Euleriano, exatamente dois vértices devem ter grau ímpar.
 * - As funções 'Tarjan_DFS' e 'serPonte' devem estar corretamente implementadas
 * e acessíveis, fornecendo os valores de 'pai', 'descoberta' e 'low' necessários
 * para a detecção de pontes.
 * - A função 'Vertice::isEmpty()' deve retornar true se o vértice não tiver mais arestas.
 *
 * @param g Ponteiro para o objeto Grafo a ser analisado.
 * @param vis Um mapa que rastreia os vértices visitados pela Tarjan_DFS.
 * @param vi O vértice inicial para a construção do circuito/caminho.
 * @param v_pai O vértice pai de 'vi' na árvore DFS inicial (geralmente nullptr na primeira chamada).
 * @param pai Um mapa que armazena o pai de cada vértice na árvore DFS.
 * @param tempo Um contador de tempo usado na Tarjan_DFS para stamps de descoberta.
 * @param descoberta Um mapa que armazena o tempo de descoberta de cada vértice.
 * @param low Um mapa que armazena o valor 'low' de cada vértice (menor tempo de descoberta alcançável).
 * @return Um 'std::vector' de ponteiros para Vertice que representa a sequência ordenada
 * dos vértices no circuito/caminho Euleriano encontrado.
 */
vector<Vertice*> fleury(Grafo* g,Vertice* vi)
{    map<Vertice*, Vertice*> pai;
     int tempo = 0;
     map<Vertice*, bool> vis;
     map<Vertice*, int> descoberta;
     map<Vertice*, int> low;
     Vertice* v_pai; 
    Tarjan_DFS(g, vis, vi, v_pai, tempo, pai, descoberta, low);

    stack<Vertice*> pilha;
    vector<Vertice*> ciclo;
    pilha.push(vi);

    while (!pilha.empty()) {
        Vertice* u = pilha.top();

        if (u->isEmpty()) {
            ciclo.push_back(u);
            pilha.pop();
        } else {
            // Encontra o primeiro vizinho
            Vertice* v = u->arestas[0].destino;

            // Verifica se a aresta é ponte
            bool isBridge = serPonte(u, v, pai, descoberta, low);

            // Se não é ponte, remove a aresta
            if (!isBridge || u->arestas.size() == 1)
            {
                // Remove aresta u-v
                u->remover_aresta(v->id);
                v->remover_aresta(u->id);

                pilha.push(v);
            }
            else
                {
                // Se é ponte e há outras opções, procura outra aresta
                bool found = false;
                for (size_t i = 1; i < u->arestas.size(); i++)
                    {
                    v = u->arestas[i].destino;
                    if (!serPonte(u, v, pai, descoberta, low))
                        {
                        // Remove aresta u-v
                        u->remover_aresta(v->id);
                        v->remover_aresta(u->id);

                        pilha.push(v);
                        found = true;
                        break;
                        }
                    }

                // Se todas são pontes, remove a primeira
                if (!found)
                    {
                    v = u->arestas[0].destino;
                    u->remover_aresta(v->id);
                    v->remover_aresta(u->id);

                    pilha.push(v);
                    }
                }
        }
    }

    // Imprime o ciclo euleriano
    // cout << "Ciclo Euleriano encontrado: ";
    // for (Vertice* v : ciclo) {
    //     cout << v->id + 1 << " "; // +1 para ajustar a numeração (começa em 1)
    // }
    // cout << endl;

    return ciclo;
}



void imprimir_caminho(vector<Vertice*> caminho){
    for(auto vertice : caminho){
        cout << vertice->id << "  ";
    }
    cout << endl;
}

/*
 * @brief Encontra e imprime um caminho euleriano em um grafo.
 * * Um caminho euleriano é um percurso que passa por cada aresta do grafo exatamente uma vez.
 * Esta função pode utilizar dois algoritmos diferentes para realizar essa tarefa,
 * selecionados através de um parâmetro booleano.
 * * @param grafo Um ponteiro para o objeto Grafo no qual o caminho será buscado.
 * @param hier  Um booleano que funciona como seletor de algoritmo:
 * - `true`: Utiliza o algoritmo de Hierholzer.
 * - `false`: Utiliza o algoritmo de Fleury.
 */
void caminho_euleriano(Grafo* grafo, bool hier) {
 
    vector<Vertice*> caminho;
    if (hier) {
        caminho = hierholzer(grafo);
        cout << "caminho euleriano feito usando hierholzer: " << endl;
    } else {
        caminho = fleury(grafo, grafo->vertices[0]);
        cout << "caminho euleriano feito usando fleury: " << endl;
    }

    imprimir_caminho(caminho);
}

/*
 * @brief Realiza o emparelhamento de um conjunto de vértices.
 * * Em teoria dos grafos, um emparelhamento (ou matching) é um conjunto de arestas
 * onde não há vértices em comum. Esta função decide entre uma abordagem heurística
 * (rápida, mas não necessariamente ótima) e uma abordagem exata para encontrar os pares.
 * * @param restantes Ponteiro para um vetor de vértices que ainda não foram emparelhados.
 * @param resultado Ponteiro para a estrutura de dados que armazenará os pares resultantes.
 * @param heuri     Um booleano que determina a abordagem:
 * - `true`: Utiliza uma função heurística para emparelhar.
 * - `false`: Utiliza um algoritmo exato (não heurístico).
 */
void decideEmparelhamento(vector<Vertice*>* restantes, vector<vector<pair<Vertice*, Vertice*>>>* resultado, bool heuri) {
    if (heuri) {
        heuristica_emparelhamento(restantes, resultado);
        cout << "emparelhamento feito com heuristica: " << endl;
    } else {
        emparelhamentos(restantes, resultado);
        cout << "emparelhamento feito sem heuristica: " << endl;
    }
}
#endif