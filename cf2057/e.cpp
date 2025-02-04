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

int MAXN = 400;

int id, par[2 * MAXN];
vector<int> adj[2 * MAXN];

int find(int u) {
    return par[u] == u ? u : par[u] = find(par[u]);
}

void unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)
        return;
    par[u] = par[v] = par[id] = id;
    adj[id] = {u, v};
    id++;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<pair<int, pii>> edges;
	for (int i = 0; i < m; i++) {
		int u,v,w;cin>>u>>v>>w;
		edges.emplace_back(w, make_pair(u, v));
	}
	sort(all(edges));
	for (
}
