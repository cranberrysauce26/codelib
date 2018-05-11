#include <vector>
#include <cassert>
const int MAXN = 1e5+5, LOG = 21;
std::vector<int> adj[MAXN];

int n, p[MAXN][LOG], h[MAXN];

/**
 * NOTE: Assumes vertices are 1 indexed!
 * STATUS: Untested but should work
 */

void dfs(int u) {
	for (int v : adj[u]) {
		if (v!=p[u][0]) {
			p[v][0]=u;
			h[v]=h[u]+1;
			dfs(v);
		}
	}
}

void init() {
	for (int k = 1; k < LOG; ++k) {
		for (int u = 1; u <= n; ++u) {
			p[u][k] = p[p[u][k-1]][k-1];
		}
	}
}

/**
 * Returns the k'th parent of u.
 * Where the parent of u is the first parent,
 * the grandparent is the second, etc.
 * 
 * If the k'th parent does not exist, it returns 0.
 */
int anc(int u, int k) {
	for (int l = LOG-1; l >= 0; --l) {
		if (k&(1<<l)) {
			u = p[u][l];
		}
	}
	return u;
}

int lca(int u, int v) {
	if (h[u]<h[v]) {
		v = anc(v, h[v]-h[u]);
	} else if (h[u] > h[v]) {
		u = anc(u, h[u]-h[v]);
	}
	assert(h[u]==h[v]);
	if (u==v) return u; // or v

	for (int k = LOG-1; k >= 0; --k) {
		if (p[u][k]!=p[v][k]) {
			u = p[u][k];
			v = p[v][k];
		}
	}
	assert(u!=v);
	assert(p[u][0] == p[v][0]);
	return p[u][0]; // or p[v][0]
}