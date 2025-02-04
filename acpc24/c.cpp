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

int init_ans;

struct dsu {
	vector<int> p,sz;vector<pair<int&,int>>history;
	int ans;
	dsu(int n) {
		p.resize(n+4);
		ans=1;
		sz.resize(n+4);
		for(int i=0;i<n+3;i++)p[i]=i,sz[i]=1;
	}
	int rep(int n) {
		if(n==p[n])return n;
		return rep(p[n]);
	}
	void merge(int a, int b) {
		a=rep(a),b=rep(b);
		if(a==b)return;
		if(sz[a]<sz[b])swap(a,b);
		history.emplace_back(sz[a],sz[a]);
		history.emplace_back(p[b],p[b]);
		sz[a]+=sz[b];
		p[b]=a;
		ans=max(ans,sz[a]);
	}
	void rollback() {
		while (history.size()) {
			history.back().first=history.back().second;
			history.pop_back();
		}
		ans = init_ans;
	}
};

int32_t main() {
	int n,m;cin>>n>>m;
	vector<int>a(n+3);
	for(int i=0;i<n;i++)cin>>a[i];
	vector<pii> unmerged;
	dsu uf = dsu(n);
	for(int i=0;i<m;i++){
		int u,v;cin>>u>>v;
		if (a[u]==a[v]){uf.merge(u,v);dbg(u,v);}
		else unmerged.emplace_back(u,v);
	}
	init_ans=uf.ans;
	uf.history.clear();
	vector<unordered_map<int,vector<pii>>> adj(n+4,unordered_map<int,vector<pii>>());
	for(auto i : unmerged) {
		adj[a[i.f]][a[i.s]].emplace_back(i.f, i.s);
		adj[a[i.s]][a[i.f]].emplace_back(i.s, i.f);
	}
	int ans=init_ans;
	dbg(init_ans);
	for (int i=0;i<n;i++){
		for (auto j : adj[i]) {
			// merging i with j.f
			for (auto x : j.s) {
				uf.merge(x.f, x.s);
				dbg(x.f,x.s);
			}
			dbg(i, j.f, uf.ans);
			ans = max(ans, uf.ans);
			uf.rollback();
		}
	}
	cout<<ans<<"\n";
}
