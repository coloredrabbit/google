#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
using ll = long long;
const int MAX_N = 1e6, MAX_K = 1e4, MOD = 1e9 + 7;
ll _pow(int a, int n) {
	if (n <= 1) return n ? a : 1;
	ll h = _pow(a, n >> 1);
	return (h * h % MOD) * (n % 2 ? a : 1) % MOD;
}
int main() {
	int T, tc, N, x[MAX_N], y[MAX_N], K, A[MAX_K], C, D, E1, E2, F, i, j, ans;
	ll frequency, score;
	/*
	frequency[i] = N - i
	score[i] = K + 2^k-2 + ... + (i+1) ^ (k - 2) / i
	*/
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d%d%d%d%d%d%d%d", &N, &K, &x[0], &y[0], &C, &D, &E1, &E2, &F);
		ans = score = 0;
		for (i = 0; i < N; i++) {
			if (i) {
				x[i] = ((ll)C * x[i - 1] + (ll)D * y[i - 1] + E1) % F;
				y[i] = ((ll)D * x[i - 1] + (ll)C * y[i - 1] + E2) % F;
			}
			A[i] = (x[i] + y[i]) % F;

			score = (score + (i ? ((_pow(i + 1, K + 1) - (i + 1) + MOD) % MOD *  _pow(i, MOD - 2) % MOD) : K)) % MOD;
			frequency = N - i;
			ans = (ans + (frequency * score % MOD) * A[i]) % MOD;
		}

		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}
