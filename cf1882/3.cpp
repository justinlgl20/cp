#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n; cin >> n;
    vector<int> a(n+1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    int ans = 0;
    vector<int> dp(n+1, 0);
    int sumpos = 0;
    for (int i = 1; i <= n; i++) sumpos += (a[i] > 0 ? a[i]:0);
    if (n == 1) ans = sumpos;
    else if (a[1] < 0 and a[2] > 0) {
        ans = max(sumpos+a[1], sumpos-a[2]);
    } else {
        ans = sumpos;
    }
    cout << ans << "\n";
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) solve();
}
