#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
ll count_palindromes(const vector<T> &t, const T sentinel) {
    vector<T> s(2 * t.size() + 1);
    for (int i = 0; i < t.size(); ++i) {
        s[2 * i] = sentinel;
        s[2 * i + 1] = t[i];
    }
    s[2 * t.size()] = sentinel;
    vector<int> p(s.size());
    int center = 0;
    ll ans = 0;
    for (int i = 1; i < s.size(); ++i) {
        int r = center + p[center];
        if (i < r) p[i] = min(r - i, p[2 * center - i]);
        while ((i - p[i] - 1) >= 0 && i + p[i] + 1 < s.size() && s[i - p[i] - 1] == s[i + p[i] + 1]) ++p[i];
        if (i + p[i] > r) center = i;
        if (i % 2 == 0)
            ans += 1LL * p[i] / 2;
        else
            ans += 1LL * p[i] / 2 + 1LL;
    }
    return ans;
}