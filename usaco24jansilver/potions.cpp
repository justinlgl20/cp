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

int nxt() {
    int g; cin >> g; return g;
}

int32_t main() {
    int n = nxt();
    vector<int> p(n);
    generate(all(p), nxt);
    vector<vector<int>> adj(n+2, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int a=nxt(),b=nxt();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> tin(n+4);
    vector<int> tout(n+4);
    int cnt = 0;
    vector<int> arr(n+3, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        tin[u] = ++cnt;
        arr[tin[u]] = u;
        for (auto i : adj[u]) {
            if (i != p) dfs(i, u);
        }
        tout[u] = cnt;
    };
    dfs(1, 0);
    vector<bool> leaf(n+4, 0);
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1 and i != 1) {
            leaf[i] = 1;
        }
    }
    vector<pair<int, int>> ranges;
    for (int i = 0; i < n; i++) {
        ranges.emplace_back(tin[p[i]], tout[p[i]]);
    }
    // go through ranges in order and greedily take a good one if its there
    // otherwise mark one in the range as used up

}
