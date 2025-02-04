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

void dfs(int u,vector<vector<int>>&adj,vector<int>&order,vector<int>&seen) {
	seen[u]=1;
	for(auto i:adj[u]){
		if(!seen[i])dfs(i,adj,order,seen);
	}
	order.push_back(u);
}

int32_t main() {
	int n,m;cin>>n>>m;
	vector<vector<int>> adj(n+2,vector<int>()),radj(n+2,vector<int>());
	for(int i=0;i<m;i++){
		int u,v;cin>>u>>v;
		adj[u].push_back(v);
		radj[v].push_back(u);
	}
	vector<int>vis(n,0);
	vector<int>order;
	for(int i=0;i<n;i++)if(!vis[i])dfs(i,adj,order,vis);
	reverse(all(order));
	vis.assign(n,0);
	vector<int>roots(n+4,0);
	for(int u:order){
		if(!vis[u]){
			vector<int>comp;
			dfs(u,radj,comp,vis);
			int root=u;
			for(auto i:comp)roots[i]=root;
		}
	}
	vector<int>out(n+4,0);
	for(int i=0;i<n;i++){
		for(auto j:adj[i]){
			if(roots[i]!=roots[j]){
				out[roots[j]]=1;
			}
		}
	}
	int cnt=0;
	for(int i=0;i<n;i++) if(roots[i]==i) cnt+=(out[i]==0);
	if(cnt > 1) {
		cout<<"0\n";return 0;
	} else{
		for(int i=0;i<n;i++){
			if(roots[i]==i and out[i]==0){
				vector<int>ans;
				for(int j=0;j<n;j++){
					if(roots[j] == i)ans.push_back(j);
				}
				cout<<ans.size()<<"\n";
				for(auto i:ans)cout<<i<<"\n";
				return 0;
			}
		}
	}
}
