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

vector<int> adj[200005];
int hop[200005][22];
int tin[200005],tout[200005];
int depth[200005];
int cnt=1;
void dfs(int u,int p){
	tin[u]=cnt++;
	depth[u]=depth[p]+1;
	hop[u][0]=p;
	dbg(u, 0, p);
	for(int i=1;i<=20;i++){
		hop[u][i]=hop[hop[u][i-1]][i-1];
	}
	for(auto i:adj[u]) if(i!=p)dfs(i,u);
	tout[u]=cnt++;
}

int up(int u,int k) {
	for(int i=0;i<=20;i++){
		if(k&(1ll<<i)){
			u=hop[u][i];
		}
	}
	return u;
}
bool is_anc(int u, int v){
	return (tin[u]<=tin[v] and tout[u]>=tout[v]);
}

int lca(int u,int v){
	if(is_anc(u,v))return u;
	if(is_anc(v,u))return v;
	for(int i=20;i>=0;i--){
		if(!is_anc(hop[u][i], v))u=hop[u][i];
	}
	return hop[u][0];
}

int32_t main() {
	tin[0]=0;
	tout[0]=1e18;
	int n;cin>>n;
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);
	}
	dfs(1,0);
	int q;cin>>q;
	while(q--){
		int a,b,c;cin>>a>>b>>c;
		int l=lca(a,b);
		int d1=depth[a]-depth[l];
		int ans;
		dbg(d1, c, l);
		if (d1>=c){
			dbg(a, c);
			ans=up(a,c);
			dbg(hop[a][0]);
		} else {
			c-=d1;
			// from l to c
			int d2=depth[b]-depth[l];
			if (c>=d2) ans=b;
			else {
				ans=up(b, d2-c);
			}
		}
		cout<<ans<<"\n";
	}
}
