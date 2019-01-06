#include <bits/stdc++.h>
using namespace std;

// bit maintains a prefix sum for the array a[1...n]
template <typename T>
struct bit {
    vector<T> b;
    int lg, n;

    bit(int m) {
        n = m;
        b = vector<T>(n + 1);
        lg = 0;
        while ((1 << lg) <= n) ++lg;
    }

    // Increments index i by value
    void add(int i, T value) {
        assert(i > 0 && i <= n);
        for (; i < b.size(); i += i & -i) b[i] += value;
    }

    // Returns the sum of [1, i]
    T sum(int i) const {
        assert(i >= 0 && i <= n);
        T ret = 0;
        for (; i; i -= i & -i) ret += b[i];
        return ret;
    }

    // Status: Untested
    // Returns the i'th entry. Equivalent to sum(i)-sum(i-1)
    T entry(int i) const {
        assert(i > 0 && i <= n);
        T ret = 0;
        int z = i - (i & -i);
        for (--i; i != z; i -= i & -i) ret += b[i];
        return ret;
    }

    // The following functions work only if all array entries are non-negative

    // Status: Tested
    // Returns the smallest j > i such that sum(j) - sum(i) > value, or end() if no such j exists
    // Equivalently the smallest j such that sum(j) > value + sum(i)
    int upperbound(int i, T value) const {
        assert(value >= 0 && i <= n && i >= 0);
        value += sum(i);
        i = 0;
        for (int k = lg; k >= 0; --k) {
            if (i + (1 << k) <= n && b[i + (1 << k)] <= value) {
                i += 1 << k;
                value -= b[i];
            }
        }
        return i + 1;
    }

    // Status: Untested
    // Returns the smallest j > i such that sum(j) - sum(i) >= value or end() if no such j exists
    int lowerbound(int i, T value) const {
        assert(value > 0 && i <= n && i >= 0);
        value += sum(i);
        i = 0;
        for (int k = lg; k >= 0; --k) {
            if (i + (1 << k) <= n && b[i + (1 << k)] < value) {
                i += 1 << k;
                value -= b[i + (1 << k)];
            }
        }
        return i + 1;
    }

    // Status: Tested
    // If you think of the bit as a set, this is the next (nonzero) element
    int next(int i) const {
        return upperbound(i, 0);
    }

    // TODO: Implement prev
    int prev(int i) const {
        return -1;
    }

    // Calls to lowerbound, next, and upperbound return end when no valid index exists
    inline int end() const {
        return n + 1;
    }
};