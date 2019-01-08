/*input
4
2 1
1 3
4 1
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
typedef pair<int, int> ii;

int N, p[MAXN], h[MAXN];
vector<int> adj[MAXN];

int farthest(int u, int par, int height) {
    p[u] = par;
    h[u] = height;
    int w = u;
    for (int v : adj[u]) {
        if (v != par) {
            int q = farthest(v, u, height + 1);
            if (h[q] > h[w]) w = q;
        }
    }
    return w;
}

int main() {
    scanf("%d", &N);
    for (int i = 1, a, b; i < N; ++i) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int u = farthest(1, 0, 0);
    int v = farthest(u, 0, 0);

    int center = v;
    int diameter = h[v];

    for (int i = 0; i < diameter / 2; ++i) center = p[center];

    farthest(center, 0, 0);
}