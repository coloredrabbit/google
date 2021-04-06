#include<cstdio>
#include<unordered_map>
#include<algorithm>
using namespace std;
using ll = long long;
const ll MAX_R = 5e4;
unordered_map<ll, ll> p[2], l[2], r[2];
ll gv(int y, int x) { return y * MAX_R + x; }
ll find(ll u, int idx) {
    if (p[idx].find(u) == p[idx].end()) {
        int y = u / MAX_R, x = u % MAX_R;
        l[idx][u] = gv(y - !idx, x - idx);
        r[idx][u] = gv(y + !idx, x + idx);
        return p[idx][u] = u;
    }
    return u == p[idx][u] ? u : p[idx][u] = find(p[idx][u], idx);
}
void merge(ll u, ll v, int idx) {
    u = find(u, idx), v = find(v, idx);
    if (u == v) return;
    p[idx][u] = v;
    l[idx][v] = min(l[idx][v], l[idx][u]);
    r[idx][v] = max(r[idx][v], r[idx][u]);
}
int cmd(char& c) {
    switch (c) {
    case 'N': return 0;
    case 'S': return 1;
    case 'W': return 2;
    }
    return 3;
}
int main() {
    char d;
    int tc, T, R, C, N, sr, sc, dy[] = { -1,1,0,0 }, dx[] = {0,0,-1,1}, i, j, k;
    ll u, v, x;
    scanf("%d", &T);
    for (tc = 1; tc <= T; tc++) {
        scanf("%d%d%d%d%d\n", &N, &R, &C, &sr, &sc);
        sr--, sc--;
        u = gv(sr, sc);
        for (i = 0; i < 2; i++) {
            p[i].clear(); l[i].clear(); r[i].clear();
            find(u, i);
        }
        while (N--) {
            scanf("%c", &d);

            j = cmd(d);
            i = j > 1;
            v = j % 2 ? r[i][u] : l[i][u];
            sr = v / MAX_R, sc = v % MAX_R;

            find(v, 0); find(v, 1);
            for (k = 0; k < 4; k++) {
                i = k > 1;
                x = gv(sr + dy[k], sc + dx[k]);
                if (p[i].find(x) != p[i].end())
                    merge(x, v, i);
            }
            u = v;            
        }
        printf("Case #%d: %d %d\n", tc, sr + 1, sc + 1);
    }
    return 0;
}