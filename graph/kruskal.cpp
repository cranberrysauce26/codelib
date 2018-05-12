#include <cstdio>
#include <vector>
#include <algorithm>
#define mp make_pair
#define MAXM 100005
using namespace std;
typedef pair<int, pair<int, int> > edge; 
vector<edge> edges;

int N, M, ds[MAXM], rnk[MAXM];

void init() {
    for (int i = 1; i <= N; ++i) ds[i] = i, rnk[i] = 0;
}

int find(int x) {
    return ds[x]==x ? x : ( ds[x]=find(ds[x]) );
}

bool merge(int x, int y) {
    int xr = find(x), yr = find(y);
    if (xr==yr) return 0;
    if (rnk[xr] > rnk[yr]) ds[yr]=xr;
    else {
        ds[xr]=yr;
        if (rnk[xr]==rnk[yr]) ++rnk[yr];
    }
    return 1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int a, b, w; scanf("%d%d%d", &a, &b, &w);
        edges.push_back(mp(w, mp(a, b)));
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < M; ++i) ds[i] = i;
    int tree = 0, i = 0, sum=0;
    while (tree < N-1 && i < M) {
        edge e = edges[i++];
        if (find(e.second.first)!=find(e.second.second)) {
            sum += e.first, ++tree;
            merge(e.second.first, e.second.second);
        }
    }
    printf("%d\n", sum);
}