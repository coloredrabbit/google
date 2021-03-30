#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
using seg_data = int;
const int MAX_N = 1e5, TS = 2e5;
struct seg_tree {
	int n;
	seg_data v_tree_sum[(TS + 1) * 2] = {}, v_tree_prefix[(TS + 1) * 2] = {};
	void setN(int n) {
		int i = 0;
		while ((1 << i) < n) i++;
		this->n = (1 << i);
	}
	void build() {
		for (int i = n - 1; i; i--) {
			v_tree_sum[i] = v_tree_sum[i << 1] + v_tree_sum[i << 1 | 1];
			v_tree_prefix[i] = max(v_tree_prefix[i << 1], v_tree_sum[i << 1] + v_tree_prefix[i << 1 | 1]);
		}
	}

	void update(int idx, seg_data d) {
		int L, R;
		for (v_tree_sum[idx += n] = d; idx > 1; idx >>= 1) {
			v_tree_sum[idx >> 1] = v_tree_sum[idx] + v_tree_sum[idx ^ 1];
			L = idx, R = idx ^ 1;
			if (L & 1) swap(L, R);
			v_tree_prefix[idx >> 1] = max(v_tree_prefix[L], v_tree_sum[L] + v_tree_prefix[R]);
		}
	}
};

int main() {
	int T, tc, N, S, A[MAX_N], i, ans;
	map<int, deque<int>> cnt;
	seg_tree st;
	scanf("%d", &T);
	for (tc = 1; tc <= T; tc++) {
		scanf("%d%d", &N, &S);
		st.setN(N);
		cnt.clear();
		memset(st.v_tree_prefix, 0, sizeof st.v_tree_prefix);
		memset(st.v_tree_sum, 0, sizeof st.v_tree_sum);
		for (i = 0; i < N; i++) {
			scanf("%d", &A[i]);
			deque<int>& d = cnt[A[i]];
			d.push_back(i);
			st.v_tree_prefix[st.n + i] = st.v_tree_sum[st.n + i] = d.size() == S + 1 ? -S : (d.size() <= S);
		}
		st.build();
		ans = 0;
		for (i = 0; i < N; i++) {
			ans = max(ans, st.v_tree_prefix[1]);
			deque<int>& d = cnt[A[i]];
			d.pop_front();
			st.update(i, 0);
			if (d.size() >= S) {
				st.update(d[S - 1], 1);
				if (d.size() >= S + 1)
					st.update(d[S], -S);
			}
		}
		printf("Case #%d: %d\n", tc, ans);
	}
	return 0;
}