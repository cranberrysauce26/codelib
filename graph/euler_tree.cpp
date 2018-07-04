/**
 * Suppose you have a tree where each vertex u has a value a[u].
 * The euler tree data structure allows you to:
 * 1. Find the sum of the values on the path from u to v for any u and v.
 * 2. Increment the value at node u by x.
 *
 * To the best of my knowledge, it only works if your combiner function has an
 * inverse for each value. For example, for addition, the inverse of x is -x.
 * For multiplication, it is 1/x. There is no inverse for things like min or
 * gcd, and more complex data structures like hld are required to solve those
 * problems.
 */

#include <bits/stdc++.h>
#define szof(v) ((int)(v).size())
using namespace std;
using vi = vector<int>;
using ll = long long;

struct bit {
    vector<ll> b;
    bit() {}
    bit(int n) { b = vector<ll>(n + 1); }
    ll sum(int x) const {
        ll res = 0;
        for (; x; x -= x & -x) res += b[x];
        return res;
    }
    void update(int x, ll v) {
        assert(x != 0);
        for (; x < szof(b); x += x & -x) b[x] += v;
    }

    void reset() { fill(b.begin(), b.end(), 0); }
};

/**
 * Status: Locally tested.
 */
struct lca {
    lca() {}
    lca(const vector<vi> &t, int root = 0) {
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
            for (int u = 0; u < n; ++u)
                p[k][u] = p[k - 1][u] == -1 ? -1 : p[k - 1][p[k - 1][u]];
    }

    int anc(int u, int d) const {
        for (int k = lg - 1; k >= 0; --k)
            if (d & (1 << k)) u = (u == -1) ? -1 : p[k][u];
        return u;
    }

    int operator()(int u, int v) const {
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
        int w = this->operator()(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    int lg, n;
    vi depth;
    vector<vi> p;
};

/**
 * Status: Untested.
 */
class euler_tree {
   public:
    euler_tree(const vector<vi> &tree) {
        disc.resize(szof(tree));
        finish.resize(szof(tree));
        int dfst = 0;
        function<void(int, int)> dfs = [&](int u, int p) {
            disc[u] = ++dfst;
            for (int v : tree[u]) {
                if (v != p) {
                    dfs(v, u);
                }
            }
            finish[u] = ++dfst;
        };
        dfs(0, -1);
    }
    // Increments vertex u's value by delta
    void add(int u, ll delta) {
        sum.update(disc[u], delta);
        sum.update(finish[u], -delta);
    }
    // Returns the sum of all values on the path from u to the root
    ll query(int u) const { return sum.sum(disc[u]); }
    // Returns the sum of all values on the path from u to v
    ll query(int u, int v) const {
        int w = lca_finder(u, v);
        return query(u) + query(v) - 2 * query(w);
    }

   private:
    // disc and finish are 1-indexed
    vi disc, finish;
    bit sum;
    lca lca_finder;
};