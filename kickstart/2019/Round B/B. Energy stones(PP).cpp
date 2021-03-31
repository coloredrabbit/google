#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_T = 1e4 + 1, MAX_N = 100;
struct _d { int s, e, l; }A[MAX_N];
bool operator<(const _d& a, const _d& b) {
	return a.s * b.l < b.s * a.l;
}
int N, dp[MAX_T][MAX_N];
int rec(int t, int p) {
	if (p >= N) return 0;
	int& ret = dp[t][p];
	if (ret != -1) return ret;
	ret = 0;
	return ret = max(rec(t, p + 1), rec(t + A[p].s, p + 1) + max(0, A[p].e - t * A[p].l));
}
int main() {
	int T, tc, i, ans;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		ans = 0;
		i = 0;
		while(N--) {
			scanf("%d%d%d", &A[i].s, &A[i].e, &A[i].l);
			if (A[i].l) i++;
			else ans += A[i].e;
		}
		N = i;
		sort(A, A + N);
		memset(dp, -1, sizeof dp);
		printf("Case #%d: %d\n", tc, ans + rec(0, 0));
	}
	return 0;
}