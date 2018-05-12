#include <cstdio>
#include <cstring>
#include <vector>
#define MAXN 100005
using namespace std;
typedef long long ll;

int N, best[MAXN];
ll cnt[MAXN];
vector<int> adj[MAXN];

void dfs1(int u, int p, int& dia) {
    for (int v : adj[u]) {
        if (v==p) continue;
        dfs1(v, u, dia);
        if (best[u]+best[v]+1 > dia) 
            dia = best[u]+best[v]+1;
        if (best[u] < best[v]+1) best[u] = best[v]+1;
    }
}

int diameter1() {
    memset(best, 0, sizeof best);
    int dia = 0;
    dfs1(1, 0, dia);
    return dia;
}

void dfs2(int u, int p, int& dia, ll& ways) {
    for (int v : adj[u]) {
        if (v==p) continue;
        dfs1(v, u, dia);
        if (best[u]+best[v]+1 > dia) {
            dia = best[u]+best[v]+1;
            ways = cnt[u] * cnt[v];
        } else if (best[u]+best[v]+1==dia) 
            ways += cnt[u] * cnt[v];

        if (best[u] < best[v]+1) {
            best[u] = best[v]+1;
            cnt[u] = cnt[v];
        } else if (best[u]==best[v]+1)
            cnt[u] += cnt[v];
    }
}

int diameter2() {
    memset(best, 0, sizeof best);
    for (int i = 1; i <= N; ++i) cnt[i] = 1;
    int dia = 0;
    ll ways = 0;
    dfs2(1, 0, dia, ways);
    return dia;
}

int main() {
    scanf("%d", &N);
    for (int i = 0, a, b; i < N-1; ++i) {
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}