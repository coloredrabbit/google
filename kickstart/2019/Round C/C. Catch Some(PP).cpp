#include<cstdio>
#include<cmath>
#include<vector>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 1001;
map<int, vector<int>> pos;
vector<int> colors;
int dp[MAX_N][MAX_N][2], P[MAX_N];
int rec(int clr, int k, int f) {
	if (!k)return 0;
	if (clr == pos.size()) return 2e9;
	int& ret = dp[clr][k][f];
	if (ret != -1) return ret;
	ret = rec(clr + 1, k, f);
	int i, P;
	for (i = 0; i < k && i < pos[colors[clr]].size(); i++) {
		P = pos[colors[clr]][i];
		ret = min(ret, rec(clr + 1, k - (i + 1), f) + 2 * P);
		if (!f)
			ret = min(ret, rec(clr + 1, k - (i + 1), 1) + P);
	}
	return ret;
}
int main() {
	int tc, T, N, K, A, idx[MAX_N], i;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		memset(idx, 0, sizeof idx);
		pos.clear(); colors.clear();

		scanf("%d%d", &N, &K);
		for (i = 0; i < N; i++) scanf("%d", &P[i]);
		for (i = 0; i < N; i++) {
			scanf("%d", &A);
			pos[A].push_back(P[i]);
			colors.push_back(A);
		}
		sort(colors.begin(), colors.end());
		unique(colors.begin(), colors.end());
		for (auto it = pos.begin(); it != pos.end(); it++)
			sort(it->second.begin(), it->second.end());

		memset(dp, -1, sizeof dp);
		printf("Case #%d: %d\n", tc, rec(0, K, 0));
	}
	return 0;
}