#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<cstring>
#include<cmath>
#include<stack>
using namespace std;
using ll = long long;
const int MAX_N = 61, MOD = 1e9 + 7;
int main() {
    char nxt;
    int tc, X, i, j, k, d, l, o, trace[MAX_N][MAX_N][MAX_N][3] = {}, T, W, E, _result[3];
    double p[3], exp, dp[MAX_N][MAX_N][MAX_N], target;
    stack<char> stk;
    trace[0][0][0][0] = 1, trace[0][0][0][1] = trace[0][0][0][2] = 0;
    scanf("%d%d", &T, &X);
    for (tc = 1; tc <= T; tc++) {
        memset(dp, 0, sizeof dp);
        target = 0;

        scanf("%d%d", &W, &E);
        dp[1][0][0] = dp[0][1][0] = dp[0][0][1] = (W + E) / 3.;
        for (d = 2; d < MAX_N; d++) {
            for (i = 0; i < MAX_N; i++) for (j = 0; i + j <= d; j++) {
                k = d - i - j;

                p[0] = (double)j / d;
                p[1] = (double)k / d;
                p[2] = (double)i / d;

                for (l = 0; l < 3; l++) {
                    int ni = i - (l == 0), nj = j - (l == 1), nk = k - (l == 2);
                    if (0 <= ni && 0 <= nj && 0 <= nk) {
                        exp = 0;
                        for (o = 0; o < 3; o++) {
                            if (l == o) exp += p[o] * E;
                            else if ((l + 1) % 3 == o)
                                exp += p[o] * W;
                        }
                        if (dp[i][j][k] < dp[ni][nj][nk] + exp / T) {
                            dp[i][j][k] = dp[ni][nj][nk] + exp / T;
                            trace[i][j][k][0] = ni;
                            trace[i][j][k][1] = nj;
                            trace[i][j][k][2] = nk;

                            if (target < dp[i][j][k]) {
                                target = dp[i][j][k];
                                _result[0] = i;
                                _result[1] = j;
                                _result[2] = k;
                            }
                        }
                    }
                }
            }
        }
        printf("Case #%d: ", tc);
        i = _result[0], j = _result[1], k = _result[2];
        for (d = 1; d < MAX_N; d++) {
            int ni = trace[i][j][k][0], nj = trace[i][j][k][1], nk = trace[i][j][k][2];
            if (i != ni) nxt = 'R';
            else nxt = j != nj ? 'S' : 'P';
            i = ni, j = nj, k = nk;
            stk.push(nxt);
        }
        while (!stk.empty()) {
            printf("%c", stk.top());
            stk.pop();
        }
        puts("");
    }
    return 0;
}