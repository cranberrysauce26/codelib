#ifndef DIOPHANTINE_H
#define DIOPHANTINE_H

#include <cassert>
#include "gcd.cpp"

// Returns unique x such that ax = 1 mod m, or -1 if no x exists
long long inverse(long long a, long long m) {
    long long x, y;
    long long g = egcd(a, m, x, y);
    if (g != 1LL) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Returns unique x mod m such that a*x = b (mod m), assuming a != 0, or -1 if no such x exists
long long linear_modulo_diophantine(long long a, long long b, long long m) {
    assert(a != 0);
    long long x, y;
    long long g = egcd(a, m, x, y);
    if (b % g != 0) return -1;
    x *= b / g;
    x %= m;
    if (x < 0) x += m;
    return x;
}
#endif