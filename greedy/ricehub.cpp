#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll sum[100005];
inline ll f(int l, int r) {
	return sum[r]-sum[(l+r)/2]+sum[l-1]- sum[(l+r)/2-((r-l+1)&1)];
}
/**
 * There are R farmers in total at position X[0], X[1], ..., X[R-1].
 * They all satisfy 1 <= X[i] <= L (although L is not used at all in the algorithm so this is unimportant).
 * Transporting farmer i and his/her crop to a point at position p costs abs(p-X[i]) i.e., the distance from X[i] to p.
 * The maximum cost you can incur is B.
 * The function returns the maximum number of farmers you can bring to the ricehub over all possible positions of the ricehub
 * within the budget B.
 * It can be easily modified to also return one such maximal position.
 * 
 * Here's how the algorithm works.
 * If you place a ricehub at some point, you will get a (possibly empty) contigious sequence of farmers.
 * e.g., all farmers from i to j. Fix i and j and suppose a placement of the ricehub takes exactly the farmers [i, j].
 * Then obviously you place the ricehub in [X[i], X{j]] and so
 * the sum of the distances for i and j is just X[j]-X[i] no matter where the ricehub is placed in this interval.
 * Now let's say you have farmers i+1 and j-1. Then the ricehub should be placed in between X[i+1] and X[j-1], and so on for i+1, j-2, etc.
 * This is the greedy step. If you continue this way, you get the difference between the sum of the upper half and the 
 * sum of the lower half. (The exact function is f above, where sum is 1 indexed).
 * 
 * Finally, notice that f(l, r) is non decreasing for f and a fixed l. So a simple binary search will give you the answer.
 * 
 * Complexity: R*lg(R)
 */
int besthub(int R, int L, int *X, ll B) {
	for (int i = 1; i <= R; ++i) sum[i] = sum[i-1] + X[i-1];
	int best = 0;
	for (int i = 0; i < R; ++i) {
		int lo = i, hi = R-1;
		while (lo < hi) {
			int mid = hi-(hi-lo)/2;
			if (f(i+1,mid+1) <= B) lo = mid;
			else hi = mid-1;
		}
		best = max(best, lo-i+1);
	}
	return best;
}