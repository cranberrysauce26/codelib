#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#define sz(v) ((int)(v).size())
typedef std::vector<double> vec;
typedef std::vector<vec> mat;

const double EPS = 1e-5;

void print_vec(const vec& v) {
	for (double x : v) std::cout << x << " ";
	std::cout << "\n";
}

void print_mat(const mat& m) {
	for (auto& v : m) print_vec(v);
	std::cout << "\n";
}

/**
 * rref takes a matrix as input and returns its reduced row echelon form.
 * A matrix is in reduced row echelon form if and only if:
 * 
 * 1. If there is a row where every entry is zero, then this row lies below any other row that contains a nonzero entry.
 * 2. The leftmost nonzero entry of a row is equal to 1.
 * 3. The leftmost nonzero entry of a row is the only nonzero entry in its column.
 * 4. Consider any two different leftmost nonzero entries, one located in row i, column j and the other in row s, column j. Then if s > i, t > j.
 * 
 * Lemma: For every matrix A, there is a unique matrix B in reduced row echelon form that is row equivalent to A.
 */
void rref(mat& A) {
	int R = sz(A), C = sz(A[0]);
	printf("R = %d, C = %d\n", R, C);
	print_mat(A);
	for (int col = 0, tr = 0; col < C; ++col) {
		// set lr to be max abs value of A[lr][col]
		int lr = tr;
		for (int r = tr+1; r < R; ++r) {
			if (std::abs(A[r][col]) > std::abs(A[lr][col])) lr = r;
		}
		if (lr < R && std::abs(A[lr][col]) > EPS) {
			std::swap(A[tr], A[lr]);
			for (int c = col+1; c < C; ++c) A[tr][c] /= A[tr][col];
			A[tr][col] = 1;
			for (int r = 0; r < R; ++r) {
				if (r != tr && std::abs(A[r][col]) > EPS) {
					for (int c = col+1; c < C; ++c) A[r][c] -= A[r][col] * A[tr][c];
					A[r][col] = 0;
				}
			}
			++tr;
		}
		print_mat(A);
	}
}
/**
 * rref_solve solves the system of linear equations represented by the augmented matrix A,
 * assuming A is in reduced row echelon form.
 * 
 * It returns 0 if there are no solutions, 1 if there is a unique solution, and 2 if there are infinite solutions.
 * If there is at least one solution, it stores the answer in x.
 * 
 * Each row in the augmented matrix represents an equation. Each column except column n represents a variable.
 * The last column represents the vector of constants y. i.e., Mx = y, where M is A with the last column removed.
 * 
 * Definition: A column is free iff it has no leading 1. F is the set of free columns.
 * Definition: A column is dependent iff it is not free. D is the set of dependent columns.
 * 
 * Definition: A matrix is consistent iff n is free. (i.e., there is no row of zeroes followed by a constant at the end)
 * 
 * Lemma: A solution exists iff the matrix is consistent.
 * Lemma: A consistent matrix has a unique solution iff F is empty. Otherwise there are infinite solutions.
 * Lemma: Index D as d[0] < d[1] < ... < d[|D|-1]. Then the following is a solution:
 * for 0 <= k < n
 * 		if (k == d[j] for some j) x[k] = A[j][n]
 * 		else x[k] = 0
 */
int rref_solve(vec& x, const mat& A) {
	int m = sz(A), n = sz(A[0])-1, ndep = 0;
	x.resize(n, 0);
	for (int r = 0, c = 0; r < m; ++r) {
		while (c <= n && abs(A[r][c]) < EPS) ++c;
		if (c < n) {
			++ndep;
			x[c] = A[r][n];
		} else if (c==n) return 0;
		else break;
	}
	if (ndep == n) return 1;
	return 2;
}

int main() {
	mat A = {
		{1, 2, -1, 1, 1},
		{0, 1, -1, -2, -1},
		{1, 3, -1, 1, 1},
		{-2, -3, 3, 1, -2},
		{1, 3, -1, 2, 1}
	};
	rref(A);
	vec x; 
	int state = rref_solve(x, A);
	std::cout << "state: " << state << "\n";
	if (state) {
		for (double v : x) std::cout << v << " ";
		std::cout << std::endl;
	}
}