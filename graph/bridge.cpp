#include <bits/stdc++.h>
#define szof(v) ((int)(v).size())
using namespace std;

typedef pair<int, int> ii;

/**
 * Status: Tested.
 * Returns a vector of booleans representing whether the i'th edge is a bridge.
 */
vector<bool> find_bridges(const vector<vector<int>> &g, const vector<ii> &e) {
    vector<bool> isbridge(szof(e), 0);
    vector<int> lowlink(szof(g), -1), disc(szof(g), -1);

    auto adj = [&](int u, int edge) { return e[edge].first == u ? e[edge].second : e[edge].first; };

    int dfst = 0;
    function<void(int, int)> dfs = [&](int u, int par_edge) {
        lowlink[u] = disc[u] = dfst++;
        for (int ee : g[u]) {
            int v = adj(u, ee);
            if (disc[v] == -1) {
                dfs(v, ee);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } else if (ee != par_edge) {
                lowlink[u] = min(lowlink[u], disc[v]);
            }
        }
        // Let the dfs parent of u be p
        // then (p,u) is a bridge
        // iff lowlink[u] > disc[p]

        if (par_edge != -1) {
            int p = adj(u, par_edge);
            if (lowlink[u] > disc[p]) {
                isbridge[par_edge] = true;
            }
        }
    };

    for (int u = 0; u < szof(g); ++u) {
        if (disc[u] == -1) {
            dfs(u, -1);
        }
    }

    return isbridge;
}

/**
 * Status: Tested.
 * Returns the bridge tree of undirected graph g (or the bridge forest, iff g is disconnected), inputted as an edge list.
 * The number of vertices is n = szof(g)
 * g[u] contains the id's of the edges adjacent to u for 0 <= u < n
 * e[id] is (a, b) representing an edge between vertices a and b
 *
 * The function returns the bridge tree as an adjancency list.
 * component[u] returns the component that vertex u ends up in in the bridge forest
 */
vector<vector<int>> bridge_tree(const vector<vector<int>> &g, const vector<ii> &e, vector<int> &component) {
    component = vector<int>(szof(g), -1);
    auto adj = [&](int u, int edge) { return e[edge].first == u ? e[edge].second : e[edge].first; };
    auto isbridge = find_bridges(g, e);
    vector<vector<int>> tree;
    vector<bool> visit(szof(g), 0);
    int numcomps = 0;

    function<void(int, int)> build_tree = [&](int u, int comp) {
        visit[u] = 1;
        component[u] = comp;
        for (int ee : g[u]) {
            int v = adj(u, ee);
            if (!visit[v]) {
                if (isbridge[ee]) {
                    tree.push_back(vector<int>());
                    assert(szof(tree) - 1 == numcomps);
                    tree[comp].push_back(numcomps);
                    tree[numcomps].push_back(comp);
                    ++numcomps;
                    build_tree(v, numcomps - 1);
                } else {
                    build_tree(v, comp);
                }
            }
        }
    };

    for (int u = 0; u < szof(g); ++u) {
        if (!visit[u]) {
            tree.push_back(vector<int>());
            assert(szof(tree) - 1 == numcomps);
            ++numcomps;
            build_tree(u, numcomps - 1);
        }
    }
    return tree;
}

int main() {
    int n, m;
    printf("Enter your tree (Note: 0-indexed!)\n");
    scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    vector<ii> e(m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &e[i].first, &e[i].second);
        g[e[i].first].push_back(i);
        g[e[i].second].push_back(i);
    }
    vector<int> comp;
    auto t = bridge_tree(g, e, comp);
    printf("The bridge tree has %d vertices\n", szof(t));
    for (int i = 0; i < n; ++i) {
        printf("Vertex %d is in component %d\n", i, comp[i]);
    }
    for (int i = 0; i < szof(t); ++i) {
        printf("Vertices adjacent to %d: ", i);
        for (int x : t[i]) {
            printf("%d ", x);
        }
        printf("\n");
    }
}