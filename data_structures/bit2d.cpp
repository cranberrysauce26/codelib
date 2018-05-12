#include <bits/stdc++.h>
#define MAXN 1003

int N, bit[MAXN][MAXN];

// update(x, y, v) adds v to (x, y).

void update(int x, int z, int v) {
	for (; x <= N; x += x&-x) 
		for (int y = z; y <= N; y += y&-y)
			bit[x][y] += v;
}

// query(x, y) is the sum for all (a, b) where 1 <= a <= x and 1 <= b <= y.

int query(int x, int z) {
	int res = 0;
	for (; x; x-= x&-x)
		for (int y = z; y; y -= y&-y)
			res += bit[x][y];
	return res;
}

int main() {
	N = 1000;
	update(1, 2, 1);
	assert(query(1, 1) == 0);
	assert(query(2, 3) == 1);
	update(3, 2, 5);
	assert(query(3, 2) == 6);
	assert(query(100, 100) == 6);
}