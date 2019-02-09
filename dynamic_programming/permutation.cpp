#include <bits/stdc++.h>
using namespace std;

/**
 * Status: Tested
 * Complexity: n^2
 * 
 * Counts the number of permutations of {1, 2, ..., n} with a given relative order modulo mod.
 * The input is a string "<>><<>><<" of length n-1 indicating the order
 * For example, the permutation [3, 1, 5, 2, 4] corresponds to "><><"
 */
int count_permutations(string s, const int mod = 1e9 + 7) {
    int n = s.size() + 1;
    auto dp = vector<vector<int>>(2);
    dp[0] = {1};
    for (int i = 1; i < n; ++i) {
        auto& cur = dp[i & 1];
        const auto& pre = dp[(i - 1) & 1];
        cur.resize(i + 1);
        if (s[i - 1] == '>') {
            cur[i] = 0;
            for (int j = i - 1; j >= 0; --j) cur[j] = (cur[j + 1] + pre[j]) % mod;
        } else if (s[i - 1] == '<') {
            cur[0] = 0;
            for (int j = 1; j <= i; ++j) cur[j] = (cur[j - 1] + pre[j - 1]) % mod;
        } else {
            assert(false);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans = (ans + dp[(n - 1) & 1][i]) % mod;
    return ans;
}

int main() {
    assert(count_permutations("<") == 1);
    assert(count_permutations("<>") == 2);
}