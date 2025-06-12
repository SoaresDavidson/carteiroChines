#include <iostream>
#include <bits/stdc++.h>

using namespace std;
//push_back = append, .begin = iterator que aponta pro primeiro


bool eDeCorte(vector<vector<int>> g, int v1, int v2, int v = 0){
    for(auto i : g[v]){
        
    }
}

void fleury(vector<vector<int>> g){

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

}