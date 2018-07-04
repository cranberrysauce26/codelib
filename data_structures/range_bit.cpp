#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct bit {
    vector<ll> b;
    bit() {}
    bit(int N) { b = vector<ll>(N + 5); }
    ll sum(int x) {
        ll res = 0;
        for (; x; x -= x & -x) res += b[x];
        return res;
    }
    void update(int x, ll v) {
        for (; x < b.size(); x += x & -x) b[x] += v;
    }

    void reset() { fill(b.begin(), b.end(), 0); }
};

struct range_bit {
    bit m, b;
    range_bit(int N) {
        m = bit(N + 5);
        b = bit(N + 5);
    }

    // adds v to each element in [l, r]
    void update(int l, int r, ll v) {
        m.update(l, v);
        b.update(l, -v * (l - 1));

        m.update(r + 1, -v);
        b.update(r + 1, v * r);
    }

    // returns the sum of each element in [1, x]
    ll sum(int x) { return m.sum(x) * x + b.sum(x); }

    // returns the sum of each element in [l, r]
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }
};