#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cmath>
#include<string>
using namespace std;
using ll = long long;
const int MAX_N = 5e6+1;
int main() {
	char b[MAX_N + 1];
	int T, tc, N, ans, ps[MAX_N + 1], i, L;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d\n%s", &N, b);
		L = N % 2 + N / 2;
		for (i = 1; i <= N; i++)
			ps[i] = ps[i - 1] + (b[i - 1] - '0');
		ans = 0;
		for (i = L; i <= N; i++)
			ans = max(ans, ps[i] - ps[i - L]);
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}