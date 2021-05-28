#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cstring>
#include<cmath>
using namespace std;
using ll = long long;
const int MAX_N = 61, MOD = 1e9 + 7;
char hand[] = "RSP";
int T, W, E;
double dp[MAX_N][MAX_N][MAX_N];
double rec(int x[3]) {
	int& r = x[0], & s = x[1], & p = x[2];
	int c = r + s + p;
	if (c == MAX_N - 1) return 0;
	double& ret = dp[r][s][p];
	if (ret != -1) return ret;
	ret = 0;
	int i, j, n[3];
	double P[3], exp;
	if (c) {
		P[0] = (double)s / c;
		P[1] = (double)p / c;
		P[2] = (double)r / c;
	}
	else P[0] = P[1] = P[2] = 1. / 3;

	for (i = 0; i < 3; i++) {
		exp = 0;
		for (j = 0; j < 3; j++) {
			n[j] = x[j] + (i == j);
			if (i == j) exp += P[j] * E;
			else if ((i + 1) % 3 == j)
				exp += P[j] * W;
		}
		ret = max(ret, rec(n) + exp / T);
	}
	return ret;
}
void trace(int x[3]) {
	int& r = x[0], & s = x[1], & p = x[2];
	int c = r + s + p;
	if (c == MAX_N - 1) return;
	double& ret = dp[r][s][p];
	int i, j, n[3];
	double P[3], exp;
	if (c) {
		P[0] = (double)s / c;
		P[1] = (double)p / c;
		P[2] = (double)r / c;
	}
	else P[0] = P[1] = P[2] = 1. / 3;

	for (i = 0; i < 3; i++) {
		exp = 0;
		for (j = 0; j < 3; j++) {
			n[j] = x[j] + (i == j);
			if (i == j) exp += P[j] * E;
			else if ((i + 1) % 3 == j)
				exp += P[j] * W;
		}
		if (ret == rec(n) + exp / T) {
			printf("%c", hand[i]);
			trace(n);
			break;
		}
	}
}
int main() {
	int tc, X, i, j, k, _base[3] = {};
	scanf("%d%d", &T, &X);
	for (tc = 1; tc <= T; tc++) {
		for (i = 0; i < MAX_N; i++) for (j = 0; j < MAX_N; j++) for (k = 0; k < MAX_N; k++)
			dp[i][j][k] = -1;
		scanf("%d%d", &W, &E);
		double r = rec(_base);
		printf("Case #%d: ", tc);
		trace(_base);
		puts("");
	}
	return 0;
}