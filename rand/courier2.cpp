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

int N, K;
vector < pii > p;
vector<int> adj[200005];

template<typename T, int SZ> struct LazySeg { 
	static_assert(__builtin_popcount(SZ)==1);
	const T ID{}; T cmb(T a, T b) { return a+b; }
	T seg[2*SZ], lazy[2*SZ]; 
	LazySeg() { for(int i=0;i<2*SZ;++i) seg[i] = lazy[i] = ID; }
	void push(int ind, int L, int R) { /// modify values for current node
		if(lazy[ind]==-1)return;
		seg[ind] = (R-L+1)*lazy[ind]; // dependent on operation
		if (L != R) for(int i=0;i<2;i++) lazy[2*ind+i] = lazy[ind]; /// prop to children
		lazy[ind] = -1; 
	} // recalc values for current node
	void pull(int ind){seg[ind]=cmb(seg[2*ind],seg[2*ind+1]);}
	void build() { for(int i=SZ-1;i>=1;i--) pull(i); }
	void upd(int lo,int hi,T inc,int ind=1,int L=0, int R=SZ-1) {
		push(ind,L,R); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) { 
			lazy[ind] = inc; push(ind,L,R); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M); 
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	T query(int lo, int hi, int ind=1, int L=0, int R=SZ-1) {
		push(ind,L,R); if (lo > R || L > hi) return ID;
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2; return cmb(query(lo,hi,2*ind,L,M),
			query(lo,hi,2*ind+1,M+1,R));
	}
};

vector<pii> sw;
int hop[200005][20];
int tout[200005], pos[200005]; // inc inc

int up(int u,int k) {
	for(int i=0;i<19;i++){
		if(k&(1ll<<i))u=hop[u][i];
	}
	return u;
}

template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N;
	int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
	vector<int> rpos; // rpos not used but could be useful
	void dfsSz(int x) { 
		sz[x] = 1; 
		for(auto &y:adj[x]) {
			par[y] = x; depth[y] = depth[x]+1;
			sw.emplace_back(x,y);
			adj[y].erase(find(all(adj[y]),x)); /// remove parent from adj list
			dfsSz(y); sz[x] += sz[y];
			if (sz[y] > sz[adj[x][0]]) swap(y,adj[x][0]);
		}
	}
	void dfsHld(int x) {
		pos[x] = ti++; rpos.push_back(x);
		for(auto &y:adj[x]) {
			root[y] = (y == adj[x][0] ? root[x] : y);
			dfsHld(y); }
	}
	void init(int _N, int R = 0) { N = _N; 
		par[R] = depth[R] = ti = 0; dfsSz(R);
		root[R] = R; dfsHld(R); 
		dbg(rpos);
	}
	int lca(int x, int y) {
		for (; root[x] != root[y]; y = par[root[y]])
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
		return depth[x] < depth[y] ? x : y;
	}
	int dist(int x, int y) { // # edges on path
	 	return depth[x]+depth[y]-2*depth[lca(x,y)]; }
	LazySeg<int,SZ> tree; // segtree for sum
	template <class BinaryOp>
	void processPath(int x, int y, BinaryOp op) {
		for (; root[x] != root[y]; y = par[root[y]]) {
			if (depth[root[x]] > depth[root[y]]) swap(x,y);
			op(pos[root[y]],pos[y]); }
		if (depth[x] > depth[y]) swap(x,y);
		op(pos[x]+VALS_IN_EDGES,pos[y]); 
	}
	void modifyPath(int x, int y, int v) { 
		dbg("MOD", x,y);
		processPath(x,y,[this,&v](int l, int r) {
			tree.upd(l,r,v); }); }
	int queryPath(int x, int y) { 
		int res = 0; processPath(x,y,[this,&res](int l, int r) {
			res += tree.query(l,r); });
		dbg("QUERY",x,y, res);
		return res; }
	void modifySubtree(int x, int v) { 
		tree.upd(pos[x]+VALS_IN_EDGES,pos[x]+sz[x]-1,v); }
};


int32_t main() {
	dbg("HI");
        cin >> N >> K;
        for (int i = 0; i < N - 1; i++) {
                int a;
                cin >> a;
                adj[a].push_back(i + 2);
                adj[i + 2].push_back(a);
        }
	vector<vector<int>> stuff(N+4,vector<int>());
        for (int i = 0; i < K; i++) {
                int a, b;
                cin >> a >> b;
                p.push_back({min(a, b),max(a, b)});
		stuff[a].push_back(b);
		stuff[b].push_back(a);
        }
        int ans = 0;
        int root = 1;
	for(;root<=N;root++){
		if(adj[root].size()==1)break;
	}
	HLD<(1ll<<18),true> tree;
	tree.init(N, root);
	dbg("HLD INITIALISED");
	vector<pii> idk;
        sort(p.begin(), p.end());
	for(int i=0;i<K-1;i++){
		if(p[i]==p[i+1]){
			ans=max(ans,tree.dist(p[i].f,p[i].s));
		} else {
			idk.emplace_back(p[i]);
		}
	}
	idk.emplace_back(p[K-1]);
	p=idk;
	vector<int> tin(N+4,0),tout(N+4,0);
	int cnt=0;
	function<void(int,int)> dfs=[&](int u, int p) {
		tin[u]=cnt++;
		for(int i : adj[u]){
			if(i!=p)dfs(i,u);
		}
		tout[u]=cnt++;
	};
	dfs(root,0);
	vector<int> nodes;
	for(int i=1;i<=N;i++)nodes.push_back(i);
	sort(all(nodes), [&](int a, int b) {
		return tout[a]<tout[b];
	});
	set<pii> s;
	for(int u : nodes) {
		for(int v : stuff[u]) {
			if(s.find(make_pair(u,v))!=s.end())continue;
			ans=max(ans, tree.queryPath(u,v));
			tree.modifyPath(u,v,1);
			s.insert(make_pair(u,v));
			s.insert(make_pair(v,u));
		}
	}
	cout<<ans<<"\n";
}
