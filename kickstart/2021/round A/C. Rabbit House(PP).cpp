#include<cstdio>
#include<set>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 305;
struct _pos { int y, x; };
bool operator<(const _pos& a, const _pos& b) {
    return a.y == b.y ? a.y < b.y : a.x < b.x;
}
int main() {
    int tc, T, R, C, i, j, b[MAX_N][MAX_N], qsize, dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 }, y, x;
    bool hasQ[MAX_N][MAX_N] = {};
    queue<pair<int, _pos>> pq;
    ll ans;
    scanf("%d", &T);
    for (tc = 1; tc <= T; tc++) {
        scanf("%d%d", &R, &C);
        for (i = 1; i <= R; i++) for (j = 1; j <= C; j++) {
            scanf("%d", &b[i][j]);
            pq.push({ b[i][j], {i, j} });
            hasQ[i][j] = 1;
        }
        ans = 0;
        while (!pq.empty()) {
            auto u = pq.front(); pq.pop();
            y = u.second.y, x = u.second.x;
            hasQ[y][x] = 0;

            for (i = 0; i < 4; i++) {
                int ty = y + dy[i], tx = x + dx[i];
                if (ty && ty <= R && tx && tx <= C && b[y][x] - 1 > b[ty][tx]) {
                    ans += max(0, b[y][x] - 1 - b[ty][tx]);
                    b[ty][tx] = b[y][x] - 1;
                    if (!hasQ[ty][tx]) {
                        pq.push({ b[ty][tx], { ty,tx } });
                        hasQ[ty][tx] = 1;
                    }
                }
            }
        }
        printf("Case #%d: %lld\n", tc, ans);
    }
    return 0;
}