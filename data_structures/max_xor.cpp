#include <set>
#include <cassert>
/**
 * max_xor_t is a data structure that supports
 * 1. add an integer x. (I believe it works for x < 0 as well)
 * 2. query(x, mx) := the element v out of all elements added that satisfies v <= mx and maximizes v^x, or -1 if it doesn't exist.
 * Complexity: max_bits * log(s.size()) for query, log(s.size()) for add
 * NOTE: Using a trie brings complexity down to add(max_bits), query(max_bits).
 */

struct max_xor_t {
	int max_bits = 1;
	std::set<int> s;
	inline void add(int x) {
		s.insert(x);
		while ((1<<max_bits) < x) ++max_bits;
	}

	inline int query(int x, int mx) {
		auto lo = s.begin(), hi = s.upper_bound(mx);
		if (hi==s.begin()) return -1;
		--hi;
		int pre = 0; // invariant: the prefix of all elements in [lo, hi] before k, the current bit, equals pre
		auto tmp = s.begin();
		for (int k = max_bits; k >= 0 && *lo < *hi; --k){
			// printf("k = %d, *lo = %d, *hi = %d\n", k, *lo, *hi);
			if (x&(1<<k)) {
				// you want it to be zero
				// so decrease hi
				tmp = s.lower_bound(pre | (1<<k));
				if (tmp == s.begin()) {
					pre |= 1<<k;
					continue;
				}
				--tmp;
				if (*tmp < *lo) {
					pre |= 1<<k;
					continue;
				}
				if (*tmp > *hi) {
					continue;
				}
				hi = tmp;
			} else {
				// you want it to be one
				tmp = s.lower_bound(pre | (1<<k));
				if (tmp==s.end()) continue;
				if (*tmp > *hi) continue;
				lo = tmp;
				pre |= 1<<k;
			}
		}
		assert(lo==hi);
		return *lo;
	}
};