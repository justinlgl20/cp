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

vector<pii> adj[200005], radj[200005];
int deg[200005];

int32_t main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        deg[v]++;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, -w);
    }
    int start = 0;
    queue<int> starts;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) start = i;
    }
    vector<int> seen(n+4, 0);
    vector<int> val(n+4, -1);
    function<void(int)> dfs = [&](int u) {
        seen[u] = true;
        dbg(u);
        for (auto i : adj[u]) {
            if (!seen[i.f]) {
                val[i.f] = val[u]+i.s;
                dfs(i.f);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!seen[i]) {
            val[i] = 1; dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << val[i] << " \n"[i==n];
    }
}
