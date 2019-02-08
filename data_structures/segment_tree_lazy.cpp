#include <bits/stdc++.h>
using namespace std;

/**
 * Status: Tested
 * Supports adding x to [l, r] and querying minimum in [l, r]
 */
template <typename U>
struct min_query_add_update_node {
    U lazy, mn;
    min_query_add_update_node()
        : lazy(0), mn(0) {
    }
    min_query_add_update_node(U x)
        : lazy(0), mn(x) {
    }
    min_query_add_update_node(min_query_add_update_node a, min_query_add_update_node b)
        : mn(min(a.mn, b.mn)), lazy(0) {
    }
    bool islazy() const {
        return lazy != 0;
    }
    void apply(U x) {
        mn += x;
        lazy += x;
    }
    void update_child(min_query_add_update_node& u) const {
        u.apply(lazy);
    }
    void unlazy() {
        lazy = 0;
    }
};

/**
 * Status: Untested
 * Supports setting each a[i] to min(a[i], v) in [l, r] and querying minimum in [l, r]
 */
template <typename U>
struct min_query_min_update_node {
    U lazy, mn;
    min_query_min_update_node()
        : lazy(0), mn(0) {
    }
    min_query_min_update_node(U x)
        : lazy(0), mn(x) {
    }
    min_query_min_update_node(min_query_min_update_node a, min_query_min_update_node b)
        : mn(min(a.mn, b.mn)), lazy(0) {
    }
    bool islazy() const {
        return lazy != 0;
    }
    void apply(U x) {
        mn = min(mn, x);
        lazy = min(mn, x);
    }
    void update_child(min_query_add_update_node& u) const {
        u.apply(lazy);
    }
    void unlazy() {
        lazy = 0;
    }
};

/**
 * Status: Tested
 * Lazy segment tree
 * T is the node type
 * U is the update type
 */
template <typename T, typename U>
class lazy_segtree {
   public:
    lazy_segtree(int n)
        : n(n), t(vector<T>(4 * n)) {
    }

    // Pass iterators [begin, end) of any type S such that T has constructor T(S)
    template <typename InputIterator>
    lazy_segtree(InputIterator begin, InputIterator end)
        : n(end - begin), t(vector<T>(4 * n)) {
        function<void(int, int, int)> build = [&](int u, int tl, int tr) {
            if (tl == tr)
                t[u] = T(*(begin + tl));
            else {
                int tm = (tl + tr) / 2;
                build(2 * u, tl, tm);
                build(2 * u + 1, tm + 1, tr);
                t[u] = T(t[2 * u], t[2 * u + 1]);
            }
        };
        build(1, 0, n - 1);
    }

    void update(int l, int r, U v) {
        update(1, 0, n - 1, l, r, v);
    }

    T query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

   private:
    int n;
    vector<T> t;

    void pushdown(int u, int tl, int tr) {
        if (t[u].islazy() && tl != tr) {
            t[u].update_child(t[2 * u]);
            t[u].update_child(t[2 * u + 1]);
            t[u].unlazy();
        }
    }

    T query(int u, int tl, int tr, int l, int r) {
        pushdown(u, tl, tr);
        if (l <= tl && tr <= r) return t[u];
        int tm = (tl + tr) / 2;
        if (tm < l)
            return query(2 * u + 1, tm + 1, tr, l, r);
        if (tm >= r)
            return query(2 * u, tl, tm, l, r);
        return T(query(2 * u, tl, tm, l, r), query(2 * u + 1, tm + 1, tr, l, r));
    }

    void update(int u, int tl, int tr, int l, int r, U v) {
        pushdown(u, tl, tr);
        if (l <= tl && tr <= r) return t[u].apply(v);
        int tm = (tl + tr) / 2;
        if (l <= tm) update(2 * u, tl, tm, l, r, v);
        if (tm + 1 <= r) update(2 * u + 1, tm + 1, tr, l, r, v);
        t[u] = T(t[2 * u], t[2 * u + 1]);
    }
};

int main() {
    auto v = vector<long long>{0, 1, 2, 3, 4};
    lazy_segtree<min_query_add_update_node<long long>, long long> t(v.begin(), v.end());
    assert(t.query(0, 1).mn == 0);
    t.update(0, 2, 1e10);
    cout << t.query(0, 1).mn << "\n";
}