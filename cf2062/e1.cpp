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

struct BinaryLifting {
    int n, r;
    vector<vector<int>> adj;
    vector<int> par, jmp, depth;
    void init(int _n) {
        n = _n;
        adj.resize(n);
        par = jmp = depth = vector<int>(n);
    }
    void ae(int u, int v,int w = 1) { adj[u].push_back(v), adj[v].push_back(u); }
    void gen(int _r = 0) { r = _r, par[r] = jmp[r] = r; dfs(r); }
    void dfs(int u = 0) {
        for (int v : adj[u]) {
            depth[v] = depth[u] + 1;
            par[v] = u;
            if (depth[jmp[jmp[u]]] + depth[u] == 2 * depth[jmp[u]]) jmp[v] = jmp[jmp[u]];
            else jmp[v] = u;
            adj[v].erase(find(all(adj[v]), u));
            dfs(v);
        }
    }
    int lift(int u, int d) {
        if (d == 0) return r;
        while (depth[par[u]] >= d) {
            if (depth[jmp[u]] >= d) u = jmp[u];
            else u = par[u];
        }
        return u;
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = lift(u, depth[v]);
        if (u == v) return u;
        while (u != v) {
            if (jmp[u] != jmp[v]) u = jmp[u], v = jmp[v];
            else u = par[u], v = par[v];
        }
        return u;
    }
    int dist(int u, int v) { // # of edges on path
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

void solve() {
	int n;cin>>n;
	vector<int>v(n+3,0);
	for(int i=1;i<=n;i++)cin>>v[i];
	set<int>s;
	for(auto i=1;i<=n;i++)s.insert(v[i]);
	vector<vector<int>> adj(n+3,vector<int>());
	BinaryLifting tree;
	tree.init(n+4);
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;
		tree.ae(u,v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	tree.gen(1);
	vector<int> tin(n+3,0),tout(n+3,0);
	int cnt=0;
	function<void(int,int)>dfs=[&](int u,int p) {
		tin[u]=cnt++;
		for(auto i:adj[u]){
			if(i==p)continue;
			dfs(i,u);
		}
		tout[u]=cnt++;
	};
	dfs(1,0);
	function<bool(int,int)>is_anc=[&](int u,int p){
		return tin[p]<=tin[u] and tout[u]<=tout[p];
	};
	vector<pii> vs;
	for(int i=1;i<=n;i++){
		vs.emplace_back(v[i],i);
	}
	sort(all(vs));
	int mx=vs.back().f;
	int anc=vs.back().s;
	while (vs.size() and vs.back().f==mx){anc=tree.lca(anc,vs.back().s);vs.pop_back();}
	int last=-1, qd=1;
	if(vs.size()){
		last=vs.back().f;
		qd=vs.back().s;
	}
	bool working=false;
	vector<int> answers;
	while (vs.size()) {
		// try this one
		int u=vs.back().s;
		dbg(u, anc);
		vs.pop_back();
		if(v[u]!=last and working) break;
		if(v[u]!=last){
			anc=tree.lca(anc,qd);
			qd=u;
			last=v[u];
		}
		qd = tree.lca(qd,u);
		if(is_anc(anc,u)){
			// u is an ancestor of all the biggest ones
			// so if we take u, we lose
			continue
		} else {
			working=1;
			answers.push_back(u);
		}
	}
	// now we want all things that can get rid of all things in answer without getting rid of all the things that have value >= answer value

	cout<<"0\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
