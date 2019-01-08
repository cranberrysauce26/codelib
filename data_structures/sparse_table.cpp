#include <algorithm>
#include <cstdio>
#define MAXN 100005
#define LOG 20
using namespace std;
int N, Q, A[MAXN], m[MAXN][LOG];

// minimum in [l, r]
int query(int l, int r) {
    int k = 32 - __builtin_clz(r - l + 1) - 1;
    return A[m[l][k]] < A[m[r - (1 << k) + 1][k]] ? m[l][k] : m[r - (1 << k) + 1][k];
}

void build() {
    for (int i = 1; i <= N; ++i) m[i][0] = i;
    for (int k = 1; k < LOG; ++k) {
        for (int i = 1; i <= N; ++i) {
            if (i + (1 << k) - 1 > N) continue;
            int x = i + (1 << (k - 1));
            if (A[m[i][k - 1]] < A[m[x][k - 1]])
                m[i][k] = m[i][k - 1];
            else
                m[i][k] = m[x][k - 1];
        }
    }
}

int main() {
    freopen("rmq_data.txt", "r", stdin);

    // Take input
    scanf("%d", &N);
    printf("N = %d\n", N);
    for (int i = 1; i <= N; ++i) scanf("%d", A + i);
    build();
    // Take queries
    scanf("%d", &Q);
    while (Q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        // return the index of the  minimum in range [l, r]
        printf("%d\n", query(l, r));
    }
}
