#include <cstdio>
#include <queue>
#include <functional>
#define MAXN 100005
#define INF 1000000000
using namespace std;
typedef pair<int, int> ii;
int N, M, dist[MAXN];
vector<ii> adj[MAXN];
priority_queue<ii, vector<ii>, greater<ii> > pq;

int dijkstra(int src, int dst) {
    for (int i = 1; i <= N; ++i) dist[i] = INF;
    dist[src]=0;
    pq.push(ii(0, src));
    while (!pq.empty()) {
        ii front = pq.top(); pq.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue;
        if (u==dst) return d;
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second, w = adj[u][i].first;
            if (w+d < dist[v]) {
                dist[v] = w+d;
                pq.push(ii(dist[v], v));
                // pre[v] = u if you want a shortest path tree!
            }
        }
    }
    return INF;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        adj[a].emplace_back(w, b);
        // adj[a].push_back(ii(w, b));
        adj[b].push_back(ii(w, a));
    }
    int a, b; scanf("%d%d", &a, &b);
    printf("%d\n", dijkstra(a, b));
}