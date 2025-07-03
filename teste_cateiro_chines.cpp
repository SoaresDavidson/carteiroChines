#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include "grafo.hpp"
#include "util.hpp"
#define ALL(x) x.begin(), x.end()
#define ll long long
#define f first;
#define s second;

using namespace std;

using namespace std::chrono;

int main(){
    int N = 30;
    int iteracoes = 10;
    int tempo_medio = 0;
    cout << "Quantas execucoes vai ter esse codigo" << endl;
    cout << N << " vertices" << "\n";

    Grafo* grafo = gerar_grafo_aleatorio(N, 12, 6,14);
    grafo->salvar_grafo("grafo_500.txt");

    while(iteracoes--)
    {
        ifstream arquivo("grafo_500.txt"); // abre o arquivo
        if (!arquivo.is_open())
        {
            cerr << "Erro ao abrir o arquivo!" << endl;
            return 1;
        }
        auto inicio = high_resolution_clock::now();

        int qtdVertices,qtdArestas; 
        //cout << "Informe a quantidade de vertices e a de Arestas" <<endl;
        arquivo >> qtdVertices >> qtdArestas;
        Grafo* grafo = new Grafo(qtdVertices);

        //cout << "Insira: (vertice inicial vertice final peso) o primeiro vertice comeca no 0" << endl;
        //recebendo as arestas e construindo o grafo
        for(int i = 0;i<qtdArestas;i++){
            ll comeco,destino,peso; 
            arquivo >> comeco >> destino >> peso;
            grafo->vertices[comeco]->adicionar_aresta(peso,grafo->vertices[destino],i);
        }

        aplicar_carteiro_chines(grafo,true,qtdVertices);

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
    cout << "Tempo de execucao medio por interacao foi: " << tempo_medio/10 << " ms" << endl;
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