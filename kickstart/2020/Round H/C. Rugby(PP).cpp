#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
using ll = long long;
const int MAX_N = 1e5 + 5;
int x[MAX_N];
ll gv(int N, int xbase) {
	ll cost = 0;
	for (int i = 0; i < N; i++)
		cost += abs(xbase + i - x[i]);
	return cost;
}
int main() {
	int T, tc, N, i, y[MAX_N], xL, xR;
	double l, r, llr, lrr;
	ll ans, costx, costy, costllr, costlrr;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		for (i = 0; i < N; i++) scanf("%d%d", &x[i], &y[i]);
		sort(x, x + N); sort(y, y + N);
		for (costy = i = 0; i < N; i++) costy += abs(y[N / 2] - y[i]);
		l = -2e9, r = 2e9;
		while (r - l >= 1e-2) {
			llr = (2 * l + r) / 3, lrr = (l + 2 * r) / 3;
			costllr = gv(N, llr);
			costlrr = gv(N, lrr);
			if (costllr < costlrr) r = lrr;
			else l = llr;
		}

		ans = 1e18;
		for (i = -10; i <= 10; i++)
			ans = min(ans, gv(N, l + i) + costy);
		printf("Case #%d: %lld\n", tc, ans);
	}
	return 0;
}