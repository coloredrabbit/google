#include<cstdio>
#include<set>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 1e5 + 1;
int main() {
	char s[MAX_N];
	int tc, T, N, Q, i, j, L, R, ans, ocnt;
	bool acc[MAX_N][26] = {};
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d\n%s", &N, &Q, s);
		for (i = 0; s[i]; i++) {
			memcpy(acc[i + 1], acc[i], sizeof acc[i + 1]);
			acc[i + 1][s[i] - 'A'] ^= 1;
		}
		ans = 0;
		while (Q--) {
			scanf("%d%d", &L, &R);
			ocnt = 0;
			for (i = 0; i < 26 && ocnt < 2; i++)
				ocnt += (acc[R][i] ^ acc[L - 1][i]);
			ans += ocnt < 2;
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}