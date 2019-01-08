#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct bit {
    vector<T> b;
    bit() {
    }
    bit(int N) {
        b = vector<T>(N + 5);
    }

    // Returns the sum of all elements in the range [1, x]
    T sum(int x) {
        T res = 0;
        for (; x; x -= x & -x) res += b[x];
        return res;
    }

    // Adds v to the element at index x
    void update(int x, T v) {
        for (; x < b.size(); x += x & -x) b[x] += v;
    }

    void reset() {
        fill(b.begin(), b.end(), 0);
    }
};

template <typename T>
struct range_bit {
    bit<T> m, b;
    range_bit(int N) {
        m = bit(N + 5);
        b = bit(N + 5);
    }

    // adds v to each element in [l, r]
    void update(int l, int r, T v) {
        m.update(l, v);
        b.update(l, -v * (l - 1));

        m.update(r + 1, -v);
        b.update(r + 1, v * r);
    }

    // returns the sum of each element in [1, x]
    T sum(int x) {
        return m.sum(x) * x + b.sum(x);
    }

    // returns the sum of each element in [l, r]
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};