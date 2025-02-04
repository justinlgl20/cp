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

const int MOD = 998244353;

void solve() {
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n+3, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> dp(n+3, vector<int>(n+2, 1e9));
    for (int i = 0; i <= n; i++) dp[1][i] = 0;
    vector<int> par(n+3, 0);
    vector<int> depth(n+3, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        par[u] = p;
        if (par[u] == 1) {
            for (int j = 0; j <= n; j++) {
                    // other case
                    dp[u][j] = 2 * ((int)adj[u].size()) - 1ll;
                if (j > 0) {
                    if (dp[par[u]][j-1] != 1e9)
                        dp[u][j] = min(dp[u][j],  1 + dp[par[u]][j-1]);
                }
                dp[u][j] %= MOD;
            }
        }
        else if (u != 1) {
            for (int j = 0; j <= n; j++) {
                if (dp[par[par[u]]][j] != 1e9)
                    dp[u][j] = min(dp[u][j], 2 * ((int)adj[u].size()) + dp[par[par[u]]][j]);
                if (j > 0 and dp[par[par[u]]][j-1] != 1e9) // used so far
                    dp[u][j] = min(dp[u][j], 2+dp[par[par[u]]][j-1]);
                dp[u][j] %= MOD;
            }
        }
        for (auto i : adj[u]) {
            if (i == p) continue;
            depth[i] = depth[u]+1;
            dfs(i, u);
        }
    };
    dfs(1, -1);
    while (q--) {
        int v, p; cin >> v >> p;
        cout << 1+dp[par[v]][p] << "\n";
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
