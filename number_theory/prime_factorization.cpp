#include <bitset>
#include <cstdio>
#include <vector>
using namespace std;
typedef pair<int, int> ii;
typedef long long ll;

namespace way1 {

/**
 * Simple O(sqrt(n)) factorization no preprocessing
 * use for relatively small n
 */

vector<ii> factorize(int n) {
    vector<ii> ans;
    for (int f = 2; f * f <= n; ++f) {
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

void factorize(ll k, vector<ll> &primes) {
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

namespace way3 {
/**
 * For prime factorizing numbers up to 10^7 in log N
 */
const int MAX_NUM = (int)1e7;
int sp[MAX_NUM];
void sieve() {
    for (int i = 2; i < MAX_NUM; ++i) {
        sp[i] = i;
    }
    for (int i = 2; i * i < MAX_NUM; ++i) {
        if (sp[i] == i) {
            for (int j = i * i; j < MAX_NUM; j += i) {
                sp[j] = i;
            }
        }
    }
}

vector<ii> factorize(int n) {
    vector<ii> f;
    while (n != 1) {
        f.push_back({sp[n], 0});
        while (n % sp[n] == 0) {
            ++f.back().second;
        }
    }
	return f;
}
}  // namespace way3

int main() {
    auto ans = way1::factorize(215);
    for (auto x : ans) {
        printf("%d^%d ", x.first, x.second);
    }
    printf("\n");
}