#include <cstdio>
#include <algorithm> // for std::min
#define MAXN 100005
#define INF 1000000007
using namespace std;
int N, Q, t[MAXN];

// builds the segment tree
// IMPORTANT!!!!!! Set t[N+0]...t[N+(N-1)]!!!!
// IMPORTANT!!!!!! Zero indexed!
// IMPORTANT!!!!!! Currently is min, not max
void build() {
    for (int i = N-1; i > 0; --i) t[i] = min(t[i<<1], t[i<<1|1]);
}

// sets element x to v, zero indexed.
void update(int x, int v) {
    for (t[x+=N]=v; x>1; x >>= 1) t[x>>1] = min(t[x], t[x^1]);
}

// returns the minimum in the range [l, r), zero indexed.
int query(int l, int r) {
    int ans = INF;
    for (l+=N, r+=N; l < r; l >>= 1, r >>= 1) {
        if (l&1) ans = min(ans, t[l++]);
        if (r&1) ans = min(ans, t[--r]);
    } 
    return ans;
}

int main() {
    freopen("data.txt", "r", stdin);
    scanf("%d%d", &N, &Q);
    for (int i = 0; i < N; ++i) scanf("%d", t+N+i);
    build();
    while (Q--) {
        char cmd; int a, b;
        scanf(" %c %d %d", &cmd, &a, &b);
        if (cmd=='C') update(a-1, b);
        else if (cmd=='M') printf("%d\n", query(a-1, b));
        else printf("Invalid command\n");
    }
}