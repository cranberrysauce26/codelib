/**
 * Disjoint set data structure with path compression and rank heuristic
 */
#include <vector>

// 0 indexed
struct disjoint_set {
    std::vector<int> ds, rank;
    disjoint_set(int n) {
        ds = std::vector<int>(n);
        rank = std::vector<int>(n);
        for (int i = 0; i < n; ++i) ds[i] = i;
    }
    int find(int x) {
        return (x == ds[x]) ? x : ds[x] = find(ds[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rnk[x] < rnk[y])
            ds[x] = y;
        else {
            if (rnk[x] == rnk[y]) ++rnk[x];
            ds[y] = x;
        }
        return true;
    }
};

// 1 indexed
const int MAXN = 5e5 + 5;
int n, ds[MAXN], rnk[MAXN];
void init() {
    for (int i = 1; i <= n; ++i) ds[i] = i;
}
int find(int x) {
    return (x == ds[x]) ? x : ds[x] = find(ds[x]);
}
bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (rnk[x] < rnk[y])
        ds[x] = y;
    else {
        if (rnk[x] == rnk[y]) ++rnk[x];
        ds[y] = x;
    }
    return true;
}