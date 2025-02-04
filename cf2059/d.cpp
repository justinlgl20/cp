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
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n,s1,s2;cin>>n>>s1>>s2;
	vector<vector<int>>cost(n+4,vector<int>(n+4,1e18));
	vector<vector<int>>works(n+4,vector<int>(n+4,0));
	cost[s1][s2]=0;
	vector<vector<int>> adj(n+4,vector<int>());
	vector<vector<int>> adj2(n+4,vector<int>());
	int m1;cin>>m1;
	for(int i=0;i<m1;i++){
		int u,v;cin>>u>>v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
		works[u][v]++;
		works[v][u]++;
	}
	int m2;cin>>m2;
	for(int i=0;i<m2;i++){
		int u,v;cin>>u>>v;
		adj2[u].emplace_back(v);
		adj2[v].emplace_back(u);
		works[u][v]++;
		works[v][u]++;
	}
	vector<int> dest(n+4,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(works[i][j]>=2)dest[i]=1;
		}
	}
	priority_queue<pair<int,pii>> q;
	q.push(make_pair(0ll, make_pair(s1,s2)));
	while (q.size()) {
		int w=-q.top().f,u=q.top().s.f,v=q.top().s.s;
		q.pop();
		if(w>cost[u][v]) continue;
		for(int i : adj[u]){
			for(int j : adj2[v]){
				if(w+abs(i-j)<cost[i][j]){
					cost[i][j]=w+abs(i-j);
					q.push(make_pair(-cost[i][j], make_pair(i, j)));
				}
			}
		}
	}
	int ans=1e18;
	for(int i=1;i<=n;i++){
		if(dest[i])ans=min(ans,cost[i][i]); 
	}
	if(ans==1e18){
		cout<<"-1\n";return;
	}
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;while(t--)solve();
}
