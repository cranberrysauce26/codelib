#ifndef FORD_FULKERSON_H
#define FORD_FULKERSON_H
#include <cstring>
#include <algorithm>

// Usage:
// 1 INDEXED!!!!!
// Set MAX_VERTS and INF
// set nv := number of vertices
// set g, the capacity graph (NOTE THAT maxflow uses g as the residual graph so it changes!)
// Call maxflow with s = source, t = sink

struct ford_fulkerson_t {
	static const int MAX_VERTS = 205, INF = 2e9;
	int nv, visit[MAX_VERTS], par[MAX_VERTS], g[MAX_VERTS][MAX_VERTS];
	bool dfs(int u, int dest) {
		visit[u] = true;
		if (u == dest) return true;
		for (int v = 1; v <= nv; ++v) {
			if (!visit[v] && g[u][v] != 0) {
				par[v] = u;
				if (dfs(v, dest)) return true;
			}
		}
		return false;
	}
	int maxflow(int s, int t) {
		int mflow = 0;
		memset(visit, 0, sizeof visit);
		memset(par, 0, sizeof par);
		while (dfs(s,t)) {
			int pflow = INF;
			for (int u = t; u != s; u = par[u]) {
				pflow = std::min(pflow, g[par[u]][u]);
			}
			for (int u = t; u != s; u = par[u]) {
				g[u][par[u]] += pflow;
				g[par[u]][u] -= pflow;
			}
			mflow += pflow;
			memset(par, 0, sizeof par);
			memset(visit, 0, sizeof visit);
		}
		return mflow;
	}
};
#endif