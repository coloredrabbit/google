#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
using ll = long long;
const int MAX_N = 1e5 + 5;
ll dp[2][20];
ll rec(int t, int p, string& s) {
	if (p == s.length()) return 1;
	ll& ret = dp[t][p];
	if (ret != -1) return ret;
	ret = 0;
	int i, st, c = t ? s[p] - '0' : 9;
	st = !(p % 2);
	if (!st && !p) st = 2;
	for (i = st; i <= c; i += 2)
		ret += rec(t && i == c, p + 1, s);
	return ret;
}
ll gv(string& x) {
	ll ret = 0;
	memset(dp, -1, sizeof dp);
	ret = rec(1, 0, x);
	string nines;
	while (nines.length() + 1 < x.length()) {
		nines.push_back('9');
		memset(dp, -1, sizeof dp);
		ret += rec(1, 0, nines);
	}
	return ret;
}
int main() {
	int T, tc, i;
	string R, l;
	ll ans = 0, L;
	cin >> T;
	for (tc = 1; tc <= T; tc++) {
		cin >> L >> R;
		L--;
		l.clear();
		if (!L) l.push_back('0');
		i = 0;
		while (L) {
			l.push_back(L % 10 + '0');
			L /= 10;
		}
		reverse(l.begin(), l.end());
		ans = gv(R) - gv(l);
		printf("Case #%d: %lld\n", tc, ans);
	}
	return 0;
}