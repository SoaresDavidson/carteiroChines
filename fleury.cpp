#include <iostream>
#include <bits/stdc++.h>
/*
    v = 6; a = 10;
    grafo[0].push_back(1); grafo[1].push_back(0);

    grafo[0].push_back(2); grafo[2].push_back(0);

    grafo[1].push_back(2); grafo[2].push_back(1);

    grafo[1].push_back(3); grafo[3].push_back(1);

    grafo[1].push_back(4); grafo[4].push_back(1);

    grafo[2].push_back(3); grafo[3].push_back(2);

    grafo[2].push_back(4); grafo[4].push_back(2);

    grafo[3].push_back(4); grafo[4].push_back(3);

    grafo[3].push_back(5); grafo[5].push_back(3);

    grafo[4].push_back(5); grafo[5].push_back(4);

*/



using namespace std;
//push_back = append, .begin = iterator que aponta pro primeiro
vector<int> pai;
vector<int> descoberta;
vector<int> low;
int tempo = 0;

void dfs(vector<vector<int>> g, vector<bool> vis, int vi, int v_pai) 
{
    vis[vi] = true;
    descoberta[vi] = low[vi] = tempo++;
    for (int v : g[vi])
    {
        if (v == v_pai) continue;
/*
O ALGORITMO EXECUTA UMA DFS, DETERMINANDO OS MENORES TEMPOS
DE DESCOBERTA DE CADA VÉRTICE CONSIDERANDO OS NÓS ADJACENTES EXCETO O NÓ PAI
*/
        if(!vis[v])
            {
                pai[v] = vi;
                dfs(g, vis, v, vi);
                low[vi] = min(low[vi], low[v]);
            }
        else
            {
                low[vi] = min(low[vi], descoberta[v]);
            }
    }
}

bool serPonte(int v, int u)
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


void fleury(vector<vector<int>> g, vector<bool> vis, int vi, int v_pai){

}


int main(){
    int v, a; cin >> v >> a;
    vector<vector<int>> grafo(v);
    vector<bool> visitados(v, false);

    for(int i = 0; i < a; i++){
        int v1, v2; cin >> v1 >> v2; v1--;v2--;
        grafo[v1].push_back(v2);
        grafo[v2].push_back(v1);
    }

}