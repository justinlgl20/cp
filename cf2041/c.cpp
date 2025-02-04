#include <bits/stdc++.h>
using namespace std;
 
int gri[13][13][13];
int dp[4100][4100][3];

int popcount(int x) {
    int ans = 0;
    for (int i = 0; i < 31; i++) {
        if (x&1<<i) {
            ans++;
        }
    }
    return ans;
}

int32_t main() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> gri[i][j][k];
            }
        }
    }
    int ans = 1e9;
    for (int k = 0; k < 4100; k++) {
        for (int j = 0; j < 4100; j++) {
                dp[k][j][0] = 1e9;
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        // gri we are up to
        for (int k = 0; k <= (1ll<<n); k++) {
            for (int j = 0; j <= (1ll<<n); j++) {
                    dp[k][j][i%2] = 1e9;
            }
        }
        for (int col = 1; col <= (1ll<<(n)) - 1ll; col++) {
            if (__builtin_popcount(col) == i) {
                for (int j = 0; j < n; j++) {
                    if (col&(1ll<<j)) {
                        for (int row = 1; row <= (1ll<<(n)) - 1ll; row++) {
                            if (__builtin_popcount(row) == i) {
                                for (int k = 0; k < n; k++) {
                                    if (row&(1ll<<k)) {
                                        dp[col][row][i%2] = min(dp[col][row][i%2], dp[col&(~(1ll<<j))][row&(~(1ll<<k))][(i-1+2)%2]+gri[i][j][k]);
                                        if (i == n) {
                                            ans = min(ans, dp[col][row][i%2]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ans << "\n";
}
