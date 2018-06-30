#include <bits/stdc++.h>

/**
 * Simple min/max segment tree with support for point updates
 *
 */
template <typename T>
class RMQ {
   public:
    // Constructs the segment tree using bidirectional iterators [begin, end)
    template <class InputIterator>
    RMQ(InputIterator begin, InputIterator end) {
        n = end - begin;
        assert(n > 0);
        mn = std::vector<std::pair<T, int>>(4 * n);
        mx = std::vector<std::pair<T, int>>(4 * n);
        std::function<void(int, int, int)> build = [&](int u, int tl, int tr) {
            if (tl == tr) {
                mn[u] = {*(begin + tl), tl};
                mx[u] = {*(begin + tl), tr};
            } else {
                int tm = (tl + tr) / 2;
                build(2 * u, tl, tm);
                build(2 * u + 1, tm + 1, tr);
                mn[u] = std::min(mn[2 * u], mn[2 * u + 1]);
                mx[u] = std::max(mx[2 * u], mx[2 * u + 1]);
            }
        };
        build(1, 0, n - 1);
    }
    RMQ(int nn) {
        n = nn;
        std::function<void(int, int, int)> build = [&](int u, int tl, int tr) {
            if (tl == tr) {
                mn[u].second = tl;
                mx[u].second = tr;
            } else {
                int tm = (tl + tr) / 2;
                build(2 * u, tl, tm);
                build(2 * u + 1, tm + 1, tr);
                mn[u] = std::min(mn[2 * u], mn[2 * u + 1]);
                mx[u] = std::max(mx[2 * u], mx[2 * u + 1]);
            }
        };
        build(1, 0, n - 1);
    }
    // Returns the maximum in the range [l, r], 0-indexed as a (value, index)
    // pair. Ties are breaken by using the maximum index.
    std::pair<T, int> query_max(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return _querymx(1, 0, n - 1, l, r);
    }
    // Returns the minimum in the range [l, r], 0-indexed as a (value, index)
    // pair. Ties are breaken by using the minimum index.
    std::pair<T, int> query_min(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        return _querymn(1, 0, n - 1, l, r);
    }
    // Sets the value at index i to v
    void update(int i, T v) {
        assert(0 <= i && i < n);
        _update(1, 0, n - 1, i, v);
    }

   private:
    int n;
    std::vector<std::pair<T, int>> mn, mx;

    std::pair<T, int> _querymx(int u, int tl, int tr, int l, int r) const {
        if (tl > r || tr < l) {
            return {std::numeric_limits<T>::lowest(), -1};
        } else if (l <= tl && tr <= r) {
            return mx[u];
        } else {
            int tm = (tl + tr) / 2;
            auto lft = _querymx(2 * u, tl, tm, l, r);
            auto rt = _querymx(2 * u + 1, tm + 1, tr, l, r);
            return std::max(lft, rt);
        }
    }

    std::pair<T, int> _querymn(int u, int tl, int tr, int l, int r) const {
        if (tl > r || tr < l) {
            return {std::numeric_limits<T>::max(), -1};
        } else if (l <= tl && tr <= r) {
            return mn[u];
        } else {
            int tm = (tl + tr) / 2;
            auto lft = _querymn(2 * u, tl, tm, l, r);
            auto rt = _querymn(2 * u + 1, tm + 1, tr, l, r);
            return std::min(lft, rt);
        }
    }

    void _update(int u, int tl, int tr, int i, T v) {
        if (tl == tr) {
            mn[u] = {v, tl};
            mx[u] = {v, tl};
        } else {
            int tm = (tl + tr) / 2;
            if (i <= tm) {
                _update(2 * u, tl, tm, i, v);
            } else {
                _update(2 * u + 1, tm + 1, tr, i, v);
            }
            mn[u] = std::min(mn[2 * u], mn[2 * u + 1]);
            mx[u] = std::max(mx[2 * u], mx[2 * u + 1]);
        }
    }
};

using namespace std;

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