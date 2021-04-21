#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 3e5, LIMIT = 300;
bool isP(ll n) {
	int i;
	ll sqrtN = sqrt(n);
	for (i = 2; i <= sqrtN; i++) if (n % i == 0)
		return 0;
	return 1;
}
int main() {
	int tc, T;
	ll X, R, i, j, k, t, Z, sqrtZ, ans, l, r, mid;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%lld", &Z);
		ans = 0;
		l = 1, r = 1e9;
		while (l <= r) {
			mid = l + r >> 1;
			if (mid * mid <= Z) l = mid + 1;
			else r = mid - 1;
		}
		sqrtZ = r;
		for (i = max(1LL, sqrtZ - LIMIT); i <= sqrtZ; i++) {
			if (isP(i)) {
				j = i + 1;
				while (!isP(j)) j++;
				if (i * j <= Z) {
					ans = max(ans, i * j);
				}
			}
		}
		printf("Case #%d: %lld\n", tc, ans);
	}
	return 0;
}