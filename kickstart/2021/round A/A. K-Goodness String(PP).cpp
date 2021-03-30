#include<cstdio>
#include<set>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAX_N = 2e5, MSZ = 200;
int main() {
    char s[MAX_N + 1];
    int tc, T, N, K, c, i;
    scanf("%d", &T);
    for (tc = 1; tc <= T; tc++) {
        scanf("%d%d\n%s", &N, &K, s);
        for (c = i = 0; i < N / 2; i++)
            c += s[i] != s[N - i - 1];
        printf("Case #%d: %d\n", tc, abs(K - c));
    }
    return 0;
}