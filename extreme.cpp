#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include "grafo.hpp"
#define ll long long

using namespace std;

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

void emparelhamentos(vector<Vertice*>* restantes, vector<vector<pair<Vertice*, Vertice*>>>* resultado, vector<pair<Vertice*, Vertice*>>* emparelhamentoAtual = new vector<pair<Vertice*, Vertice*>>())
{
    //Recebe um vetor de vetores de pares de vértices e o preenche com cada emparelhamento possível
    if ((*restantes).empty())
    {
        (*resultado).push_back(*emparelhamentoAtual);
        return;
    }

    cout << "Existem vertices restantes. Executando" << endl;

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
int main()
{
    cout << "Fodase" << endl;
    Grafo grafo;
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        Vertice* novo = new Vertice();
        grafo.adicionar_vertice(novo);
    }
    cout << "Adicionou os vertices" << endl;

    vector<vector<pair<Vertice*, Vertice*>>> emparelhados;
    emparelhamentos(&grafo.vertices, &emparelhados);
    ll o = emparelhados.size();

    if (o == 0) cout << "Nao tem e nada no vetor" << endl;
    for (ll i = 0; i < o; i++)
    {
        ll m = emparelhados[i].size();
        cout << "Emparelhamento " << i + 1 << ":" << endl;
        for (ll j = 0; j < m; j++)
        {
            cout << "(" << emparelhados[i][j].first << ", " << emparelhados[i][j].second << ") ";
        }
        cout << endl;
    }
}