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
const int MAXN = 1e5+5;
using namespace std;
vector<int> adj[MAXN];

int N;

// temporary variables

int treesz[MAXN];
bool computed[MAXN];

// results
vector<int> centroid_tree[MAXN];

int centroid_parent[MAXN], centroid_root;
vector<int> centroid_children[MAXN];

// Use this to check if u is in the centroid subtree of v

int dfst=0, centroid_disc[MAXN], centroid_finish[MAXN];

void compute_disc_finish(int u, int p) {
	centroid_disc[u] = ++dfst;
	for (int v : centroid_children[u]) compute_disc_finish(v, u);
	centroid_finish[u] = ++dfst;
}	

void compute_tree_sizes(int u, int p) {
	treesz[u] = 1;
	for (int v : adj[u]) {
		if (v != p) compute_tree_sizes(v, u);
	}
}

int find_centroid(int u, int p, int sz) {
	for (int v : adj[u]) {
		if (!computed[v] && v != p) {
			if (treesz[v] > sz/2) return find_centroid(v, u, sz);
		}
	}
	return u;
}

void decompose(int u, int p) {

	// compute the sizes of the subtree
	compute_tree_sizes(u, p);

	// p is the parent of u in the original tree
	// first we find the centroid 

	int centroid = find_centroid(u, p, treesz[u]);
	computed[centroid] = true;

	// the parent of centroid is p

	centroid_parent[centroid] = p;
	centroid_children[p].push_back(centroid);

	for (int v : adj[centroid]) {
		if (!computed[v]) {
			decompose(v, u);
		}
	}

	if (p < 1) centroid_root = centroid;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i < N; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	decompose(1, -1);
	compute_disc_finish(centroid_root, -1);
}