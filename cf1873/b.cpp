#include <bits/stdc++.h>
using namespace std;
#define int long long


int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> g(n);
        int m = 1e9, p = -1;
        for (int i = 0; i < n; i++){
            cin >> g[i];
            if (g[i] < m) {m = g[i];
            p = i;}
        }
        g[p] += 1;
        int ans = 1;
        for (int i = 0; i < n; i++) ans *= g[i];
        cout << ans << "\n";
        
    }
}
