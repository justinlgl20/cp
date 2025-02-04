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

struct dsu {
    vector<int> p;
    vector<int> sz;
    dsu(int n) {
        p.resize(n+4);
        sz.resize(n+4);
        for (int i = 0; i < n+3; i++) p[i] = i, sz[i] = 1;;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a=rep(a), b= rep(b);
        if (a == b) return;
        p[a] = b;
        sz[b] += sz[a];
    }
};

void solve() {
    int n; cin >> n;
    dsu x = dsu(n);
    vector<vector<int>> adj(n+3, vector<int>());
    for (int i = 1; i < n; i++) {
        char c; cin >> c;
        if (c == '<') {
            adj[x.rep(i)].push_back(i+1);
        }
        if (c == '>') {
            adj[i+1].push_back(x.rep(i));
        }
        if (c == '=') {
            x.merge(i+1, i);
        }
    }
    vector<int> seen(n+5, 0);
    vector<int> size(n+5, 0);
    function<void(int)> dfs = [&](int u) {
        seen[u] = 1;
        size[u] = x.sz[u];
        for (auto i : adj[u]) {
            if (!seen[i]) {
                dfs(i);
            }
            size[u] += size[i];
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!seen[i] and x.rep(i) == i) {
            dfs(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (x.rep(i) == i) {
            dbg(i, size[i], x.sz[x.rep(i)]);
            ans += x.sz[x.rep(i)] * (size[i] - x.sz[x.rep(i)]);
        }
    }
    cout << ans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
