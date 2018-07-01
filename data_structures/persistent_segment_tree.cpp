#include <bits/stdc++.h>

/**
 * A persistent segment tree allows you to store the history of your segment
 * tree. The example below is a persistent sum segment tree.
 */
struct node {
    node(int s = 0) : sum(s), l(nullptr), r(nullptr) {}
    node(node *left, node *right) : l(left), r(right) {
        sum = left->sum + right->sum;
    }
    ~node() {
        if (l != nullptr) {
            delete l;
            l = nullptr;
        }
        if (r != nullptr) {
            delete r;
            r = nullptr;
        }
    }
    int sum;
    node *l, *r;
};

typedef node *pnode;

pnode build(int tl, int tr) {
    if (tl == tr) return new node();
    int tm = (tl + tr) / 2;
    return new node(build(tl, tm), build(tm + 1, tr));
}

/**
 * update returns a "copy" of u for the new segment tree.
 */
pnode update(pnode u, int tl, int tr, int x, int delta) {
    assert(u != nullptr);
    if (tl == tr) {
        return new node(u->sum + delta);
    }
    int tm = (tl + tr) / 2;
    if (x <= tm) {
        return new node(update(u->l, tl, tm, x, delta), u->r);
    } else {
        return new node(u->l, update(u->r, tm + 1, tr, x, delta));
    }
}

int query(pnode u, int tl, int tr, int l, int r) {
    assert(u != nullptr);
    if (tl > r || tr < l) return 0;
    if (l <= tl && tr <= r) {
        return u->sum;
    }
    int tm = (tl + tr) / 2;
    int left = query(u->l, tl, tm, l, r);
    int right = query(u->r, tm + 1, tr, l, r);
    return left + right;
}

int main() {
    srand(time(NULL));
    std::vector<pnode> T;
    const int n = 1000, q = 1000, maxval = 1e4;
    std::vector<std::vector<int>> versions(q + 1, std::vector<int>(n, 0));
    T.resize(q + 1);
    T[0] = build(0, n - 1);
    for (int i = 1; i <= q; ++i) {
        int x = rand() % n, delta = rand() % maxval;
        // printf("Version %d: adding %d to element %d\n", i, delta, x);
        T[i] = update(T[i - 1], 0, n - 1, x, delta);
        versions[i].assign(versions[i - 1].begin(), versions[i - 1].end());
        versions[i][x] = versions[i - 1][x] + delta;
    }

    int ac = 0;
    for (int i = 0; i < q; ++i) {
        int version = rand() % (q + 1), l = rand() % n, r = rand() % n;
        if (l > r) std::swap(l, r);
        // printf("Query: version %d, l = %d, r = %d\n", version, l, r);
        int got = query(T[version], 0, n - 1, l, r);
        int actual = 0;
        for (int j = l; j <= r; ++j) actual += versions[version][j];
        if (got == actual) {
            ++ac;
        } else {
            printf("WA: got %d expected %d\n", got, actual);
        }
    }
    printf("AC %d/%d\n", ac, q);
    // ONLY DO THIS LOCALLY BECAUSE IT TAKES TOO MUCH TIME!
    for (auto p : T) {
        if (p != nullptr) delete p;
    }
}