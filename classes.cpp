#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Vertice{
    public:
    vector<Aresta> arestas();
    int grau = 0;
};
class Aresta{
    public:
    int peso;
    Vertice destino;
};

class Grafo{
    public:
    vector<Vertice> vertices();
    int ordem = 0;
};
int main()
{
    
}
