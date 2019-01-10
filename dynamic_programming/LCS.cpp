#include <bits/stdc++.h>
using namespace std;

/**
 * Status: Tested
 * Longest common substring
 * O(s.size() * t.size())
 */
int LCS(string s, string t) {
    vector<vector<int>> dp(s.size(), vector<int>(t.size(), 0));
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < t.size(); ++j) {
            if (s[i] == t[j]) {
                if (i && j)
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = 1;
            } else {
                if (i) dp[i][j] = dp[i - 1][j];
                if (j) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
    }
    return dp.back().back();
    // To reconstruct a possible LCS
    int n = s.size() - 1, m = t.size() - 1;
    string lcs;
    while (n >= 0 && m >= 0) {
        if (s[n] == t[m]) {
            lcs += s[n];
            --n, --m;
        } else if (n && dp[n][m] == dp[n - 1][m]) {
            --n;
        } else {
            --m;
        }
    }
    reverse(lcs.begin(), lcs.end());
    cout << lcs << "\n";
}