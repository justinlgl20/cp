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
int tin[200005],tout[200005], pos[200005]; // inc inc
 
int up(int u,int k) {
	for(int i=0;i<19;i++){
		if(k&(1ll<<i))u=hop[u][i];
	}
	return u;
}
 
template<int SZ, bool VALS_IN_EDGES> struct HLD { 
	int N;
	int par[SZ], root[SZ], depth[SZ], sz[SZ], ti;
	vector<int> adj[SZ];
	void ae(int u,int v){
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
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
HLD<(1ll<<18),true> tree;

bool is_ancestor(int u, int v){
	return tin[u]<=tin[v] and tout[v]<=tout[v];
}
vector<int> cadj[200005];
void aux_tree(vector<int> &nodes) {
	sort(all(nodes),[&](int i, int j) {return tin[i]<tin[j];});
	nodes.resize(unique(all(nodes))-nodes.begin());
	for(int i=0;i<nodes.size()-1;i++){
		cadj[nodes[i]].clear();
		int p=tree.lca(nodes[i],nodes[i+1]);
		cadj[p].clear();
		nodes.emplace_back(p);
	}
	cadj[nodes.size()-1].clear();
	sort(all(nodes),[&](int i, int j) {return tin[i]<tin[j];});
	nodes.erase(unique(all(nodes)),nodes.end());
	vector<int> s;
	s.push_back(nodes[0]);
	for(int i=1;i<nodes.size();i++){
		int v=nodes[i];
		while(s.size()>=2 and !is_ancestor(s.back(),v)){
			cadj[s[s.size()-2]].emplace_back(s.back());
			s.pop_back();
		}
		s.push_back(v);
	}
	while (s.size()>=2){
		cadj[s[s.size()-2]].emplace_back(s.back());
		s.pop_back();
	}
	// generated cadj
}
 
 
int32_t main() {
	dbg("HI");
        cin >> N >> K;
        int root = 1;
        for (int i = 0; i < N - 1; i++) {
                int a;
                cin >> a;
                adj[a].push_back(i + 2);
		tree.ae(a,i+2);
                adj[i + 2].push_back(a);
        }
	tree.init(N, root);
	dbg("HLD INITIALISED");
        for (int i = 0; i < K; i++) {
                int a, b;
                cin >> a >> b;
                p.push_back({min(a, b),max(a, b)});
        }
        int ans = 0;
        sort(p.begin(), p.end());
	vector<pii> idk;
        for (int i = 0; i < K - 1; i++) {
                if (p[i].f == p[i + 1].f && p[i].s == p[i + 1].s) {
                        ans = max(ans, tree.dist(p[i].f, p[i].s));
                } else{
			idk.push_back(p[i]);
		}
        }
	idk.push_back(p[K-1]);
	p=idk;
	int cnt=0;
	function<void(int,int)> dfs=[&](int u, int p) {
		tin[u]=cnt++;
		for(int i : adj[u]){
			if(i!=p)dfs(i,u);
		}
		tout[u]=cnt++;
	};
	dfs(root,0);
	
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
					hop[c][0]=v;
					for(int i=1;i<=19;i++)hop[c][i]=hop[hop[c][i-1]][i-1];
                                        st.push(c);
                                }
                        }
                }
        }
	dbg("HI");
        vector < pii > paths[N + 1];
        for (int i = 0; i < (int)p.size(); i++) {
                int a = p[i].first;
                int b = p[i].second;
                paths[tree.lca(a, b)].push_back({a,b}); // this bit
        }
	dbg("HI");
        for (int v: dfs_order) {
                for (pii p: paths[v]) {
                        ans = max(ans, tree.queryPath(p.first, v));
                        ans = max(ans, tree.queryPath(p.second, v));
		}
		for(pii p: paths[v]) {
			tree.modifyPath(p.first, p.second, 1);
                }
	}
 
	dbg("SECOND STAGE");
	// DONE EVERYTHING WHERE PATHS AREN'T SAME LCA
	vector<vector<pii>> things(N + 3, vector<pii>());
	vector<vector<pii>> things2(N + 3, vector<pii>());
	tree.modifySubtree(root,0);
	for(int v: dfs_order) {
		for (pii p : paths[v]){
			if(p.f != v and p.s != v) {
				int c=up(p.f, tree.depth[p.f]-tree.depth[v]-1ll);
				things[c].emplace_back(p);
			}
			swap(p.f,p.s);
			if(p.f != v and p.s != v) {
				int c=up(p.f, tree.depth[p.f]-tree.depth[v]-1ll);
				things[c].emplace_back(p);
			}
		}
		for (pii p : paths[v]){
			if(p.f != v) {
				int c=up(p.f, tree.depth[p.f]-tree.depth[v]-1ll);
				things2[c].emplace_back(p);
			}
			swap(p.f,p.s);
			if(p.f != v) {
				int c=up(p.f, tree.depth[p.f]-tree.depth[v]-1ll);
				things2[c].emplace_back(p);
			}
		}
 
		for(int i : adj[v]) {
			if(i == par[v])continue;
			tree.modifySubtree(v,0);
			for(auto j : things2[i]) {
				ans=max(ans, tree.queryPath(j.f,v));
				tree.modifyPath(j.f,v,1);
			}
		}
		for(int i : adj[v]) {
			// do by pairs of children
			unordered_map<int, vector<pii>> idk;
			dbg(i);
			for(auto p : things[i]) {
				dbg(p.f,p.s);
				// i is first child
				int sec = up(p.s, tree.depth[p.s]-tree.depth[v]-1);
				idk[sec].emplace_back(p);
			}
			for(auto &j : idk) {
				unordered_map<int, vector<int>> pairs;
				// two children are j.f and i
				// p.s is under j.f and p.f is under i where p is in j.s
				dbg(j.f, i);
				// j.s stores all the pairs of paths that pass through v. 
				// now lets build an aux tree to dfs on
				int best=0; // best stores the overlap of best pair of paths from v to i then to some other places. 
				vector<int> stuff = {v, j.f, i};
				for(auto i : j.s) {
					pairs[i.s].push_back(i.f);
					pairs[i.f].push_back(i.s);
					stuff.push_back(i.f);
					stuff.push_back(i.s);
				}
				// NOW BUILD AUX TREE ON STUFF
				// then dfs down from sec and hld stuff on i's subtree
				tree.modifySubtree(v,0);
				aux_tree(stuff);
				int b=0;
				function<void(int,int)> dfs=[&](int u, int p) {
					// edge above u is the last edge
					for(int v:cadj[u]){
						if(v!=p)dfs(v,u);
					}
					// add edges that are from u
					// todo add children's thingies into hld
					// do child with most paths last
				};
				dfs(j.f, i);
				ans=max(ans,b);
			}
		}
	}
 
        cout << ans << "\n";
 
}
