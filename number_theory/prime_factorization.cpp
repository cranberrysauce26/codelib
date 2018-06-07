#include <vector>
#include  <cstdio>
using namespace std;
typedef pair<int,int> ii;

vector<ii> prime_factorize(int n) {
	vector<ii> ans;
	for (int f = 2; f*f <= n; ++f) {
		int e = 0;
		while (n%f==0) {
			n/=f;
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

int main() {
	auto ans = prime_factorize(215);
	for (auto x : ans) {
		printf("%d^%d ", x.first, x.second);
	}
	printf("\n");
}