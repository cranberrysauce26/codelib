#include <bits/stdc++.h>
struct node;
using pnode = node*;

struct node {
    int s;
    pnode ch[2];
};

const int HIGHEST_BIT = 30;

// Add x given that node u is at level b
// The root is at level 0
// The leaves are at level -1
void add(pnode u, int x, int b) {
    assert(b <= HIGHEST_BIT);
    ++u->s;
    if (b >= 0) {
        int c = (x >> b) & 1;
        if (!u->ch[c]) u->ch[c] = new node();
        add(u->ch[c], x, b - 1);
    }
}

pnode search(pnode u, int x, int b) {
    if (b == -1) return u;
    int c = (x >> b) & 1;
    if (u->ch[c]) return search(u->ch[c], x, b - 1);
    return NULL;
}

int main() {
    pnode root = new node();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        add(root, a, HIGHEST_BIT);
    }
}
