#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cstring>
using ll = long long;
const int MAX_N = 1e5 + 2, MOD = 1e9 + 7;
int _pow(int a, int n) {
	if (n < 2) return n ? a : 1;
	int h = _pow(a, n >> 1);
	return ((ll)h * h) % MOD * (n % 2 ? a : 1) % MOD;
}
int main() {
	char s[MAX_N];
	int tc, T, N, K, ans, i, l, r, c;
	scanf("%d\n", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d\n%s", &N, &K, s);
		K += 'a';
		c = N / 2 + N % 2;
		l = 0, r = N - 1;
		ans = 0;
		while (l + 1 < r) {
			for (i = 'a'; i < K && i < s[l]; i++)
				ans = (ans + _pow(K - 'a', c - 1)) % MOD;
			l++, r--;
			c--;
		}
		for (i = 'a'; i < K && i < s[l]; i++)
			ans = (ans + 1) % MOD;
		while (r < N) {
			if (s[l] < s[r]) {
				ans = (ans + 1) % MOD;
				break;
			}
			else if (s[l] > s[r])
				break;
			l--, r++;
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}