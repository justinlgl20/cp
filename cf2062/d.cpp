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
	vector<int>l(n+4,0),r(n+4,0);
	vector<pair<pii,int>> s;
	for(int i=1;i<=n;i++){cin>>l[i]>>r[i];s.emplace_back(make_pair(r[i],l[i]),i);}
	sort(all(s));
	vector<vector<int>>adj(n+4,vector<int>());
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<int> highl=l,highr=r;
	int add=0;
	dbg("HI");
	int root = 1;
	function<void(int,int)> dfs=[&](int u,int p) {
		highl[u]=0;
		highr[u]=0;
		dbg(u,p);	
		int totaladd=0;
		for(auto i : adj[u]){
			if(i==p)continue;
			int oadd=add;
			dfs(i,u);
			dbg(i, add);
			int added_to_add=add-oadd;
			// need to apply this to all other values of highl and highr
			highl[i] -= added_to_add;
			highr[i] -= added_to_add;
			totaladd += added_to_add;
			add=oadd;
		}
		for(auto i : adj[u]){
			highl[i]+=totaladd;
			highr[i]+=totaladd;
			l[i] = max(highl[i], l[i]);
			r[i] = max(highr[i], r[i]);
			highl[u]=max(highl[u], highl[i]);
			highr[u]=max(highr[u],highr[i]);
		}
		add += totaladd;
		dbg(u, totaladd);
		l[u]+=add;
		r[u]+=add;
		if(u != root) {
			if(l[u] > highr[u]) {
				// our left is bigger than all children's rights
				// this means we must increase all children to our left
				// do nothing
			}
			if(r[u] < highl[u]){
				// we need to increase this node
				add += highl[u]-r[u];
				l[u] += highl[u]-r[u];
				r[u] += highl[u]-r[u];
			}
		} else {
			if(r[u] < highl[u]) {
				int ans=0;
				for(auto i : adj[u]) {
					dbg(i, highl[i]);
					if(highl[i] > r[u]) {
						ans += highl[i]-r[u];
					}
				}
				l[u]=max(ans, l[u]);;
			}
			if(l[u] > highr[u]) {
				int ans=0;
				for(auto i : adj[u]) {
					if(highr[u] < l[u]) {
						ans += l[u] - highr[u];
					}
				}
				l[u]=max(l[u], ans);
			}
		}
		highl[u]=max(highl[u],l[u]);
		highr[u]=max(highr[u],r[u]);
	};
	dfs(root,0);
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,l[i]);
	}
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
