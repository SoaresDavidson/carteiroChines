#include <iostream>
#include <bits/stdc++.h>

using namespace std;
//push_back = append, .begin = iterator que aponta pro primeiro
vector<int> pai;
vector<int> descoberta;
vector<int> low;
int tempo = 0;

/*
O ALGORITMO EXECUTA UMA DFS, DETERMINANDO OS MENORES TEMPOS
DE DESCOBERTA DE CADA VÉRTICE CONSIDERANDO OS NÓS ADJACENTES EXCETO O NÓ PAI
*/

void dfs(vector<vector<int>>& g, vector<bool>& vis, int vi, int v_pai) 
{
    vis[vi] = true;
    descoberta[vi] = low[vi] = tempo++;

    for (int v : g[vi]) {
        if (v == v_pai) continue;

        if(!vis[v]) {
            pai[v] = vi;
            dfs(g, vis, v, vi);
            low[vi] = min(low[vi], low[v]);
        }
        else {
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


void fleury(vector<vector<int>> g, int vi)
{
    stack<int> pilha;
    vector<int> ciclo;
    pilha.push(vi);

    while (!pilha.empty()) {
        int u = pilha.top();

        if (g[u].empty()) {
            ciclo.push_back(u);
            pilha.pop();
        } else {
            // Encontra o primeiro vizinho
            int v = g[u][0];

            // Verifica se a aresta é ponte
            bool isBridge = serPonte(u, v);

            // Se não é ponte, remove a aresta
            if (!isBridge || g[u].size() == 1) 
            {
                // Remove aresta u-v
                g[u].erase(find(g[u].begin(), g[u].end(), v));
                g[v].erase(find(g[v].begin(), g[v].end(), u));

                pilha.push(v);
            }
            else
                {
                // Se é ponte e há outras opções, procura outra aresta
                bool found = false;
                for (size_t i = 1; i < g[u].size(); i++) 
                    {
                    v = g[u][i];
                    if (!serPonte(u, v)) 
                        {
                        // Remove aresta u-v
                        g[u].erase(g[u].begin() + i);
                        g[v].erase(find(g[v].begin(), g[v].end(), u));

                        pilha.push(v);
                        found = true;
                        break;
                        }
                    }

                // Se todas são pontes, remove a primeira
                if (!found) 
                    {
                    v = g[u][0];
                    g[u].erase(g[u].begin());
                    g[v].erase(find(g[v].begin(), g[v].end(), u));

                    pilha.push(v);
                    }
                }
        }
    }

    // Imprime o ciclo euleriano
    cout << "Ciclo Euleriano encontrado: ";
    for (int v : ciclo) {
        cout << v + 1 << " "; // +1 para ajustar a numeração (começa em 1)
    }
    cout << endl;
}


int main(){
    int v, a; cin >> v >> a;
    vector<vector<int>> g(v);
    vector<bool> visitados(v, false);

    pai.resize(v, -1);
    descoberta.resize(v, -1);
    low.resize(v, -1);

    for(int i = 0; i < a; i++){
        int v1, v2; cin >> v1 >> v2; v1--;v2--;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

    dfs(g, visitados, 0, -1);
    fleury(g, 0);
}