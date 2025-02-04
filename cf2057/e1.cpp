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
		p.resize(n+4);
		for (int i = 0; i < n+3; i++) p[i] = i;
	}
	int rep(int u) {
		if (p[u] == u) return u;
		return p[u] = rep(p[u]);
	}
	void merge(int a, int b) {
		p[rep(a)] = rep(b);
	}
};

void solve() {
	int n, m, q; cin >> n >> m >> q;
	vector<pair<int, pii>> edges;
	dsu x = dsu(n);
	for (int i = 0; i < m; i++) {
		int u, v, w; cin>>u>>v>>w;
		edges.emplace_back(w, make_pair(u, v));
	}
	sort(all(edges));
	vector<vector<int>> adj(n+4, 0);
	for (auto i : edges) {
		if (x.rep(i.s.f) != x.rep(i.s.s)) {
			x.merge(i.s.f, i.s.s);
			adj[i.s.f].emplace_back(i.s.s, i.f);
			adj[i.s.s].emplace_back(i.s.f, i.f);
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}
