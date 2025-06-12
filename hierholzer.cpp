#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> ciclos;
vector<int> sequencia;

void dfs(vector<vector<int>> g, vector<vector<bool>> &vis ,int v){
    

    for (auto w : g[v]) if (!vis[v][w]){
        sequencia.push_back(v);
        vis[v][w] = true;
        vis[w][v] = true;
            
        auto it = find(sequencia.begin(), sequencia.end(), w);

        if (it != sequencia.end()){
            sequencia.push_back(w);
            ciclos.push_back(sequencia);
  
            for (auto i : sequencia){
                cout << i+1 << endl;
            }
            sequencia = vector<int>();
        }

        cout << v+1 << " vai para " << w+1 << endl;
        dfs(g, vis, w);
    }
}

int main(){
    int v, a; cin >> v >> a;
    vector<vector<bool>> vis(v, vector<bool>(v, false));
    vector<vector<int>> grafo(v);

    for(int i = 0;i < a; i++){
        int v1, v2; cin >> v1 >> v2; v1--;v2--;
        grafo[v1].push_back(v2);
        grafo[v2].push_back(v1);
    }

    dfs(grafo, vis, 0);

    for (auto i : ciclos){
        for (auto j : i){
            cout << j+1 << " ";
        }
        cout << endl;
    }


    //a.insert(a.begin() + 1, b.begin(), b.end()); // insert b into a at index 1
    vector<int> euleriano;
    for (auto i : ciclos){
        if (euleriano.empty()){
            euleriano.insert(euleriano.begin(), i.begin(), i.end());
            continue;
        }

        auto it = find(euleriano.begin(), euleriano.end(), i[0]);
        euleriano.insert(it+1, i.begin()+1, i.end());
    }

    for (auto i : euleriano)
        cout << i+1 << " ";
    
}

// 6 10
// 1 2
// 1 3
// 2 3
// 2 4
// 2 5
// 3 4
// 3 5
// 4 5
// 4 6
// 5 6