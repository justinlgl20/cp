#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif
 
#define pii pair<int, int>
#define f first
#define s second
 
int dp[4100][4100][2];
 
int32_t main() {
    // start from dp[0][0][0]
vector<vector<int>> gri[13];
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            vector<int> v;
            for (int k = 1; k <= n; k++) {
                int x; cin >> x;
                v.push_back(x);
            }
            gri[i].push_back(v);
        }
    }
    int ans = 1e9;
    
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        // gri we are up to
        for (int k = 0; k < 4100; k++) {
            for (int j = 0; j < 4100; j++) {
                    dp[k][j][i] = 1e9;
            }
        }
        for (int col = 1; col <= (1ll<<(n)) - 1ll; col++) {
            for (int row = 1; row <= (1ll<<(n)) - 1ll; row++) {
                for (int j = 0; j < n; j++) {
                    if (col&(1ll<<j) and __builtin_popcount(col) == i) {
                        for (int k = 0; k < n; k++) {
                            if (row&(1ll<<k) and __builtin_popcount(row) == i) {
                                dp[col][row][i%2] = min(dp[col][row][i%2], dp[col&(~(1ll<<j))][row&(~(1ll<<k))][(i+1)%2]+gri[i][j][k]);
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
    cout << ans << "\n";
}