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

int dp[5005][5005][2];

void solve() {
    int n; cin >> n;
    vector<pii> things(n);
    for (int i = 0; i < n; i++) cin >> things[i].f;
    for (int i = 0; i < n; i++) cin >> things[i].s;
    for (int i = 0; i < n+3; i++) {
        for (int j = 0; j < n+3; j++) {
            for (int k = 0; k < 2; k++) dp[i][j][k] = -1e9;
        }
    }
    int ans = -1e9;
    for (int j = 0; j < n+3; j++) {
        dp[0][j][0] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (j > 0)
                dp[i][j][0] = max(dp[i][j][0], dp[i-1][j-1][0]+things[i-1].f);
            dp[i][j][0] = max(dp[i][j][0], dp[i-1][j][0]+things[i-1].s);
            if (j > 0)
                dp[i][j][1] = max(dp[i][j][1], dp[i-1][j-1][1]+things[i-1].f);
            dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][1]+things[i-1].s);
            dp[i][j][1] = max(dp[i][j][1], dp[i-1][j][0] + things[i-1].f + things[i-1].s);
            if (i == n) ans = max(ans, dp[i][j][1]);
        }
    }
    cout << ans << "\n";



}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
