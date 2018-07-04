int depth[MAX], heavy[MAX], treesz[MAX], par[MAX];
void dfs(int u) {
    heavy[u] = -1;
    treesz[u] = 1;
    for (int v : adj[u]) {
        if (v != par[u]) {
            depth[v] = 1 + depth[u];
            par[v] = u;
            dfs(v);
            treesz[u] += treesz[v];
            if (heavy[u] == -1 || treesz[v] > treesz[heavy[u]]) {
                heavy[u] = v;
            }
        }
    }
}

int top[MAX], hldid[MAX], chainsz[MAX], hldnum = 0;
void hld_init(int u) {
    hldid[u] = ++hldnum;
    ++chainsz[top[u]];
    DEBUG("top[%d] = %d, hldid[%d] = %d\n", u, top[u], u, hldid[u]);
    for (int v : adj[u]) {
        if (v != par[u]) {
            if (v != heavy[u]) {
                top[v] = v;
                hld_init(v);
            } else {
                top[v] = top[u];
                hld_init(v);
            }
        }
    }
}

bit bit1, bit2;

void hld_update(int u, int val1, int val2) {
    DEBUG("hld_update(%d, %d, %d)\n", u, val1, val2);
    int lo = hldid[top[u]];
    int hi = hldid[u];
    if (val1 != 0) {
        bit1.update(lo, val1);
        bit1.update(hi + 1, -val1);
    }
    if (val2 != 0) {
        bit2.update(lo, val2);
        bit2.update(hi + 1, -val2);
    }
    u = top[par[top[u]]];
    while (u) {
        // chainsum1[u] += val1 * chainsz[u];
        // chainsum2[u] += val2 * chainsz[u];
        if (val1 != 0) {
            bit1.update(hldid[u], val1);
            bit1.update(hldid[u] + chainsz[u], -val1);
        }
        if (val2 != 0) {
            bit2.update(hldid[u], val2);
            bit2.update(hldid[u] + chainsz[u], -val2);
        }
        u = top[par[u]];
    }
}

inline ii count_between(int u) {
    int lo = hldid[top[u]];
    int hi = hldid[u];
    if (hi == lo + chainsz[top[u]] - 1) {
        return {bit1.sum(lo), bit2.sum(lo)};
    }
    return {bit1.sum(lo) - bit1.sum(hi + 1), bit2.sum(lo) - bit2.sum(hi + 1)};
}

ii hld_query(int u, int v) {
    ii res = {0, 0};
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]]) {
            ii toadd = count_between(u);
            res.first += toadd.first;
            res.second += toadd.second;
            u = par[top[u]];
        } else {
            ii toadd = count_between(v);
            res.first += toadd.first;
            res.second += toadd.second;
            v = par[top[v]];
        }
    }
    int lo = hldid[u], hi = hldid[v];
    if (lo > hi) {
        swap(lo, hi);
    }
    DEBUG("query(u = %d, v = %d) res = {%d, %d}\n", u, v, res.first,
          res.second);
    if (hi == hldid[top[u]] + chainsz[top[u]] - 1) {
        res.first += bit1.sum(lo);
        res.second += bit2.sum(lo);
    } else {
        res.first += bit1.sum(lo) - bit1.sum(hi + 1);
        res.second += bit2.sum(lo) - bit2.sum(hi + 1);
    }
    return res;
}