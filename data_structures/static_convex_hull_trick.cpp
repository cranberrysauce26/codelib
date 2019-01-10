#include <bits/stdc++.h>
using namespace std;
using pll = pair<ll, ll>;

// Status: Tested
// Query for minimum
struct convex_hull {
    deque<pll> lines;

    // Only requires that l1.first <= l2.first <= l3.first
    bool bad(pll l1, pll l2, pll l3) {
        return (l2.second - l3.second) * (l2.first - l1.first) >= (l1.second - l2.second) * (l3.first - l2.first);
    }

    // Add y=mx+b such that m is the smallest slope of any line in the set
    void add_min_slope(ll m, ll b) {
        if (!lines.empty()) {
            assert(m <= lines.front().first);
        }
        pll cur = {m, b};
        while (lines.size() >= 2 && bad(cur, lines[0], lines[1])) {
            lines.pop_front();
        }
        lines.push_front(cur);
    }

    // Add y=mx+b such that m is the largest slope of any line in the set
    void add_max_slope(ll m, ll b) {
        if (!lines.empty()) {
            assert(m >= lines.back().first);
        }
        pll cur = {m, b};
        while (lines.size() >= 2 && bad(lines[lines.size() - 2], lines[lines.size() - 1], cur)) {
            lines.pop_back();
        }
        lines.push_back(cur);
    }

    ll query_min(ll x) {
        int lo = 0, hi = lines.size() - 1;
        while (lo < hi) {
            int mid = hi - (hi - lo) / 2;
            auto l2 = lines[mid], l1 = lines[mid - 1];
            if (l1.second - l2.second >= x * (l2.first - l1.first)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lines[lo].first * x + lines[lo].second;
    }
};