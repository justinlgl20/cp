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

void solve() {
	int n;cin>>n;
	
	vector<int> deg(n+4,0);
	vector<vector<int>> adj(n+4,vector<int>());
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;
		dbg(n, u, v);
		deg[u]++;deg[v]++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	if(n<=2) {
		cout<<"0\n";
		return;
	}
	multiset<int> degs;
	for(int i = 1;i<=n;i++){
		degs.insert(deg[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(deg[i]==1)continue;
		degs.erase(degs.find(deg[i]));
		for(auto j : adj[i]){
			degs.erase(degs.find(deg[j]));
				degs.insert(deg[j]-1);
		}
		dbg(i, deg[i], (*degs.rbegin()));
		ans = max(ans, deg[i]+(*degs.rbegin())-1ll);
		degs.insert(deg[i]);
		for(auto j : adj[i]){
				degs.erase(degs.find(deg[j]-1));
			degs.insert(deg[j]);
		}
	}
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
