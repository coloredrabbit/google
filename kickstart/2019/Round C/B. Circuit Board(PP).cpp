#include<cstdio>
#include<cmath>
#include<vector>
#include<map>
#include<cstring>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_R = 301;
int main() {
	int tc, T, R, C, K, V, w, left[MAX_R][MAX_R], l, i, j, k, ans;
	map<int, int> pos;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		ans = 0;
		scanf("%d%d%d", &R, &C, &K);
		for (i = 0; i < R; i++) {
			l = -1;
			pos.clear();
			for (j = 0; j < C; j++) {
				scanf("%d", &V);
				while (!pos.empty() && V - pos.begin()->first > K) {
					l = max(l, pos.begin()->second);
					pos.erase(pos.begin());
				}
				while (!pos.empty() && pos.rbegin()->first - V > K) {
					l = max(l, pos.rbegin()->second);
					pos.erase(pos.rbegin()->first);
				}
				pos[V] = j;
				left[i][j] = l + 1;
				w = C;
				for (k = i; k >= 0; k--) {
					w = min(w, j - left[k][j] + 1);
					ans = max(ans, w * (i - k + 1));
				}
			}
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}