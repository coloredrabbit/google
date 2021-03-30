#include<cstdio>
#include<set>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 1e3+2, MSZ = 200, FU = 0, FD = 2, FL = 1, FR = 3; // from
int gv(int a, int b) {
    int ret = 0, c;
    c = max(0, min(a / 2, b) - 1);
    ret += c;
    c = max(0, min(b / 2, a) - 1);
    ret += c;
    return ret;
}
int main() {
    int tc, T, R, C, i, j, b[MAX_N][MAX_N], ps[4][MAX_N][MAX_N], hor;
    ll ans;
    scanf("%d", &T);
    for (tc = 1; tc <= T; tc++) {
        memset(ps, 0, sizeof ps);
        scanf("%d%d", &R, &C);
        for (i = 1; i <= R; i++) for (j = 1; j <= C; j++) {
            scanf("%d", &b[i][j]);
            if (b[i][j]) {
                ps[FU][i][j] = ps[FU][i - 1][j] + b[i][j];
                ps[FL][i][j] = ps[FL][i][j - 1] + b[i][j];
            }
        }

        for (i = R; i; i--) for (j = C; j; j--) {
            if (b[i][j]) {
                ps[FD][i][j] = ps[FD][i + 1][j] + b[i][j];
                ps[FR][i][j] = ps[FR][i][j + 1] + b[i][j];
            }
        }

        ans = 0;
        for (i = 1; i <= R; i++) for (j = 1; j <= C; j++) {
            ans += gv(ps[FL][i][j], ps[FU][i][j]);
            ans += gv(ps[FU][i][j], ps[FR][i][j]);
            ans += gv(ps[FR][i][j], ps[FD][i][j]);
            ans += gv(ps[FD][i][j], ps[FL][i][j]);
        }

        printf("Case #%d: %lld\n", tc, ans);
    }
    return 0;
}