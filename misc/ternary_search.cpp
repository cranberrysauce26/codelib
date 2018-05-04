#include <cassert>
#include <cstdio>

/**
 * Usage: returns the maximum in [l, r] inclusively using l ternary search.
 * It requires that [l, r] is unimodal.
 * So it STRICTLY increases to a maximum, then it may level off, then it STRICTLY decreases to the end. It must increase AND decrease.
 */	
template <typename T>
T* ternary_search_maximum(T* l, T* r) {
	assert(l <= r);
	T *m1, *m2;
	while (l < r) {
		m1 = l + (r-l)/3;
		m2 = r - (r-l)/3;
		if (*m1 >= *m2) r = m2-1;
		else l = m1+1; 
	}
	assert(l==r);
	return l; // or r
}

/**
 * Usage: returns the minimum in [l, r] inclusively using l ternary search.
 * It requires that [l, r] is unimodal.
 * So it STRICTLY decreases to a maximum, then it may level off, then it STRICTLY increases to the end. It must decrease AND increase.
 */	
template <typename T>
T* ternary_search_minimum(T* l, T* r) {
	assert(l <= r);
	T *m1, *m2;
	while (l < r) {
		m1 = l + (r-l)/3;
		m2 = r- (r-l)/3;
		if (*m1 <= *m2) r = m2-1;
		else l = m1+1;
	}
	return l;
}

template <typename T>
int ternary_search_maximum(int l, int r, T (*f)(int)) {
	assert(l <= r);
	int m1, m2;
	while (l < r) {
		m1 = l + (r-l)/3;
		m2 = r- (r-l)/3;
		if (f(m1) <= f(m2)) r = m2-1;
		else l = m1+1;
	}
	assert(l==r);
	return l;
}

template <typename T>
int ternary_search_minimum(int l, int r, T (*f)(int)) {
	assert(l <= r);
	int m1, m2;
	while (l < r) {
		m1 = l + (r-l)/3;
		m2 = r- (r-l)/3;
		if (f(m1) >= f(m2)) r = m2-1;
		else l = m1+1;
	}
	assert(l==r);
	return l;
}

int parabola(int x) {
	return (x-3)*(x-3);	
}

long long parabola2(int x) {
	return -1LL*(x-4)*(x-4);
}

int main() {
	int x[6] = {7, 3, 3, 2, 2, 9};
	int* minx = ternary_search_minimum(x, x+4);
	printf("%d\n", *minx);
	int c = ternary_search_maximum(-10, 10, parabola);
	printf("%d\n", c);
	int d = ternary_search_minimum(-40, 100, parabola2);
	printf("%d\n", d);
}