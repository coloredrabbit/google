#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cstring>
#include<cmath>
#include<string>
using namespace std;
using ll = long long;
const int MAX_L = 101, LEN = 141;
struct _tree {
	string s;
	_tree* left, * right;
	void _del() {
		if (left) {
			left->_del();
			right->_del();
		}
	}
};
struct _bigint {
	int b[LEN] = {}, p = 0;
	_bigint() {}
	_bigint(int n) {
		if (!n) p = 1;
		while (n) {
			b[p++] = n;
			n /= 10;
		}
	}
	_bigint(const string& s) {
		for (const auto& c : s) {
			b[s.length() - 1 - p] = c - '0';
			p++;
		}
	}
	bool isZero() {
		return p == 1 && b[0] == 0;
	}
	string toString() {
		string r;
		for (int i = p - 1; i >= 0; i--)
			r += b[i] + '0';
		return r;
	}
	void calPosition() {
		int i;
		for (i = LEN - 1; i > 0; i--) if (b[i])
			break;
		p = i + 1;
	}
	_bigint& operator+=(const _bigint& o) {
		int s, c = 0, i;
		for (i = 0; i < LEN; i++) {
			s = b[i] + o.b[i] + c;
			c = s / 10;
			b[i] = s % 10;
		}
		calPosition();
		return *this;
	}
	_bigint operator+(const _bigint& o) {
		_bigint r;
		int s, c = 0, i;
		for (i = 0; i < LEN; i++) {
			s = b[i] + o.b[i] + c;
			c = s / 10;
			r.b[i] = s % 10;
		}
		r.calPosition();
		return r;
	}
	_bigint operator*(const _bigint& o) {
		_bigint r;
		int i, j, c = 0;
		for (i = 0; i < LEN; i++) for (j = 0; i + j < LEN; j++)
			r.b[i + j] += b[i] * o.b[j];
		for (i = 0; i < LEN; i++) {
			r.b[i] += c;
			c = r.b[i] / 10;
			r.b[i] %= 10;
		}
		r.calPosition();
		return r;
	}
};
struct _mul_group {
	vector<string> g;
	_mul_group() {}
	_mul_group(const string s) {
		g.push_back(s);
	}
};
bool operator<(const _mul_group& a, const _mul_group& b) {
	return a.g < b.g;
}
int np[MAX_L];
_tree* rec(string& s, int l, int r) {
	vector<_tree*> op;
	int i;
	for (i = l; i <= r; ) {
		if (np[i] != -1) {
			op.push_back(rec(s, i + 1, np[i] - 1));
			i = np[i] + 1;
		}
		else if (s[i] == '#' || s[i] == '+' || s[i] == '*') {
			if (op.empty()) op.push_back(rec(s, l, i - 1));
			_tree* o = new _tree;
			o->s = s[i];
			op.push_back(o);
			op.push_back(rec(s, i + 1, r));
			break;
		}
		else i++;
	}
	if (op.size() == 1) return op[0];
	else if (op.empty())
		return new _tree{ s.substr(l, r - l + 1) };
	else {
		op[1]->left = op[0];
		op[1]->right = op[2];
		return op[1];
	}
}
bool isNum(const _mul_group& a) {
	if (a.g.size() > 1) return 0;

	bool f = 1;
	for (const char& c : a.g[0]) if (c == '#')
		return 0;
	return 1;
}
string sum(map<_mul_group, _bigint>& m) {
	string ret;
	bool isFirst = 1;
	for (auto& it : m) {
		if (it.first.g.size() == 1 && (it.first.g[0] == "0" || it.first.g[0] == ""))
			continue;

		if (!ret.empty())
			ret += '+';

		if (!(it.second.p == 1 && it.second.b[0] <= 1))
			ret += it.second.toString();

		isFirst = 1;
		for (auto& x : it.first.g) {
			if (!isFirst)
				ret += '*';
			ret += x;
			isFirst = 0;
		}
	}
	if (ret.empty())
		ret = "0";
	return ret;
}
map<_mul_group, _bigint> build(_tree* u) {
	map<_mul_group, _bigint> ret;
	if (u->left) {
		map<_mul_group, _bigint> l = build(u->left), r = build(u->right);
		if (u->s[0] == '#')
			ret["(" + sum(l) + '#' + sum(r) + ")"] = 1;
		else {
			if (u->s[0] == '+') {
				_bigint n;
				for (auto& it : l) {
					if (isNum(it.first)) n = n + _bigint(it.first.g[0]);
					else ret[it.first] += it.second;
				}
				for (auto& it : r) {
					if (isNum(it.first)) n = n + _bigint(it.first.g[0]);
					else ret[it.first] += it.second;
				}
				if(!n.toString().empty())
					ret[n.toString()] = 1;
			}
			else if (u->s[0] == '*') {
				for (auto lt = l.begin(); lt != l.end(); lt++) {
					bool aIsN = isNum(lt->first);
					for (auto rt = r.begin(); rt != r.end(); rt++) {
						bool bIsN = isNum(rt->first);
						if (aIsN && bIsN)
							ret[(_bigint(lt->first.g[0]) * _bigint(rt->first.g[0])).toString()] = 1;
						else if (aIsN) {
							_bigint coe = _bigint(lt->first.g[0]);
							if (!coe.isZero()) ret[rt->first] += coe * rt->second;
						}
						else if (bIsN) {
							_bigint coe = _bigint(rt->first.g[0]);
							if (!coe.isZero()) ret[lt->first] += coe * lt->second;
						}
						else {
							_mul_group cur;
							
							cur.g.insert(cur.g.end(), lt->first.g.begin(), lt->first.g.end());
							cur.g.insert(cur.g.end(), rt->first.g.begin(), rt->first.g.end());
							sort(cur.g.begin(), cur.g.end());
							ret[cur] = ret[cur] + lt->second * rt->second;
						}
					}
				}
			}
		}
	}
	else
		ret[u->s] = 1;
	return ret;
}
int main() {
	string s, res;
	map<string, int> idx;
	map<_mul_group, _bigint> ans;
	stack<int> p;
	int tc, T, N, i, j, pos;
	cin >> T;
	for (tc = 1; tc <= T; tc++) {
		idx.clear(); ans.clear();
		pos = 1;

		printf("Case #%d: ", tc);
		cin >> N;
		for (i = 0; i < N; i++) {
			cin >> s;
			for (j = 0; j < s.length(); j++) {
				np[j] = -1;
				if (s[j] == '(') p.push(j);
				else if (s[j] == ')') {
					np[p.top()] = j;
					p.pop();
				}
			}

			_tree* t = rec(s, 0, s.length() - 1);
			ans = build(t);
			res = sum(ans);

			//cout << "(" << res << ')';

			auto it = idx.find(res);
			if (it != idx.end())
				printf("%d ", it->second);
			else {
				printf("%d ", pos);
				idx[res] = pos++;
			}
			t->_del();
		}
		puts("");
	}
	return 0;
}