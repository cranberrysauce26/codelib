#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

namespace way1 {

/**
 * Simple O(sqrt(n)) factorization no preprocessing
 * use for relatively small n
 */
template <typename T>
vector<pair<T, int>> factorize(T n) {
    vector<pair<T, int>> ans;
    for (T f = 2; f * f <= n; ++f) {
        int e = 0;
        while (n % f == 0) {
            n /= f;
            ++e;
        }
        if (e) {
            ans.push_back({f, e});
        }
    }
    if (n != 1) {
        ans.push_back({n, 1});
    }
    return ans;
}
}  // namespace way1

namespace way2 {

/**
 * For prime factorizing numbers up to MAX = 10^18.
 * Let HIGH be the sqrt of MAX
 * O(HIGH*log log HIGH) preprocessing in sieve
 * O(HIGH/log(HIGH)) prime factorization
 *
 * This is better than way1 by a factor of log(HIGH) by the prime number theorem
 * This factor is significant for numbers up to MAX
 */

vector<ll> allprimes;
const ll HIGH = 31622800;
bitset<HIGH> isprime;
void sieve() {
    isprime.set();
    for (ll i = 2; i * i < HIGH; ++i) {
        if (isprime[i]) {
            for (ll j = i * i; j < HIGH; j += i) {
                isprime[j] = 0;
            }
        }
    }
    for (ll i = 2; i < HIGH; ++i) {
        if (isprime[i]) {
            allprimes.push_back(i);
        }
    }
}

void factorize(ll k, vector<ll>& primes) {
    for (ll p : allprimes) {
        if (p * p > k) {
            break;
        }
        if (k % p == 0) {
            while (k % p == 0) {
                k /= p;
            }
            primes.push_back(p);
        }
    }
    if (k != 1) {
        primes.push_back(k);
    }
}

}  // namespace way2

// Factorizes in log(n)
// for numbers up to 10^7
// Status: Tested
struct small_factorizer {
    int high;
    vector<int> sp;
    small_factorizer(int high)
        : high(high) {
        sp = vector<int>(high + 1, -1);
        for (int i = 2; i <= high; ++i) sp[i] = i;
        for (int i = 2; i * i <= high; ++i) {
            if (sp[i] == i) {
                for (int j = i * i; j <= high; j += i) {
                    if (sp[j] == j) sp[j] = i;
                }
            }
        }
    }
    vector<ii> factorize(int n) {
        assert(n > 0 && n <= high);
        vector<ii> f;
        while (sp[n] != -1) {
            int p = sp[n];
            f.push_back({p, 0});
            while (sp[n] == p) {
                ++f.back().second;
                n /= p;
            }
        }
        return f;
    }
};

// Status: Tested
vector<int> all_factors(const vector<ii>& pf) {
    vector<int> ans = {1}, newf;
    for (int i = 0; i < pf.size(); ++i) {
        int p = pf[i].first, e = pf[i].second;
        newf.clear();
        for (int old : ans) {
            for (int j = 1, x = p; j <= e; ++j, x *= p) {
                newf.push_back(old * x);
            }
        }
        for (int f : newf) {
            ans.push_back(f);
        }
    }
    return ans;
}

int main() {
    // auto ans = way1::factorize(215);
    // for (auto x : ans) {
    //     printf("%d^%d ", x.first, x.second);
    // }
    // printf("\n");
}