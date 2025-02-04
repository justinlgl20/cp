//observe that either rows or columns must have at least 1 in each
#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n+1, 0);
	vector<int> b(n+1, 0);
	int ma= 1e10;
	int mb = 1e10;
	int sa = 0;
	int sb = 0;
	for (int i= 1; i <= n; i++){cin >> a[i];ma = min(a[i], ma);sa+=a[i];}
	for (int i = 1; i <= n; i++) {cin >> b[i];mb = min(b[i], mb);sb += b[i];}
	int ans = min(sa+n*mb, sb+n*ma);
	cout << ans << "\n";
}

int32_t main() {
	int t;
	cin >> t;
	while (t--) solve();
}
