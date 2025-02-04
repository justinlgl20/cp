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

struct seg{
	vector<int> t;
	int n;
	seg(int x) {
		n=1;while(n<=x)n*=2;
		t.resize(3*n+2);
		for(int i=0;i<3*n+1;i++)t[i]=0;
	}
	void upd(int p, int v) {
		for(t[p+=n]+=v;p>1;p>>=1)t[p>>1]=t[p]+t[p^1];
	}
	int query(int l, int r) {
		int ans=0;
		r++;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1) ans+=t[l++];
			if(r&1) ans+=t[--r];
		}
		return ans;
	}
};

void solve() {
	int n;cin>>n;
	vector<vector<int>> adj(n+3,vector<int>());
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> sz(n+4,0);
	vector<int> depth(n+4,1);
	function<void(int,int)>dfs=[&](int u,int p){
		sz[u]=1;
		for(int i : adj[u]){
			if(i==p)continue;
			depth[i]=depth[u]+1;
			dfs(i,u);
			sz[u]+=sz[i];
		}
	};
	dfs(1,0);
	vector<int> dep=depth;
	int ans=0;
	int done=0;
	int s=0;
	seg neg=seg(n+3),pos=seg(n+3), donedep=seg(n+3);;
	int depthsums=0;
	function<void(int,int)>solve=[&](int u,int p){
		int above, below;
		above = donedep.query(0, dep[u]);
		below = donedep.query(dep[u]+1, n+2);
		dbg(u, above,below, depthsums, s);
		int add=0;
		add += dep[u]*done;
		add += s-done;
		dbg(add);
		add -= depthsums;
		dbg(add);
		add = max(add,0ll);
		ans += add;
		// add done
		done++;
		s += (dep[u]-2*dep[u]);
		donedep.upd(dep[u], 1);
		// prepare to move down
		above = donedep.query(0, dep[u]);
		below = donedep.query(dep[u]+1, n+2);
		depthsums += above-below;
		for(int i : adj[u]){
			if(i==p)continue;
			// set done children's -2dep[p] to here
			solve(i, u);
			s += 2*sz[i];
		}
		// move back upn
		above = donedep.query(0, dep[u]);
		below = donedep.query(dep[u]+1, n+2);
		depthsums += below-above;
		dbg(u,s);
	};
	solve(1, 0);
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
