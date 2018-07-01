#include <bits/stdc++.h>
#define szof(v) ((int)(v).size())
using namespace std;
using ll = long long;

namespace FFT {
using base = complex<double>;
bool init = false;
const int LEN = 1 << 18;  // max length, power of 2
const double PI = atan(1) * 4;
base PW[LEN];  // LEN-th roots of -1
void initFFT() {
    assert((LEN & (LEN - 1)) == 0);
    double angle = 2 * PI / LEN;
    for (int i = 0; i < LEN; ++i) {
        double ca = angle * i;
        PW[i] = base(cos(ca), sin(ca));
    }
    init = true;
}
void fft(vector<base>& a, bool invert) {
    if (!init) initFFT();
    int lg = 0;
    while ((1 << lg) < szof(a)) lg++;
    for (int i = 0; i < szof(a); ++i) {
        int x = 0;
        for (int j = 0; j < lg; ++j) x |= ((i >> j) & 1) << (lg - j - 1);
        if (i < x) swap(a[i], a[x]);
    }
    for (int len = 2; len <= szof(a); len *= 2) {
        int diff = LEN / len;
        if (invert) diff = LEN - diff;
        for (int i = 0; i < szof(a); i += len) {
            int pos = 0;
            for (int j = 0; j < len / 2; ++j) {
                base v = a[i + j];
                base u = a[i + j + len / 2] * PW[pos];
                a[i + j] = v + u;
                a[i + j + len / 2] = v - u;
                pos += diff;
                if (pos >= LEN) pos -= LEN;
            }
        }
    }
    if (invert)
        for (int i = 0; i < szof(a); ++i) a[i] /= szof(a);
}

/**
 * A vector v[0], v[1], ..., v[k-1] represents the polynomial:
 * v[0] * x^(k-1) + v[1] * x^(k-2) + ... + v[k-2] * x + v[k-1].
 * So the first element is the one with the highest degree and the last element
 * is the constant.
 */
vector<ll> mult(vector<int> A, vector<int> B) {
    int l = 1;
    while (l <= max(szof(A), szof(B))) l *= 2;
    l *= 2;
    vector<base> AA(l), BB(l);
    for (int i = 0; i < szof(A); ++i) AA[i] = A[i];
    for (int i = 0; i < szof(B); ++i) BB[i] = B[i];
    fft(AA, 0);
    fft(BB, 0);
    for (int i = 0; i < l; ++i) AA[i] *= BB[i];
    fft(AA, 1);
    vector<ll> res(l);
    for (int i = 0; i < l; ++i) res[i] = (ll)(AA[i].real() + 0.5);
    return res;
}

}  // namespace FFT

int main() {
    vector<int> A = {1, 2, 3};
    vector<int> B = {3, 5};
    auto C = FFT::mult(A, B);
    for (ll x : C) {
        printf("%lld ", x);
    }
}