#include <bits/stdc++.h>
using namespace std;

/**
 * Status: Tested
 * Given n items as (weight, value) pairs and backpack that can hold a total weight w,
 * What is the maximum total value you can have?
 * 
 * Constraints: n <= 100, w <= 1e5, v <= 1e9
 * Time complexity: O(w*n)
 * Space complexity: O(w+n)
 */
long long knapsack(int w, vector<pair<int, long long>> items) {
    vector<long long> dp(w + 1, 0);
    for (auto item : items)
        for (int k = w; k >= item.first; --k)
            dp[k] = max(dp[k], item.second + dp[k - item.first]);
    return dp[w];
}