#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
inline void clampmod(ll &a, ll mod = MOD) {
    a %= mod;
    if (a < 0) a += mod;
}

// calculates (a*b) modulo mod safely
ll mulmod(ll a, ll b, ll mod = MOD) {
    clampmod(a, mod);
    clampmod(b, mod);

    ll res = 0;
    while (b != 0) {
        if (b & 1LL) {
            res = (res + a) % mod;
        }
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}
// x^e mod mod
ll powmod(ll x, ll e, ll mod = MOD) {
    if (e == 0) {
        return 1LL;
    }
    ll h = powmod(x, e / 2, mod);
    if (e % 2 == 0) {
        return mulmod(h, h, mod);
    } else {
        return mulmod(x, mulmod(h, h, mod), mod);
    }
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

// returns the inverse of a mod m or -1 if it doesn't exist
// the code is tested
ll modinverse(ll a, ll m = MOD) {
    clampmod(a, m);
    ll bm = 1, ba = 0, br = m;
    ll cm = 0, ca = 1, cr = a;
    ll tmpm, tmpa, tmpr, q;
    while (cr != 0) {
        q = br / cr;
        tmpm = bm - cm * q;
        tmpa = ba - ca * q;
        tmpr = br - cr * q;
        bm = cm, ba = ca, br = cr;
        cm = tmpm, ca = tmpa, cr = tmpr;
    }
    if (br != 1) return -1;
    ba = ((ba % m) + m) % m;
    assert((ba * a) % m == 1LL);
    return ba;
}

// There is a unique solution module the product of each modulo
// so if the modulos are m1, m2, ..., mk, then there is a solution mod M =
// m1*m2*...*mk IMPORTANT CONDITION: M DOES NOT OVERFLOW ON LONG LONG eq is a
// vector of pairs (a, mod) where x = a (mod mod) STATUS: UNTESTED
ll chinese(vector<pair<ll, ll>> &eq) {
    assert(!eq.empty());
    ll ans = 0, M = 1LL;
    for (auto &p : eq) {
        M *= p.second;
        clampmod(p.first, p.second);
    }
    for (auto p : eq) {
        ll y = M / p.second;
        ll z = modinverse(y, p.second);
        ans += mulmod(p.first, mulmod(y, z, M), M);
        ans %= M;
    }
    return ans;
}

// returns the unique x module (m1*m2) such that
// x = a1 (mod m1)
// x = a2 (mod m2)
// IMPORTANT!!!! Requires gcd(m1, m2) = 1
// tested
ll chinese2(ll a1, ll m1, ll a2, ll m2) {
    clampmod(a1, m1);
    clampmod(a2, m2);
    ll z1 = modinverse(m2, m1);
    ll z2 = modinverse(m1, m2);
    const ll mod = m1 * m2;

    ll ans1 = mulmod(a1, mulmod(m2, z1, mod), mod);
    ll ans2 = mulmod(a2, mulmod(m1, z2, mod), mod);

    ll ans = (ans1 + ans2) % mod;
    assert(ans % m1 == a1 && ans % m2 == a2);
    return ans;
}

// same as chinese2 except m1 and m2 are not necessarily coprime
// if a solution exists, it is unique module lcm(m1, m2)
// the function returns it
// if no solution exists, it returns -1
// status: TESTED
ll chinese2_not_coprime(ll a1, ll m1, ll a2, ll m2) {
    clampmod(a1, m1);
    clampmod(a2, m2);
    ll modgcd = gcd(m1, m2);
    if (modgcd == 1LL) {
        ll ans = chinese2(a1, m1, a2, m2);
        assert(ans % m1 == a1 && ans % m2 == a2);
        return ans;
    } else {
        if (a1 % modgcd != a2 % modgcd) {
            return -1LL;
        }

        ll n1 = m1, n2 = m2;
        if (gcd(m1 / modgcd, m2) == 1LL) {
            n1 /= modgcd;
        } else if (gcd(m1, m2 / modgcd) == 1LL) {
            n2 /= modgcd;
        } else {
            // THIS SHOULD NEVER HAPPEN!!
            assert(false);
        }

        ll ans = chinese2(a1, n1, a2, n2);
        assert(ans % m1 == a1 && ans % m2 == a2);
        return ans;
    }
}

/**
 * Returns whether the fraction p/q is representable with a finite
 * number of digits after the decimal point in base b (i.e., no cycles after the
 * decimal) See http://codeforces.com/contest/983/problem/A
 *
 * Algorithm:
 * It is finite if and only if the set of primes dividing q (after
 * simplification with p) is a subset of the set of primes dividing b.
 */
bool is_fraction_finite(ll p, ll q, ll b) {
    p %= q;
    ll d = gcd(p, q);
    p /= d;
    q /= d;
    d = gcd(q, b);
    while (d != 1) {
        q /= d;
        d = gcd(q, d);
    }
    return q == 1;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("gcd(%d, %d)==%d\n", a, b, gcd(a, b));
    return 0;
}