#define LOCAL
#define CPP_IO

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
ostream& operator<<(ostream& os, set<T, V> v) {
    os << "{ ";
    for (auto e : v) os << e << " ";
    return os << "}";
}

template <typename T, typename V, typename S>
ostream& operator<<(ostream& os, map<T, V, S> v) {
    os << "{ ";
    for (auto e : v) os << e << " ";
    return os << "}";
}

template <typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> x) {
    return os << "( " << x.first << ", " << x.second << " )";
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& e : v) is >> e;
    return is;
}

template <typename T, typename V>
istream& operator>>(istream& is, pair<T, V>& x) {
    return is >> x.first >> x.second;
}

template <typename T>
T divfloor(T a, T b) {
    assert(b != 0);
    if (a >= 0 && b > 0 || a <= 0 && b < 0) return a / b;
    return (a % b == 0) ? a / b : a / b - 1;
}

template <typename T>
T divceil(T a, T b) {
    assert(b != 0);
    if (a >= 0 && b > 0 || a <= 0 && b < 0) return (a % b == 0) ? a / b : a / b + 1;
    return a / b;
}

void solve();

int main() {
#ifdef LOCAL
    freopen("data.txt", "r", stdin);
#else
#ifdef CPP_IO
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#endif
#endif
    solve();
}

#pragma endregion

void solve() {
}