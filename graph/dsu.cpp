/*input
4
1 2 3 4
1 2
2 3
2 4
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
Maintain a data structure over subtrees of a tree.
Answer a query for each subtree.
*/

const int maxn = 1e5+5;

int n, c[maxn], sz[maxn];

ll ans[maxn];

vector<int> adj[maxn];

struct coltracker {
	map<int,int> freq_of_col;
	map<int, ll> sum_of_freq;
	void add(int c, int cnt) {
		int f = freq_of_col[c];
		sum_of_freq[f] -= 1LL*c;
		sum_of_freq[f+cnt] += 1LL*c;
		freq_of_col[c] += cnt;
	}

	ll query() {return prev(sum_of_freq.end())->second;}

	void clear() {freq_of_col.clear(); sum_of_freq.clear();}
};

int treesz(int u, int p) {
	sz[u] = 1;
	for (int v : adj[u]) if (v!=p) sz[u] += treesz(v,u);
	return sz[u];
}

void dfs(int u, int p, coltracker& tracker) {
	int mxsz = -1, heavy = -1;
	for (int v : adj[u]) {
		if (v != p && sz[v] > mxsz) {
			heavy = v;
			mxsz = sz[v];
		}
	}
	if (heavy != -1) dfs(heavy, u, tracker);
	coltracker tmp;
	for (int v : adj[u]) {
		if (v != p && v != heavy) {
			tmp.clear();
			dfs(v, u, tmp);
			for (auto x : tmp.freq_of_col) tracker.add(x.first, x.second);
		}
	}
	tracker.add(c[u], 1);
	ans[u] = tracker.query();
}

int main() {
	// freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", c+i);
	for (int i = 1; i < n; ++i) {
		int a, b; scanf("%d%d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	treesz(1,0);
	coltracker tracker;
	dfs(1, 0, tracker);
	for (int i = 1; i <= n; ++i) printf("%lld ", ans[i]);
	printf("\n");
}