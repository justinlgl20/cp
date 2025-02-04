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

int seen[500005];

vector<pii> adj[500005];
int val[500005];

void dfs(int u, int value) {
    seen[u] = 1;
    val[u] = value;
    for (auto i : adj[u]) {
        if (!seen[i.f]) {
            dfs(i.f, value^i.s);
        }
    }
}

int32_t main() {
    int n, m; cin >> n >> m;
    vector<pair<int, pii>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, make_pair(u, v));
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; i++) {
        if (!seen[i]) dfs(i, 0);
        dbg(i, val[i]);
    }
    for (auto i : edges) {
        if ((val[i.s.f]^val[i.s.s]) != i.f) {
            dbg(i.f, val[i.s.f]^val[i.s.s]);
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    for (auto i : edges) {
        cout << i.f << " ";
    }
    cout << "\n";

}
