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


int32_t main() {
	int n;cin>>n;
	vector<vector<int>> adj(n+5,vector<int>());
	vector<int> par(n+4,0);
	int root=-1;
	for(int i=0;i<n;i++){
		int p;cin>>p;
		par[i+1]=p;
		if(i+1!=p)
			adj[p].emplace_back(i+1);
		else {
			root = p;
		}
	}
	vector<int> depth(n+4,0);
	unordered_map<int,int> a;
	int s=0;
	function<void(int,int)>dfs=[&](int u,int p) {
		depth[u]=depth[p]+1;
		if(a.find(depth[u])==a.end()){
			a[depth[u]]=0;
		}
		a[depth[u]]++;
		s++;
		for(auto i:adj[u])if (i!=p)dfs(i,u);
	};
	int ans=0;
	dbg(root);
	vector<int> sz;
	for(int i : adj[root]){
		if(par[i]==root) {
			a.clear();
			s=0;
			dfs(i,root);
			if(s>0){
				sz.push_back(s);
			}
			for(auto q : a) {
				ans += q.s*(q.s-1ll);
			}
		}
	}
	int aw=(n-1ll)*(n);
	for(auto i : sz) {
		aw -= i*(i-1ll);
	}
	ans += aw;
	ans += n;
	cout<<ans<<"\n";

}
