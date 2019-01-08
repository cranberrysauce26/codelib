#include <vector>

template <typename T>
struct segtree {
    std::vector<T> t, a;

    /** Customize this! **/
    inline T combine(T a, T b) {
        return a + b;
    }

    segtree(std::vector<T> a)
        : a(a) {
        t = std::vector<T>(4 * a.size());
        build(1, 0, a.size() - 1);
    }

    void build(int u, int l, int r) {
        if (l != r) {
            int m = (l + r) / 2;
            build(2 * u, l, m);
            build(2 * u + 1, m + 1, r);
            t[u] = combine(t[2 * u], t[2 * u + 1]);
        } else {
            t[u] = a[l];
        }
    }

    // Returns the answer for [l, r]
    T query(int l, int r) {
        return query(1, 0, a.size() - 1, l, r);
    }

    T query(int u, int tl, int tr, int l, int r) {
        if (l <= tl && tr <= r) {
            return t[u];
        }
        int tm = (tl + tr) / 2;
        if (l <= tm && tm < r) {
            return combine(query(2 * u, tl, tm, l, r), query(2 * u + 1, tm + 1, tr, l, r));
        } else if (tm < l) {
            return query(2 * u + 1, tm + 1, tr, l, r);
        } else {
            assert(tm >= r);
            return query(2 * u, tl, tm, l, r);
        }
    }

    void update(int i, T v) {
        update(1, 0, a.size() - 1, i, v);
    }

    // Updates a[i] = v
    void update(int u, int tl, int tr, int i, T v) {
        if (tl == tr) {
            t[u] = a[i] = v;
        } else {
            int tm = (tl + tr) / 2;
            if (i <= tm) {
                update(2 * u, tl, tm, i, v);
            } else {
                update(2 * u + 1, tm + 1, tr, i, v);
            }
            t[u] = combine(t[2 * u], t[2 * u + 1]);
        }
    }
};