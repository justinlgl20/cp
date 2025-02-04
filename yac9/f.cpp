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

int MOD;
int a[500005];
struct dsu {
	vector<int> p;
	vector<vector<int>> e;
	dsu(int n) {
		p.resize(n+4);
		e.resize(n+4);
		for(int i=0;i<n+3;i++)p[i]=i,e[i]={i};
	}
	int rep(int u) {if(p[u]==u)return u;return p[u]=rep(p[u]);}
	void merge(int a, int b) {
		a=rep(a),b=rep(b);if(a==b)return;
		if (e[a].size()>e[b].size())swap(a,b); // b is bigger
		p[a]=b;
		for(auto i:e[a])e[b].push_back(i);
	}
};

vector<int> adj[500005]; // this is for all the mini trees
vector<pair<int,pii>> badj[500005]; // this is for the compressed colours
int dp[500005];
int depth[500005];
int top[500005];
vector<int> e[500005];

void dfs2(int u, int p) {
	for (auto i : adj[u]) {
		if(i==p)continue;
		depth[i]=depth[u]+1;
		dfs2(i,u);
	}
}

int32_t main() {
	int n; cin>>n>>MOD;
	for(int i=1;i<=n;i++){cin>>a[i];e[a[i]].push_back(i);}
	dsu uf = dsu(n);
	vector<pii> l;
	for(int i=0;i<n;i++){
		int u,v;cin>>u>>v;
		if(a[u]==a[v]){
			adj[u].push_back(v);
			adj[v].push_back(u);
			uf.merge(u,v);
		} else {
			l.emplace_back(u,v);
			// one of these is the top, and the others are the bottom
		}
	}
	for(auto i:l){
		dbg(a[i.f], a[i.s]);
		badj[a[i.f]].emplace_back(a[i.s], make_pair(i.s, i.f));
		badj[a[i.s]].emplace_back(a[i.f], make_pair(i.f,i.s));
	}
	int root = a[1];
	dbg(root);
	function<void(int,int)> dfs=[&](int u,int p) {
		for (auto i : badj[u]){
			if(i.f!=p){dfs(i.f, u);}
		}
		if (badj[u].size()==1 and p!=-1){
			// leaf
			for (auto i :e[u]){
				dp[i]=1;
			}
			return;
		}
		dbg(u);
		for (int j : e[u]) {
			dp[j] = 1;
			dbg(j);
			for (auto idk : badj[u]) {
				int c = idk.f;
				int topc = idk.s.f;
				int ptopc=idk.s.s;
				dbg(c, topc, ptopc);
				dfs2(topc,-1);
				int ans = 0;
				for (auto i : e[c]){
					dbg(i, depth[i]-depth[topc], depth[ptopc]-depth[j]);
					if (abs((depth[i]-depth[topc])-(depth[ptopc]-depth[j]))<=1) ans+=dp[i];
					ans%=MOD;
				}
				dp[j]*=ans;
				dp[j]%=MOD;
			}
		}
	};
	dfs2(1,-1);
	dfs(root,-1);
	int ans = 0;
	for(auto i : e[root]) {
		ans+=dp[i];
		ans%=MOD;
	}
	cout << ans << "\n";
}
