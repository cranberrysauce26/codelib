/*
	Usage of eertree:
		s is a char-by-char hashed string. e.g., hash(c) = c-'a'
		nn is the number of nodes
		nc is the number of characters added
		suffx is the id of the node representing the long suffix palindrome 
		len[u] is the length of palindrome for node u
		sufflink[u] is the id of the node of the largest proper palindromic suffix of u
		occ[u] is the number of occurences of paindrome u AFTER CALLING maxoccv()!!
		ch[u][c] is the destination node of edge from u to character c, -1 if it does not exist
*/
#include <cstring>
#include <cstdio>
#include <algorithm>
const int MAXSTR = 3e5+5, ALPHA_SIZE = 30;
int s[MAXSTR], len[MAXSTR], sufflink[MAXSTR], ch[MAXSTR][ALPHA_SIZE], occ[MAXSTR];
int nn = 2, suffx = 0, nc = 0; 
void init() {
	memset(ch, -1, sizeof ch);
	memset(occ, 0, sizeof occ);
	memset(s, 0, sizeof s);
	memset(len, 0, sizeof len);
	memset(sufflink, 0, sizeof sufflink);
	len[0] = -1;
	sufflink[0] = 0;
	len[1] = 0;
	sufflink[1] = 0;
	nn = 2;
	suffx = 0;
	nc = 0;
}
int getlink(int u) {
	while (u) {
		if (nc-len[u]-2 >= 0 && s[nc-len[u]-2] == s[nc-1]) break;
		u = sufflink[u];
	}
	return u;
}
void addchar(int c) {
	s[nc++] = c;
	suffx = getlink(suffx);
	if (ch[suffx][c] == -1) {
		len[nn] = len[suffx]+2;
		ch[suffx][c] = nn;
		sufflink[nn] = len[nn] != 1 ? ch[getlink(sufflink[suffx])][c] : 1;
		++nn;
	}
	suffx = ch[suffx][c];
	++occ[suffx];
}
long long maxoccv() {
	long long ans = 0;
	for (int i = nn-1; i >= 2; --i) {
		occ[sufflink[i]] += occ[i];
		ans = std::max(ans, 1LL * occ[i] * len[i]);
	}
	return ans;
}
int main() {
	init();
	char in;
	while ((in=getchar()) >= 'a') addchar(in-'a');
	printf("%lld\n", maxoccv());
}