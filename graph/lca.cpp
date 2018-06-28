#include <cassert>
#include <vector>
const int MAXN = 1e5 + 5, LOG = 21;
std::vector<int> adj[MAXN];

int n, p[MAXN][LOG], h[MAXN];

/**
 * NOTE: Assumes vertices are 1 indexed!
 * STATUS: Untested but should work
 */

void dfs(int u) {
    for (int v : adj[u]) {
        if (v != p[u][0]) {
            p[v][0] = u;
            h[v] = h[u] + 1;
            dfs(v);
        }
    }
}

void init() {
    for (int k = 1; k < LOG; ++k) {
        for (int u = 1; u <= n; ++u) {
            p[u][k] = p[p[u][k - 1]][k - 1];
        }
    }
}

/**
 * Returns the k'th parent of u.
 * Where the parent of u is the first parent,
 * the grandparent is the second, etc.
 *
 * If the k'th parent does not exist, it returns 0.
 */
int anc(int u, int k) {
    for (int l = LOG - 1; l >= 0; --l) {
        if (k & (1 << l)) {
            u = p[u][l];
        }
    }
    return u;
}

int lca(int u, int v) {
    if (h[u] < h[v]) {
        v = anc(v, h[v] - h[u]);
    } else if (h[u] > h[v]) {
        u = anc(u, h[u] - h[v]);
    }
    assert(h[u] == h[v]);
    if (u == v) return u;  // or v

    for (int k = LOG - 1; k >= 0; --k) {
        if (p[u][k] != p[v][k]) {
            u = p[u][k];
            v = p[v][k];
        }
    }
    assert(u != v);
    assert(p[u][0] == p[v][0]);
    return p[u][0];  // or p[v][0]
}

// or

/**
 * Way 2 uses eulerian tours on the tree
 */
namespace way2 {
// status: tested
const int MAX = 1e5 + 5;
int depth[MAX], par[MAX], enter[MAX], leave[MAX], dfslist[3 * MAX], dfst = 0;

void dfs(int u, int p, int h) {
    depth[u] = h;
    par[u] = p;
    dfslist[++dfst] = u;
    enter[u] = dfst;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, h + 1);
            dfslist[++dfst] = u;
        }
    }
    dfslist[++dfst] = u;
    leave[u] = dfst;
}

int lcatree[12 * MAX];
void lca_build(int u, int tl, int tr) {
    if (tl == tr) {
        lcatree[u] = dfslist[tl];
    } else {
        int tm = (tl + tr) / 2;
        lca_build(2 * u, tl, tm);
        lca_build(2 * u + 1, tm + 1, tr);
        lcatree[u] = depth[lcatree[2 * u]] < depth[lcatree[2 * u + 1]] ? lcatree[2 * u] : lcatree[2 * u + 1];
    }
}
int lca_query(int u, int tl, int tr, int l, int r) {
    if (l <= tl && tr <= r) {
        return lcatree[u];
    }
    int tm = (tl + tr) / 2;
    if (tm + 1 > r) {
        return lca_query(2 * u, tl, tm, l, r);
    } else if (tm < l) {
        return lca_query(2 * u + 1, tm + 1, tr, l, r);
    } else {
        int ansl = lca_query(2 * u, tl, tm, l, r);
        int ansr = lca_query(2 * u + 1, tm + 1, tr, l, r);
        return depth[ansl] < depth[ansr] ? ansl : ansr;
    }
}

int lca(int u, int v) { return lca_query(1, 1, dfst, std::min(enter[u], enter[v]), std::max(enter[u], enter[v])); }
}  // namespace way2

#define szof(v) ((int)(v).size())
#include <vector>
#include <functional>
using namespace std;
typedef vector<int> vi;
struct lca_t {
    lca_t() {}
    lca_t(const vector<vi> &t, int root = 0) {
        lg = 0;
        n = szof(t);
        while (1 << lg <= szof(t)) ++lg;
        p = vector<vi>(lg, vi(n, -1));
        depth = vi(n, 0);
        function<void(int)> dfs = [&](int u) {
            for (int v : t[u]) {
                if (v != p[0][u]) {
                    p[0][v] = u;
                    depth[v] = 1 + depth[u];
                    dfs(v);
                }
            }
        };
        dfs(root);
        for (int k = 1; k < lg; ++k)
            for (int u = 0; u < n; ++u) p[k][u] = p[k - 1][u] == -1 ? -1 : p[k - 1][p[k - 1][u]];
    }

    int anc(int u, int d) const {
        for (int k = lg - 1; k >= 0; --k)
            if (d & (1 << k)) u = (u == -1) ? -1 : p[k][u];
        return u;
    }

    int lca(int u, int v) const {
        if (depth[u] > depth[v])
            u = anc(u, depth[u] - depth[v]);
        else if (depth[v] > depth[u])
            v = anc(v, depth[v] - depth[u]);
        assert(depth[u] == depth[v]);
        if (u == v) return u;
        for (int k = lg - 1; k >= 0; --k)
            if (p[k][u] != p[k][v]) u = p[k][u], v = p[k][v];
        assert(p[0][u] == p[0][v] && u != v);
        return p[0][u];
    }

    int dist(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    int lg, n;
    vi depth;
    vector<vi> p;
};