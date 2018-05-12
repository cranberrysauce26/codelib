#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
#define MAXN 10005
int N, M, color[MAXN]; // 0 for unvisited, otherwise 1 or -1
vector<int> adj[MAXN];
bool bipartite(int start) {
    queue<int> q;
    q.push(0); // 0 numbered.
    color[start] = 1;
    while ( !q.empty() ){
        int u = q.front(); q.pop();
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if (color[v]==0) color[v] = color[u], q.push(v);
            else if (color[v]!=color[u]) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    printf("%s\n", bipartite(0) ? "Is bipartite" : "Not bipartite");
}