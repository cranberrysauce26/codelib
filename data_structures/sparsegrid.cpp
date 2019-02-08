#ifndef SPARSEGRID_H
#define SPARSEGRID_H

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/tree_policy.hpp>      // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;

/**
 * Status: Tested
 * sprasegrid stores a set (not multiset) of points (x, y) such that 1 <= x <= n, with no bounds on y.
 */
struct sparsegrid {
    using oset = tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>;
    vector<oset> b;
    // Creates an empty set supporting inserting (x, y) where 1 <= x <= n
    sparsegrid(int n)
        : b(vector<oset>(n + 1)) {
    }
    // The number of points (a, b) such that a <= x and b <= y
    int query(int x, int y) {
        int ans = 0;
        for (; x; x -= x & -x) ans += b[x].order_of_key({y + 1, numeric_limits<int>::min()});
        return ans;
    }
    // The number of points (a, b) such that xlo <= a <= xhi and ylo <= b <= yhi
    int query(int xlo, int xhi, int ylo, int yhi) {
        return query(xhi, yhi) - query(xlo - 1, yhi) - query(xhi, ylo - 1) + query(xlo - 1, ylo - 1);
    }
    // Use t = 1 to insert (x, y) and t = 2 to erase (x, y)
    void update(int x, int y, int t) {
        assert(t == 1 || t == -1);
        for (int X = x; X < b.size(); X += X & -X) {
            if (t == 1) b[X].insert({y, x});
            if (t == -1) b[X].erase({y, x});
        }
    }
};

#endif