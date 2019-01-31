#ifndef POWMOD_H
#define POWMOD_H
long long powmod(long long a, long long e, long long mod) {
    a %= mod;
    if (a < 0) a += mod;
    long long res = 1;
    while (e) {
        if (e & 1LL) res = res * a % mod;
        a = a * a % mod;
        e /= 2;
    }
    return res;
}
#endif