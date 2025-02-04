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

template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N;
	int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
	int pos[SZ]; vector<int> rpos; // rpos not used but could be useful
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
		processPath(x,y,[this,&v](int l, int r) {dbg(l,r);
			tree.upd(l,r,v); }); }
	int queryPath(int x, int y) { 
		dbg("QUERY",x,y);
		int res = 0; processPath(x,y,[this,&res](int l, int r) {dbg(l,r);
			res += tree.query(l,r); });
		dbg(res);
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
        for (int i = 0; i < K; i++) {
                int a, b;
                cin >> a >> b;
                p.push_back({
                        min(a, b),
                        max(a, b)
                });
        }
        int ans = 0;
        sort(p.begin(), p.end());
        //int root = 1;
	int x=1e18;
	for(int root=1;root<=N;root++) {
		HLD<(1ll<<12),true> tree;
		tree.init(N, root);
		dbg("HLD INITIALISED");
		for (int i = 0; i < K - 1; i++) {
			if (p[i].f == p[i + 1].f && p[i].s == p[i + 1].s) {
				ans = max(ans, tree.dist(p[i].f, p[i].s));
			}
		}
		vector < int > dfs_order;
		stack < int > st;
		vector < int > par(N + 1, 0);
		vector < bool > visited(N + 1, false);
		st.push(root);
		while (!st.empty()) {
			int v = st.top();
			st.pop();
			if (!visited[v]) {
				dfs_order.push_back(v);
				visited[v] = true;
				for (int c: adj[v]) {
					if (!visited[c]) {
						par[c]=v;
						st.push(c);
					}
				}
			}
		}
		dbg("HI");
		vector < pii > paths[N + 1];
		for (int i = 0; i < K; i++) {
			int a = p[i].first;
			int b = p[i].second;
			paths[tree.lca(a, b)].push_back({a,b}); // this bit
		}
		int y=0;
		dbg("HI");
		for (int v: dfs_order) {
			y=max(y, (int)paths[v].size());
			for (pii p: paths[v]) {
				ans = max(ans, tree.queryPath(p.first, v));
				ans = max(ans, tree.queryPath(p.second, v));
			}
			for(pii p: paths[v]) {
				tree.modifyPath(p.first, p.second, 1);
			}
		}
		x = min(x, y);
		dbg(root, ans);
		for (auto i : sw) {
			adj[i.s].push_back(i.f);
		}
		sw.clear();
	}
	cout<<x<<"\n";
	vector<vector<pii>> things(N + 3, vector<pii>());

}
