#include<cstdio>
#include<set>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_R = 251;
int main() {
	char b[MAX_R][MAX_R];
	int tc, T, i, j, dist[MAX_R][MAX_R], R, C, dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 }, l, r, mid, mainD, antiD, mainD_min, mainD_max, antiD_min, antiD_max, valid;
	queue<pair<int, int>> q;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d\n", &R, &C);
		memset(dist, -1, sizeof dist);
		for (i = 0; i < R; i++) {
			scanf("%s", b[i]);
			for (j = 0; j < C; j++) if (b[i][j] == '1') {
				dist[i][j] = 0;
				q.push({ i, j });
			}
		}
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			for (i = 0; i < 4; i++) {
				int ty = u.first + dy[i], tx = u.second + dx[i];
				if (0 <= ty && ty < R && 0 <= tx && tx < C && dist[ty][tx] == -1) {
					dist[ty][tx] = dist[u.first][u.second] + 1;
					q.push({ ty, tx });
				}
			}
		}
		l = 0, r = R + C - 1;
		while (l <= r) {
			mid = (l + r) / 2;
			mainD_min = antiD_min = 1e9;
			mainD_max = antiD_max = -1e9;
			for (i = 0; i < R; i++) for (j = 0; j < C; j++) if (mid < dist[i][j]) {
				mainD = i - j, antiD = i + j;
				mainD_min = min(mainD_min, mainD);
				mainD_max = max(mainD_max, mainD);
				antiD_min = min(antiD_min, antiD);
				antiD_max = max(antiD_max, antiD);
			}
			valid = 1;
			if (mainD_min <= mainD_max) {
				valid = 0;
				// find candidate center
				for (i = 0; !valid && i < R; i++) for (j = 0; j < C; j++) {
					mainD = i - j, antiD = i + j;
					if (max({ mainD_max - mainD, mainD - mainD_min, antiD_max - antiD, antiD - antiD_min }) <= mid) {
						valid = 1;
						break;
					}
				}
			}
			if (valid) r = mid - 1;
			else l = mid + 1;
		}

		printf("Case #%d: %d\n", tc, l);
	}
	return 0;
}