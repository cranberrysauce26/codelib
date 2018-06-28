/*
USAGE:

After doing centroid decomposition, you can do a dfs from every node in the centroid tree
and have an Nlog N complexity.

This is because there are at most log N subtrees that any given node can be part of
(because the height of the tree is log N).

For example, let's say you want to compute the number of pairs (u, v)
such that dist(u, v) = K.

Then go to every node u in the centroid tree.

Solve the problem for every child v of u.

Then iterate through each v and look at that subtree.
Compute a vector of distances and combine them to get the result.

*/
#include <bits/stdc++.h>
using namespace std;
#define szof(v) ((int)(v).size())
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
typedef vector<int> vi;

/**
 * Takes a tree as input and returns the centroid of the tree.
 * It compute cpar by reference, the parent of each node in the centroid tree.
 */
int decompose(const vector<vi> &t, vi &cpar) {
    vi sz(szof(t), 0);
	vector<bool> visit(szof(t), false);
    cpar = vi(szof(t));
    function<int(int, int)> treesz = [&](int u, int p) {
        sz[u] = 1;
        for (int v : t[u])
            if (v != p && !visit[v]) sz[u] += treesz(v, u);
        return sz[u];
    };
    function<int(int, int, int)> findcentroid = [&](int u, int p, int rootsz) {
        for (int v : t[u])
            if (v != p && !visit[v])
                if (sz[v] > rootsz / 2) return findcentroid(v, u, rootsz);
        return u;
    };
    int dfst = 0;
    function<int(int, int)> dfs = [&](int u, int p) {
        int c = findcentroid(u, p, treesz(u, p));
        visit[c] = true;
        cpar[c] = p;
        for (int v : t[c])
            if (!visit[v]) dfs(v, c);
        return c;
    };
    return dfs(0, -1);
}