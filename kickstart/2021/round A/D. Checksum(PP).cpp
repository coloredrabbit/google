#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX_N = 500;
int p[MAX_N * 2];
int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }
void merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return;
	p[u] = v;
}
int main() {
	int T, tc, N, i, j, A[MAX_N][MAX_N], B[MAX_N][MAX_N], w, y, x, ans, R, C;
	vector<pair<int, pair<int, int>>> pos;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		ans = 0;
		pos.resize(N * N);
		for (i = 0; i < N; i++) for (j = 0; j < N; j++) scanf("%d", &A[i][j]);
		for (i = 0; i < N; i++) {
			p[i] = i;
			p[i + N] = i + N;
			for (j = 0; j < N; j++) {
				scanf("%d", &B[i][j]);
				if (A[i][j] != -1) B[i][j] = 0;

				pos[i * N + j] = { -B[i][j], {i, j} };
			}
		}
		for (i = 0; i < N; i++) scanf("%d", &R);
		for (i = 0; i < N; i++) scanf("%d", &C);
		sort(pos.begin(), pos.end());

		for (i = 0; i < N * N; i++) {
			w = pos[i].first;
			y = pos[i].second.first, x = pos[i].second.second + N;
			y = find(y), x = find(x);
			if (y != x)
				merge(y, x);
			else ans += -w;
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}