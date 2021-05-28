#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cstring>
#include<cmath>
using ll = long long;
const int MAX_N = 1e5 + 2, MOD = 1e9 + 7;
int main() {
	int tc, T, N, ans;
	ll G, l, r, K, t;
	scanf("%d\n", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%lld", &G);
		ans = 0;
		N = 1;
		while(1) {
			t = G - N * (N - 1LL) / 2;
			if (t <= 0) break;
			if (t % N == 0)
				ans++;
			N++;
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}