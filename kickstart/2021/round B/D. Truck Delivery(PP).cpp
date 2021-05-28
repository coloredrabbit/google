#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;
const int MAX_N = 5e4, MAX_Q = 1e5, RANGE = 1 << 17;
struct edge { int x, y, l; ll a; } edges[MAX_N];
bool operator<(const edge& a, const edge& b) { return a.l < b.l; }
struct q { int c, w, i; } queries[MAX_Q];
bool operator<(const q& a, const q& b) { return a.w < b.w; }
int cL[MAX_N], cR[MAX_N], ordered[MAX_N], tindex;
ll lazy[RANGE], t[RANGE];
vector<int> adj[MAX_N];
ll gcd(ll p, ll q) {
	ll t;
	while (q > 0) {
		t = p % q;
		p = q;
		q = t;
	}
	return p;
}
void push(int idx, bool isLeaf) {
	if (!lazy[idx]) return;
	t[idx] = gcd(t[idx], lazy[idx]);
	if (!isLeaf) {
		lazy[idx << 1] = gcd(lazy[idx << 1], lazy[idx]);
		lazy[idx << 1 | 1] = gcd(lazy[idx << 1 | 1], lazy[idx]);
	}
	lazy[idx] = 0;
}
ll query(int idx, int L, int R, int l, int r) {
	push(idx, L == R);
	if (R < l || r < L) return 0;
	if (l <= L && R <= r) return t[idx];
	int m = (L + R) >> 1;
	return gcd(query(idx << 1, L, m, l, r), query(idx << 1 | 1, m + 1, R, l, r));
}
void update(int idx, int L, int R, int l, int r, ll d) {
	push(idx, L == R);
	if (R < l || r < L) return;
	if (l <= L && R <= r) {
		lazy[idx] = gcd(lazy[idx], d);
		push(idx, L == R);
		return;
	}
	int m = (L + R) >> 1;
	update(idx << 1, L, m, l, r, d);
	update(idx << 1 | 1, m + 1, R, l, r, d);
	t[idx] = gcd(t[idx << 1], t[idx << 1 | 1]);
}
int dfs(int u, int p) {
	int& ui = ordered[u] = tindex++;
	cR[ui] = cL[ui] = ui;
	for (int& v : adj[u]) if (v ^ p)
		cR[ui] = dfs(v, u);
	return cR[ui];
}
int main() {
	int tc, T, N, Q, i, u, v, ei;
	ll ans[MAX_Q];
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		tindex = 0;
		memset(t, 0, sizeof t);
		memset(lazy, 0, sizeof lazy);

		scanf("%d%d", &N, &Q);
		for (i = 0; i < N; i++) adj[i].clear();

		for (i = 0; i < N - 1; i++) {
			scanf("%d%d%d%lld", &u, &v, &edges[i].l, &edges[i].a);
			u--, v--;
			edges[i].x = u, edges[i].y = v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		sort(edges, edges + N - 1);
		dfs(0, -1);

		for (i = 0; i < Q; i++) {
			scanf("%d%d", &queries[i].c, &queries[i].w);
			queries[i].c--;
			queries[i].i = i;
		}
		sort(queries, queries + Q);
		for (ei = i = 0; i < Q; i++) {
			q& cq = queries[i];
			while (ei < N - 1) {
				edge& e = edges[ei];
				if (e.l > cq.w) break;

				u = ordered[e.x], v = ordered[e.y];
				if (u < v) swap(u, v);
				update(1, 0, N - 1, cL[u], cR[u], e.a);
				ei++;
			}

			int ci = ordered[cq.c];
			ans[cq.i] = query(1, 0, N - 1, cL[ci], cL[ci]);
		}
		printf("Case #%d: ", tc);
		for (i = 0; i < Q; i++) printf("%lld ", ans[i]);
		puts("");
	}
	return 0;
}