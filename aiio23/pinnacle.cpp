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
		dbg(u,v,w);
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

tree<100005> r, l;

int32_t main() {
	int n,m;cin>>n>>m;vector<int>a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	vector<int> psa(n,a[0]);
	for(int i=1;i<n;i++)psa[i]=psa[i-1]+a[i];
	function<int(int,int)>sum=[&](int l,int r){
		return psa[r]-(l>0?psa[l-1]:0);
	};
	stack<int> s; // stack is going down
	// parent of i is closest thing on right that is higher or equal to i, with weight of minimum number of things we must add
	for(int i=n-1;i>=0;i--){
		while(s.size() and a[s.top()]<a[i])s.pop();
		if(s.size())
			r.ae(i, s.top(), a[i]*(s.top()-i-1) - sum(i+1, s.top()-1));
		s.push(i);
	}
	while (s.size())s.pop();
	for(int i=0;i<n;i++){
		while(s.size() and a[s.top()]<a[i])s.pop();
		if(s.size())
			l.ae(i,s.top(),a[i]*(i-s.top()-1) - sum(s.top()+1, i-1));
		s.push(i);
	}
}
