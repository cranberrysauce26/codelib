#include <vector>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<ll, int> range;

// Decomposes [1, N)!!!!!!
vector<range> decompose(long long N) {
    vector<range> res;
    int exponent = 0;
    ll pwr = 1;
    // stage 1
    while (N/pwr >= 10LL) {
        for (int d = 1; d <= 9; d++) 
            res.push_back({d, exponent});
        
        pwr *= 10; exponent++;
    }
    // stage 2
    ll l = pwr;
    ll p = 1;
    while (l < N) {
        if (l + pwr <= N) {
            res.push_back({p, exponent});
            l += pwr;
            p++;
        } else {
            pwr /= 10; --exponent;
            p *= 10;
        }
    }
    return res;
}


// Decomposes [A, B]. Slower
vector<range> decompose(ll A, ll B) {
    vector<range> v;
    int exp=0;
    ll pow = 1LL, x = A;
    while (true) {
        if (x % (10LL * pow) == 0) ++exp, pow *= 10LL;
        if (x + pow > B) break;
        v.push_back({x, exp});
        x += pow;
    }

    while (x <= B) {
        while (x % pow != 0) --exp, pow /= 10LL;
        while (x + pow > B + 1) --exp, pow /= 10LL;
        v.push_back({x, exp});
        x += pow;
    }
    return v;
}