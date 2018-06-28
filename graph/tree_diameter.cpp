#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
#define szof(v) ((int)(v).size())

/**
 * Status: Tested.
 * IMO the simplest to understand because it's just tree dp.
 * However I usually don't see people find the tree diameter this way.
 * The dfs returns the maximum distance from u to a vertex in u's subtree.
 * To find the diameter, just pick the farthest two leaves.
 */
int tree_diameter(const vector<vector<int>>& tree) {
    int dia = 0;
    function<int(int, int)> dfs = [&](int u, int p) {
        int best = 0;
        for (int v : tree[u]) {
            if (v != p) {
                int bestv = dfs(v, u);
                if (best + bestv + 1 > dia) {
                    dia = best + bestv + 1;
                }
                if (best < bestv + 1) {
                    best = bestv + 1;
                }
            }
        }
        return best;
    };
    dfs(0, -1);
    return dia;
}

/**
 * Status: Untested.
 * Returns the number of ways to make the diameter.
 * It can be optimized to constant memory but I don't really feel like it rn.
 */
pair<int, ll> tree_diameter_with_ways(const vector<vector<int>>& tree) {
    vector<ll> cnt(szof(tree), 1LL);
    vector<int> best(szof(tree), 0);
    int dia = 0;
    ll ways = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        for (int v : tree[u]) {
            if (v != p) {
                dfs(v, u);
                if (best[u] + best[v] + 1 > dia) {
                    dia = best[u] + best[v] + 1;
                    ways = cnt[u] * cnt[v];
                } else if (best[u] + best[v] + 1 == dia) {
                    ways += cnt[u] * cnt[v];
                }

                if (best[u] < best[v] + 1) {
                    best[u] = best[v] + 1;
                    cnt[u] = cnt[v];
                } else if (best[u] == best[v] + 1) {
                    cnt[u] += cnt[v];
                }
            }
        }
    };
    dfs(0, -1);
    return make_pair(dia, ways);
}

/**
 * Status: Tested.
 */
pair<int, ii> tree_diameter_with_endpoints(const vector<vector<int>>& tree) {
    int dia = 0;
    ii ends;
    // Returns a pair (distance, vertex) representing the farthest vertex from u
    function<ii(int, int, int)> farthest = [&](int u, int p, int depth) {
        int dist = depth, end = u;
        for (int v : tree[u]) {
            if (v != p) {
                auto res = farthest(v, u, depth + 1);
                if (res.first > dist) {
                    dist = res.first;
                    end = res.second;
                }
            }
        }
        return make_pair(dist, end);
    };
    ends.first = farthest(0, -1, 0).second;
    auto ans = farthest(ends.first, -1, 0);
    ends.second = ans.second;
    dia = ans.first;
    return make_pair(dia, ends);
}

int main() {
    printf("Enter your tree (Note: 0-indexed!)\n");
    int n;
    scanf("%d", &n);
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    int dia = tree_diameter(tree);
    printf("The tree diameter is %d\n", dia);
    auto dia2 = tree_diameter_with_endpoints(tree);
    printf("With endpoints, we got a diameter of %d and a pair of vertices %d and %d\n", dia2.first, dia2.second.first, dia2.second.second);
}