/**
 * Problem: You have n blocks, each with a weight w, durability s, and value v. You wish to stack some of these
 * blocks such that the sum of the weights above each block is not more than its durability. What is the maximum
 * total value of a valid stack of blocks?
 * 
 * Constraints: n <= 1e3, w = s <= 1e4, v <= 1e9
 * 
 * Time complexity: o(nlgn + n*w)
 * Space Complexity: o(n+w)
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct block {
    int w, s;
    ll v;
    bool operator<(const block& b) const {
        return (w + s != b.w + b.s) ? (w + s < b.w + b.s) : v < b.v;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<block> b(n);
    for (int i = 0; i < n; ++i) cin >> b[i].w >> b[i].s >> b[i].v;
    sort(b.begin(), b.end());
    vector<ll> dp(2e4 + 5, 0);
    for (int i = 0; i < n; ++i) {
        // Add i
        for (int t = dp.size() - 1; t >= b[i].w; --t) {
            dp[t] = max(dp[t], b[i].v + dp[min(b[i].s, t - b[i].w)]);
        }
    }
    cout << dp.back() << "\n";
}