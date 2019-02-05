#include <cassert>
#include <vector>

/**
 * Status: Tested
 * sumcounter maintains a multiset of positive integers
 * It allows you to query for the number of subsets that sum to s, modulo mod
 * Complexity: Linear in maximum sum for updates, constant for queries
 */
struct sum_counter {
    const long long mod;
    std::vector<long long> dp;
    sum_counter(int maxsum, long long mod)
        : dp(maxsum + 1, 0), mod(mod) {
        dp[0] = 1 % mod;
    }
    // O(maxsum)
    void add(int x) {
        assert(x > 0);
        for (int i = dp.size() - 1; i >= x; --i) {
            dp[i] += dp[i - x];
            if (dp[i] >= mod) dp[i] -= mod;
        }
    }
    // O(maxsum)
    void remove(int x) {
        assert(x > 0);
        for (int i = x; i < dp.size(); ++i) {
            dp[i] -= dp[i - x];
            if (dp[i] < 0) dp[i] += mod;
        }
    }
    long long query(int s) {
        return dp[s];
    }
};