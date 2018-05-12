#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

vector<int> adj[MAXN];
int N;


int dfst=0, ncomps, disc[MAXN], lowlink[MAXN], onstack[MAXN], sz[MAXN], scc[MAXN];
// scc[u] is the scc component, 1 indexed
// sz[comp] is the number of nodes in the scc

stack<int> comp;

void tarjan(int u) {
	disc[u] = lowlink[u] = ++dfst;
	onstack[u] = true;
	comp.push(u);
	for (int v : adj[u]) {
		if (!disc[v]) {
			tarjan(v);
			lowlink[u] = min(lowlink[u], lowlink[v]);
		} else if (onstack[v]) {
			lowlink[u] = min(lowlink[u], disc[v]);
		}
	}
	if (disc[u] == lowlink[u]) {
		++ncomps;
		while (1) {
			int v = comp.top(); comp.pop();
			scc[v] = ncomps;
			sz[ncomps]++;
			onstack[v] = false;
			if (v==u) break;
		}
	}
}

// Tarjan performs a reverse topological sort
// So first reverse everything

unordered_set<int> dag[MAXN];

void compute_dag() {
	for (int u = 1; u <= N; ++u) scc[u] = ncomps-scc[u]+1;
	for (int i = 1; i < ncomps-i+1; ++i) swap(sz[i], sz[ncomps-i+1]);
	for (int u = 1; u <= N; ++u) 
		for (int v : adj[u]) 
			if (scc[u] != scc[v]) dag[scc[u]].insert(scc[v]);
}


int main() {
	for (int u = 1; u <= N; ++u) if (!disc[u]) tarjan(u);
	compute_dag();
}