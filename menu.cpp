#include <bits/stdc++.h>
#include <chrono>
#include "grafo.hpp"
#include "util.hpp"

using namespace std;

using namespace std::chrono;

int main(){
    while(true){
        int vertices, pesoMax;
        cout << "Insira a quantidade de vertices, peso maximo para gerar o grafo aleatorio: ";
        cin >> vertices >> pesoMax;
        Grafo* grafo = gerar_grafo_aleatorio(vertices, pesoMax,2);
        cout << "Grafo gerado: ";
        grafo->imprimir_grafo();
    
        int opcao; 
        bool heuristica;
        cout << "Voce deseja aplicar Heuristica no emparelhamento?\n1 - sim\n2 - nao" << endl;     
        cin >> opcao;

        heuristica = opcao < 2 ? true : false;

        aplicar_carteiro_chines(grafo,heuristica,vertices);

        cout << "Qual Algoritmo voce deseja usar:\n0 - Hierholzer\n1 - Fluery" << endl;
        cin >> opcao;
        bool algoritmo = opcao == 1 ? false : true;
        caminho_euleriano(grafo, algoritmo);

        cout << "Deseja encerrar o programa?\n0 - sim\n1 - nao"<<endl;
        cin >> opcao;

        if(!opcao) break;
    }
}
