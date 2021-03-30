#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<cmath>
using namespace std;
using ll = long long;
const int MAX_N = 1e5 + 5;
int main() {
	int T, tc, K, S, N;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d%d", &N, &K, &S);
		printf("Case #%d: %d\n", tc, K + min(N, K - S + N - S));
	}
	return 0;
}