#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 2e5;
int main() {
	int tc, T, i, L, bef, c, a, cur;
	vector<int> ans;
	char S[MAX_N + 1];
	scanf("%d\n", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d\n%s", &L, S);
		bef = -1, c = 0;
		ans.clear();
		for (i = 0; S[i]; i++) {
			if (bef >= S[i]) c = 1;
			else c++;
			bef = S[i];
			ans.push_back(c);
		}
		printf("Case #%d: ", tc);
		for (int& a : ans) printf("%d ", a);
		puts("");
	}
	return 0;
}