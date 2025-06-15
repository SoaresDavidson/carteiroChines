#ifndef GRAFO_H
#define GRAFO_H
#define ll long long 
#include <vector>
using namespace std;
class Vertice;

class Aresta {
public:
    ll peso;
    Vertice* destino; 
    Aresta(ll p, Vertice* d) : peso(p), destino(d) {}
};

class Vertice {
public:
    int id;
    vector<Aresta> arestas;
    int grau = 0;
    Vertice() {}
    void aumentar_grau(){
        grau++;
    }
    void adicionar_aresta(ll peso, Vertice* destino){
        Aresta aresta(peso, destino);
        arestas.push_back(aresta);
        aumentar_grau();
    }
};

class Grafo {
public:
    vector<Vertice*> vertices;
    int ordem = 0;
    Grafo() {}
    
    ~Grafo() {
        for (Vertice* v : vertices) {
            delete v;
        }
        vertices.clear();
    }
    void adicionar_vertice(Vertice* v){
        vertices.push_back(v);
        ordem++;
    }
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