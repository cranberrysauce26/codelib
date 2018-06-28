#include <algorithm>
#include <cassert>
#include <cstdio>
const int MAXN = 1e5 + 5;

// EVERYTHING IS 1-INDEXED!!

namespace point_update_range_query {
namespace prefix {
int bit[MAXN];

// add v to value at x.
void update(int x, int v) {
    for (; x < MAXN; x += x & -x)
        bit[x] += v;
}

// sum from [1, x]
int query(int x) {
    int res = 0;
    for (; x; x -= x & -x)
        res += bit[x];
    return res;
}
} // namespace prefix

namespace suffix {
int bit[MAXN];

// add v to value at x
void update(int x, int v) {
    for (; x; x -= x & -x)
        bit[x] += v;
}

// sum from [x, MAXN-1]
int query(int x) {
    int res = 0;
    for (; x < MAXN; x += x & -x)
        res += bit[x];
    return res;
}
} // namespace suffix
} // namespace point_update_range_query

namespace range_update_point_query {
int bit[MAXN];

// add v to value at x.
void update(int x, int v) {
    for (; x; x -= x & -x)
        bit[x] += v;
}

// sum from [1, x]
int query(int x) {
    int res = 0;
    for (; x < MAXN; x += x & -x)
        res += bit[x];
    return res;
}
} // namespace range_update_point_query

namespace range_update_range_query {
int bit1[MAXN], bit2[MAXN];

void internal_update(int x, int v, int *bit) {
    for (; x < MAXN; x += x & -x)
        bit[x] += v;
}

int internal_query(int x, int *bit) {
    int res = 0;
    for (; x; x -= x & -x)
        res += bit[x];
    return res;
}

// adds v to all values in [l, r]
void update(int l, int r, int v) {
    internal_update(l, v, bit1);
    internal_update(r + 1, -v, bit1);
    internal_update(l, v - v * l, bit2);
    internal_update(r + 1, v * l - v, bit2);
}

// returns the sum of elements in [1, x]
int query(int x) {
    return x * internal_query(x, bit1) + internal_query(x, bit2);
}

int query(int l, int r) { return query(r) - query(l - 1); }
} // namespace range_update_range_query

int bit[MAXN];

// add v to value at x.
void update(int x, int v) {
    for (; x < MAXN; x += x & -x)
        bit[x] += v;
}

// sum from [1, x]
int query(int x) {
    int res = 0;
    for (; x; x -= x & -x)
        res += bit[x];
    return res;
}

int main() {
	update(1, 1);
	update(2, -1);
	update(1, 1);
	update(3, -1);
	printf("%d\n", query(1));
}