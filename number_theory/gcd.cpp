#ifndef GCD_H
#define GCD_H
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Status: Tested
// Returns gcd and computes x and y by reference so that ax + by = gcd(a, b)
long long egcd(long long a, long long b, long long& x, long long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    auto d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
#endif