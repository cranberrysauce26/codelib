#include <bits/stdc++.h>
using namespace std;
bool is_dag(vector<vector<int>> g) {
    bool dag = true;
    vector<int> vis(g.size(), 0);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 2;
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs(v);
            } else if (vis[v] == 2) {
                dag = false;
            }
        }
        vis[u] = 1;
    };
    return dag;
}

template <typename T>
bool is_dag(vector<vector<pair<T, int>>> g) {
    bool dag = true;
    vector<int> vis(g.size(), 0);
    function<void(int)> dfs = [&](int u) {
        vis[u] = 2;
        for (auto e : g[u]) {
            if (vis[e.second] == 0) {
                dfs(e.second);
            } else if (vis[e.second] == 2) {
                dag = false;
            }
        }
        vis[u] = 1;
    };
    return dag;
}