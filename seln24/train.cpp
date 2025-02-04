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
    dsu(int n) {
        p.resize(n+3);
        for (int i = 0; i < n+2; i++) p[i] = i;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        p[rep(a)] = rep(b);
    }
};

int32_t main() {
    int n; cin >> n;
    vector<vector<int>> adj(n+4, vector<int>());
    vector<pair<pii, int>> edges;
    int c = 0;
    for (int i = 0; i < n-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.emplace_back(make_pair(u, v), w);
        adj[u].push_back(v);
        adj[v].push_back(u);
        c += w;
    }
    int k; cin >> k;
    vector<pii> hubs(k);
    for (int i = 0; i < k; i++) {
        cin >> hubs[i].s >> hubs[i].f;
    }
    dsu uf = dsu(n);
    sort(all(hubs));
    int cost = 0;
    for (int i = 1; i < k; i++) {
        edges.emplace_back(make_pair(hubs[i].s, hubs[0].s), hubs[i].f+hubs[0].f);
    }
    sort(all(edges), [&](auto x, auto y) {
        return x.s < y.s;
    });
    for (auto i : edges) {
        if (uf.rep(i.f.f) != uf.rep(i.f.s)) {
            uf.merge(i.f.f, i.f.s);
            cost += i.s;
        }
    }
    cout << c - cost << "\n";

}
