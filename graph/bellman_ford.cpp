#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5, INF = 1e9;
typedef pair<int,int> ii;
vector<ii> adj[MAXN];


int n, m, dist[MAXN], pre[MAXN];

/**
 * shortest path from src that works for negative cycles
 * runs in O(n*m)
 * returns whether there is a negative cycle
 */

bool bellman_ford(int src) {
	fill(dist, dist+1+n, INF);
	dist[src] = 0;
	for (int i = 1; i < n; ++i) {
		for (int u = 1; u <= n; ++u) {
			for (ii e : adj[u]) {
				if (dist[u]+e.first < dist[e.second]) {
					dist[e.second] = dist[u]+e.first;
					pre[e.second] = u;
				}
			}
		}
	}
	for (int u = 1; u <= n; ++u) {
		for (ii e : adj[u]) {
			if (dist[u]+e.first < dist[e.second]) {
				return true;
			}
		}
	}
	return false;
}