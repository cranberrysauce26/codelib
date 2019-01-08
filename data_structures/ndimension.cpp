#include <bits/stdc++.h>
namespace binary {
const int DIM = 20;
int n, sum[DIM];

// After this, sum[x] will be the sum of all subsets of x.
void build() {
    for (int k = 0; k < n; ++k) {
        for (int x = 0; x < (1 << n); ++x) {
            if ((x >> k) & 1) {
                sum[x] += sum[x - (1 << k)];
            }
        }
        /*
        If you want to sum supersets
        for (int x = (1 << n) - 1; x >= 0; --x) {
            if (((x >> k) & 1) == 0) {
                sum[x] += sum[x + (1 << k)];
            }
        }
        */
    }
}
}  // namespace binary

namespace general {
const int DIM = 20, MX = 1e6;
int n, d[DIM], sum[MX];
// You have a d[0] x d[1] x d[2] x ... x d[k-1] grid
// sum will hold the sum of subset
void build() {
    int delta = 1;
    for (int k = 0; k < n; ++k) {
        int dimsz = delta * d[k];
        for (int x = delta; x < MX; ++x) {
            if ((x - delta) / dimsz == x / dimsz) {
                sum[x] += sum[x - delta];
            }
        }
        /*
        If you want to sum supersets
        for (int x = MX - 1; x >= 0; --x) {
            if ((x + delta) / dimsz == x / dimsz) {
                sum[x] += sum[x + delta];
            }
        }
        */
        delta = dimsz;
    }
}

}  // namespace general
