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
const int MAX_N = 5e4;
int main() {
	char name[21];
	int T, tc, N, Q, i, j, dist[26], ans, X[MAX_N], A, B, _union[26];
	queue<int> q;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d\n", &N, &Q);
		memset(_union, 0, sizeof _union);
		for (i = 0; i < N; i++) {
			scanf("%s", name);
			for (X[i] = j = 0; name[j]; j++)
				X[i] |= (1 << (name[j] - 'A'));
			for (j = 0; name[j]; j++)
				_union[name[j] - 'A'] |= X[i];
		}
		printf("Case #%d: ", tc);
		while (Q--) {
			scanf("%d%d", &A, &B);
			A--, B--;
			memset(dist, -1, sizeof dist);
			for (i = 0; i < 26; i++) if (X[A] & (1 << i)) {
				q.push(i);
				dist[i] = 0;
			}
			while (!q.empty()) {
				int u = q.front(); q.pop();
				for (i = 0; i < 26; i++) if ((_union[u] & (1 << i)) && dist[i] == -1) {
					dist[i] = dist[u] + 1;
					q.push(i);
				}
			}
			ans = 1e9;
			for (i = 0; i < 26; i++) if (dist[i] != -1 && (X[B] & (1 << i)))
				ans = min(ans, dist[i] + 2);
			printf("%d ", ans >= 1e9 ? -1 : ans);
		}
		puts("");
	}
	return 0;
}