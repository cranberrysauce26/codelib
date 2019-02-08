#include <cmath>
#include <iostream>
#include <unordered_map>
#include "diophantine.cpp"
#include "gcd.cpp"
#include "powmod.cpp"

// Status: Tested
// Computes the unique x such that g^x % mod == h where g must be a primitive root of mod
// Complexity: O(sqrt(mod))
long long discrete_logarithm(long long h, long long g, const long long mod) {
    h %= mod;
    const auto m = static_cast<int>(ceil(sqrt(mod)));
    std::unordered_map<int, int> t;
    long long e = 1;
    for (int i = 0; i < m; ++i) {
        t[static_cast<int>(e)] = i;
        e = e * g % mod;
    }
    const auto factor = powmod(g, mod - m - 1, mod);
    e = h;
    for (int i = 0; i < m; ++i) {
        auto it = t.find(static_cast<int>(e));
        if (it != t.end()) return (1LL * m * i + 1LL * it->second) % mod;
        e = e * factor % mod;
    }
    // If h = 0
    return -1LL;
}

// Finds a solution to a^x = b given a primitive root g modulo a prime p
// If no solution exists returns -1
// If all x are solutions returns -2
long long discrete_logarithm_base(long long a, long long b, long long g, long long p) {
    if (a % p == 0) return b % p == 0 ? -2 : -1;
    a = discrete_logarithm(a, g, p);
    b = discrete_logarithm(b, g, p);
    // Now a*x = b mod (p-1)
    return linear_modulo_diophantine(a, b, p - 1);
}

// Status: Tested
// Returns not necessarily unique x such that x^a = b modulo p
long long discrete_root(long long a, long long b, long long g, long long p) {
    a %= p;
    b %= p;
    if (a == 0) return b == 1 ? -2 : -1;
    b = discrete_logarithm(b, g, p);
    long long logx = linear_modulo_diophantine(a, b, p - 1);
    if (logx == -1) return -1;
    return powmod(g, logx, p);
}

// TO FIND ALL PRIMITIVE ROOTS, SEARCH ON WOLFRAM ALPHA

int main() {
    std::cout << discrete_root(2, 4, 3, 7) << "\n";
}