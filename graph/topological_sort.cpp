#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100005
using namespace std;
int N, M, visited[MAXN];
vector<int> adj[MAXN];

void dfs(int u, vector<int>& ts) {
    if (!visited[u]) {
        visited[u] = 1;
        for (size_t i = 0; i < adj[u].size(); ++i) dfs(adj[u][i], ts);
        ts.push_back(u);
    }
}

vector<int> dfs_topsort() {
    vector<int> ts;
    for (int i = 0; i < N; ++i) visited[i] = 0;
    for (int i = 0; i < N; ++i) dfs(i, ts);
    reverse(ts.begin(), ts.end());
    return ts;
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b);
    }
}