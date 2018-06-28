#include <bits/stdc++.h>
#define szof(v) ((int)(v).size())
using namespace std;
typedef vector<int> vi;

/**
 * Status: Locally tested.
 */
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

/**
 * Status: Untested.
 */
struct euler_lca_t {
    euler_lca_t(const vector<vector<int>> &t, int root = 0) {
        disc = vi(szof(t), -1);
        finish = vi(szof(t), -1);
        depth = vi(szof(t), -1);

        function<void(int, int, int)> dfs = [&](int u, int p, int d) {
            depth[u] = d;
            disc[u] = szof(dfslist);
            dfslist.push_back(u);
            for (int v : t[u]) {
                if (v != p) {
                    dfs(v, u, d + 1);
                    dfslist.push_back(u);
                }
            }
            finish[u] = szof(dfslist);
            dfslist.push_back(u);
        };

        dfs(0, -1, 0);

        segtree = vi(4 * szof(dfslist));

        function<void(int, int, int)> build = [&](int u, int tl, int tr) {
            if (tl == tr) {
                segtree[u] = dfslist[tl];
            } else {
                int tm = (tl + tr) / 2;
                build(2 * u, tl, tm);
                build(2 * u + 1, tm + 1, tr);
                segtree[u] = depth[segtree[2 * u]] < depth[segtree[2 * u + 1]] ? segtree[2 * u] : segtree[2 * u + 1];
            }
        };

        build(1, 0, szof(dfslist) - 1);
    }

    vi dfslist, disc, finish, depth, segtree;

    int _query(int u, int tl, int tr, int l, int r) {
        if (l <= tl && tr <= r) {
            return segtree[u];
        }
        int tm = (tl + tr) / 2;
        if (tm + 1 > r) {
            return _query(2 * u, tl, tm, l, r);
        } else if (tm < l) {
            return _query(2 * u + 1, tm + 1, tr, l, r);
        } else {
            int ansl = _query(2 * u, tl, tm, l, r);
            int ansr = _query(2 * u + 1, tm + 1, tr, l, r);
            return depth[ansl] < depth[ansr] ? ansl : ansr;
        }
    }

    int lca(int u, int v) {
        if (disc[u] > disc[v]) swap(u, v);
        return _query(1, 0, szof(dfslist)-1, disc[u], disc[v]);
    }
};