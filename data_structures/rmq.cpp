#include <bits/stdc++.h>
using namespace std;

/**
 * Simple min/max segment tree with support for point updates
 */
template <typename T>
class RMQ {
   public:
    RMQ() {
    }
    // Constructs the segment tree using bidirectional iterators [begin, end)
    template <typename InputIterator>
    RMQ(InputIterator begin, InputIterator end) {
        n = end - begin;
        assert(n > 0);
        mn = vector<pair<T, int>>(4 * n);
        mx = vector<pair<T, int>>(4 * n);
        function<void(int, int, int)> build = [&](int u, int tl, int tr) {
            if (tl == tr) {
                mn[u] = {*(begin + tl), tl};
                mx[u] = {*(begin + tl), tr};
            } else {
                int tm = (tl + tr) / 2;
                build(2 * u, tl, tm);
                build(2 * u + 1, tm + 1, tr);
                mn[u] = min(mn[2 * u], mn[2 * u + 1]);
                mx[u] = max(mx[2 * u], mx[2 * u + 1]);
            }
        };
        build(1, 0, n - 1);
    }
    // Returns the maximum in the range [l, r], 0-indexed as a (value, index)
    // pair. Ties are breaken by using the maximum index.
    pair<T, int> query_max(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return query(1, 0, n - 1, l, r, 1);
    }
    // Returns the minimum in the range [l, r], 0-indexed as a (value, index)
    // pair. Ties are breaken by using the minimum index.
    pair<T, int> query_min(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return query(1, 0, n - 1, l, r, 0);
    }
    // Sets the value at index i to v
    void update(int i, T v) {
        assert(0 <= i && i < n);
        update(1, 0, n - 1, i, v);
    }

   private:
    int n;
    vector<pair<T, int>> mn, mx;
    pair<T, int> query(int u, int tl, int tr, int l, int r, int t) const {
        if (l <= tl && tr <= r) return t ? mx[u] : mn[u];
        int tm = (tl + tr) / 2;
        if (r <= tm)
            return query(2 * u, tl, tm, l, r, t);
        else if (tm < l)
            return query(2 * u + 1, tm + 1, tr, l, r, t);
        auto a = query(2 * u, tl, tm, l, r, t), b = query(2 * u + 1, tm + 1, tr, l, r, t);
        return t ? max(a, b) : min(a, b);
    }
    void update(int u, int tl, int tr, int i, T v) {
        if (tl == tr) {
            mn[u] = {v, tl};
            mx[u] = {v, tl};
        } else {
            int tm = (tl + tr) / 2;
            if (i <= tm)
                update(2 * u, tl, tm, i, v);
            else
                update(2 * u + 1, tm + 1, tr, i, v);
            mn[u] = min(mn[2 * u], mn[2 * u + 1]);
            mx[u] = max(mx[2 * u], mx[2 * u + 1]);
        }
    }
};

int main() {
    srand(time(NULL));
    int n = 1000;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rand();
    }
    // Note: RMQ also works for arrays
    RMQ<int> rmq(begin(a), end(a));
    int q = 500, ac = 0;
    for (int i = 0; i < q; ++i) {
        int l = rand() % n, r = rand() % n;
        if (l > r) {
            swap(l, r);
        }
        auto gotmx = rmq.query_max(l, r);
        auto gotmn = rmq.query_min(l, r);

        int realmx = std::numeric_limits<int>::lowest();
        int realmn = std::numeric_limits<int>::max();
        for (int i = l; i <= r; ++i) {
            realmx = max(realmx, a[i]);
            realmn = min(realmn, a[i]);
        }

        if (gotmx.first == realmx && gotmn.first == realmn) {
            if (a[gotmx.second] == realmx && a[gotmn.second] == realmn) {
                ++ac;
            }
        }
        int j = rand() % n;
        int v = rand();
        a[j] = v;
        rmq.update(j, v);
    }
    printf("AC %d/%d\n", ac, q);
}