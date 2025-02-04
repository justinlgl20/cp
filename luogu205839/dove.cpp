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

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+4, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> val(n+3, 0);
    int l = 1, r = n;
    function<void(int, int)> dfs =  [&](int u, int p) {
        for (auto i : adj[u]) {
            if (i != p) dfs(i, u);
        }
        if (!val[u]) {
            val[u] = r--;
            if (p&&!val[p]) val[p] = l++;
        }
    };
    dfs(1, 0);
    for (int i = 1; i <= n; i++) cout << val[i] << " \n"[i==n];
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
