#include<cstdio>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 3e5 + 2, INF = 2e9;
struct _d { int c, d; } ps[MAX_N], es[MAX_N];
int main() {
	int tc, T, N, A[MAX_N], i, ans, d, tempc, nA;
	ps[0].c = 0, ps[0].d = INF;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d", &N);
		ans = 0;

		for (i = 1; i <= N; i++) scanf("%d", &A[i]);
		ps[1].c = 1, ps[1].d = INF;
		for (i = 2; i <= N; i++) {
			ps[i].c = 2;
			ps[i].d = A[i] - A[i - 1];
			if (ps[i].d == ps[i - 1].d)
				ps[i].c = ps[i - 1].c + 1;
			ans = max(ans, ps[i].c);
		}

		es[N + 1].c = 0, es[N + 1].d = INF;
		es[N].c = 1, es[N].d = INF;
		for (i = N - 1; i; --i) {
			es[i].c = 2;
			es[i].d = A[i + 1] - A[i];
			if (es[i].d == es[i + 1].d)
				es[i].c = es[i + 1].c + 1;
			ans = max(ans, es[i].c);
		}

		for (i = 1; i <= N; i++) {
			tempc = 1;
			if (1 < i) {
				tempc = ps[i - 1].c + 1;
				nA = A[i - 1] + ps[i - 1].d;
				if (i < N && A[i + 1] - nA == nA - A[i - 1]) {
					if ((A[i + 1] - nA == es[i + 1].d || es[i + 1].d == INF))
						tempc += es[i + 1].c;
					else tempc++;
				}	
				ans = max(ans, tempc);
			}
			if (i < N) {
				tempc = es[i + 1].c + 1;
				nA = A[i + 1] - es[i + 1].d;
				if (1 < i && A[i + 1] - nA == nA - A[i - 1]) {
					if ((nA - A[i - 1] == ps[i - 1].d || ps[i - 1].d == INF))
						tempc += ps[i - 1].c;
					else tempc++;
				}

				ans = max(ans, tempc);
			}
		}

		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}