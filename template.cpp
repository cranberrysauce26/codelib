#define LOCAL

#pragma region

#ifdef LOCAL
#define debug cout
#else
#define debug \
    if (0) cout
#endif

#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using ll = long long;

template <typename T>
ostream& operator<<(ostream& os, vector<T> v) {
    os << "[ ";
    for (auto e : v) os << e << " ";
    return os << "]";
}

template <typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> x) {
    return os << "{ " << x.first << ", " << x.second << " }";
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (int i = 0; i < v.size(); ++i) is >> v[i];
    return is;
}

template <typename T, typename V>
istream& operator>>(istream& is, pair<T, V>& x) {
    return is >> x.first >> x.second;
}

void solve();

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
}

#pragma endregion

void solve() {
}