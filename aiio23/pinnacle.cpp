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

#define pii pair<int, int>

template<int SZ>
struct tree {
	int p[SZ];
	int val[SZ];
	vector<pii> adj[SZ];
	void ae(int u, int v, int w){
		p[u]=v;
		adj[v].emplace_back(u,w);
	}
	void dfs(int u){
		for(auto i:adj[u]){
			val[i]=val[u]+i.s;
			dfs(i.f);
		}
	}
	void init(int root) {
		dfs(root);
	}
	void query(int u, int v){ // v is peak of mountain, u is l/r
		return val[u]-val[v];
	}
};

tree<100005> right, left;

int32_t main() {
	int n;cin>>n;vector<int>a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	stack<int> s; // stack is going down
}
