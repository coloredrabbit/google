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
const int MAX_N = 15, SEG_SIZE= 756777; // almost 15C5 * 10C5
int main() {
	string s;
	int T, tc, A, B, mid, N;
	cin >> T;
	for (tc = 1; tc <= T; tc++) {
		cin >> A >> B >> N;
		while(N >= 0){
			N--;

			mid = (A + B) / 2;
			cout << mid << '\n';
			cin >> s;
			if(s[0] == 'C') break;
			else if(s[4] == 'B') B = mid - 1;
			else A = mid + 1;
		}
	}
	return 0;
}