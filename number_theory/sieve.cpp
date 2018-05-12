const int MAXN = 100005;
int prime[MAXN], N;
void sieve() {
	for (int i = 2; i <= N; ++i) prime[i] = true;
	for (int x = 2; x*x <= N; ++x) 
		if (prime[x]) 
			for (int y = x*x; y <= N; y += x) prime[y] = false;
}