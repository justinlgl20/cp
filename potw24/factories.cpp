#include <bits/stdc++.h>
using namespace std;
 
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

// SOURCED FROM https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/data-structures/DynaCon.h

constexpr int MAX_N = 1e5+5, MAX_M = 1e5+5;
int N;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
#define sz(x) int((x).size())
const int MOD=(int)1e9+7;
template<int SZ> struct Treap {
	int cnt, pri[SZ], par[SZ], sz[SZ]; // ETT node for each edge
	bitset<SZ> specialNode, existsSpecialNode;
	bitset<SZ> specialEdge, existsSpecialEdge;
	int edgeId[SZ];
	array<int,2> c[SZ];
	int makeEdge(int label) {
		edgeId[++cnt] = label; pri[cnt] = rng(); sz[cnt] = 1;
		return cnt;
	}
	void calc(int x) {
		int a = c[x][0], b = c[x][1];
		sz[x] = 1+sz[a]+sz[b];
		existsSpecialNode[x]=specialNode[x]|existsSpecialNode[a]|existsSpecialNode[b];
		existsSpecialEdge[x]=specialEdge[x]|existsSpecialEdge[a]|existsSpecialEdge[b];
	}
	int extractSpecialEdge(int x) {
		int a = c[x][0], b = c[x][1], res;
		assert(existsSpecialEdge[x]);
		if (specialEdge[x]) {
			res = edgeId[x], specialEdge[x] = 0;
		} else if (existsSpecialEdge[a]) res = extractSpecialEdge(a);
		else res = extractSpecialEdge(b);
		assert(res >= 0); calc(x); return res;
	}
	int extractSpecialNode(int x) {
		assert(existsSpecialNode[x]);
		int a = c[x][0], b = c[x][1];
		if (specialNode[x]) return x;
		if (existsSpecialNode[a]) return extractSpecialNode(a);
		return extractSpecialNode(b);
	}
	int getRoot(int x) { // get top node in ETT
		while (par[x]) x = par[x];
		return x;
	}
	bool con(int a, int b) { return getRoot(a) == getRoot(b); }
	void link(int x, int d, int y) { // set d-th child of x to y
		assert(x); assert(d == 0 || d == 1);
		assert(!c[x][d]), c[x][d] = y; 
		if (y) assert(!par[y]), par[y] = x;
		calc(x);
	}
	int dis(int x, int d) { // disconnected d-th child of x
		assert(x); assert(d == 0 || d == 1);
		int y = c[x][d]; c[x][d] = 0; calc(x);
		if (y) assert(par[y] == x), par[y] = 0;
		return y;
	}
	pii split(int x) { // x and everything to right goes in p.s
		// everything else goes in p.f
		pii p = {dis(x,0),x};
		while (par[x]) {
			int y = par[x];
			if (c[y][0] == x) {
				dis(y,0), link(y,0,p.s),  p.s = y;
			} else {
				assert(c[y][1] == x);
				dis(y,1), link(y,1,p.f); p.f = y;
			}
			x = y;
		}
		assert(!par[p.f] && !par[p.s]); return p;
	}
	int merge(int x, int y) {
		assert(!par[x] && !par[y]);
		if (!x || !y) return max(x,y);
		if (pri[x] > pri[y]) {
			int X = dis(x,1);
			link(x,1,merge(X,y));
			return x;
		} else {
			int Y = dis(y,0);
			link(y,0,merge(x,Y));
			return y;
		}
	}
	int getFirst(int x) {
		if (!x) return 0;
		while (c[x][0]) x = c[x][0];
		return x;
	}
	int makeFirst(int x) { // rotate ETT of x such that x is first
		assert(x); pii p = split(x); return merge(p.s,p.f); }
	void remFirst(int x) { // remove first node of ETT rooted at x
		assert(x && !par[x]);
		while (c[x][0]) x = c[x][0];
		int y = dis(x,1), p = par[x];
		if (p) dis(p,0), link(p,0,y);
		while (p) {
			calc(p);
			p = par[p];
		}
	}
	int reroot(int x) { 
		assert(1 <= x && x <= N); return makeFirst(x); }
	void markSpecialNode(int x, int val) {
		if (specialNode[x] == val) return;
		for(specialNode[x]=val;x;x=par[x]) 
			calc(x);
	}
};


vector<pii> ed; vector<int> edgeLevel; vector<bool> span; // vertices which edge connects, level of edge, whether edge is part of spanning tree
struct ETT {
	Treap<MAX_N+2*MAX_M> T;
	int level; // level of ETT, 0 to log(N)
	vector<pii> nonSpan[MAX_N]; // list of non-spanning edges adjacent to each vertex
	pii edgeNodes[MAX_M]; // list of spanning edges
	int spanEdges;
	void init(int _level) {
		level = _level; 
		for(int i=0;i<N;i++) T.makeEdge(-1);
	}
	bool con(int a, int b) { return T.con(a,b); }
	bool add(int label) {
		assert(level <= edgeLevel[label]);
		int a = ed[label].f, b = ed[label].s;
		if (con(a,b)) {
			assert(!span[label]);
			nonSpan[a].push_back({label,b}), nonSpan[b].push_back({label,a});
			T.markSpecialNode(a,1), T.markSpecialNode(b,1); 
			return 0;
		} else {
			spanEdges ++;
			span[label] = 1;
			int ta = T.reroot(a), tb = T.reroot(b); 
			if (ta||tb) assert(ta != tb);
			int x = T.makeEdge(label), y = T.makeEdge(label);
			edgeNodes[label] = {x,y};
			if (level == edgeLevel[label]) {
				T.specialEdge[x] = T.existsSpecialEdge[x] = 1;
			}
			T.merge(T.merge(ta,x),T.merge(tb,y));
			return 1;
		}
	}
	void rem(int label) { // remove smth that's in the spanning tree
		int x,y; tie(x,y) = edgeNodes[label]; assert(x && y);
		T.makeFirst(x);
		pii p = T.split(y); assert(T.getFirst(p.f) == x && T.getFirst(p.s) == y);
		T.remFirst(p.f), T.remFirst(p.s); spanEdges --;
	}
	pair<vector<int>,int> replace(int x, int y) {
		// dbg("FIND REPLACEMENT",level,x,y);
		x = T.getRoot(x), y = T.getRoot(y); // try to find replacement edge for (x,y)
		if (T.sz[x] > T.sz[y]) swap(x,y); // loop over smaller component
		pair<vector<int>,int> res = {{},-1};
		while (T.existsSpecialEdge[x]) {
			// increase levels of all spanning tree edges
			int ind = T.extractSpecialEdge(x);
			assert(edgeLevel[ind] == level); 
			res.f.push_back(ind); edgeLevel[ind] ++;
		}
		while (T.existsSpecialNode[x]) {
			int t = T.extractSpecialNode(x);
			while (sz(nonSpan[t])) {
				pii u = nonSpan[t].back(); nonSpan[t].pop_back();
				if (edgeLevel[u.f] > level || span[u.f]) continue; // outdated information
				assert(edgeLevel[u.f] == level);
				int r = T.getRoot(u.s); 
				assert(r == x || r == y);
				if (r == y) { res.s = u.f; return res; } // wow done!
				res.f.push_back(u.f); edgeLevel[u.f] ++;
			}
			T.markSpecialNode(t,0);
		}
		return res;
	}
};

struct DynaCon {
	ETT E[17]; void init() { for(int i=0;i<17;i++) E[i].init(i); }
	bool con(int a, int b) { return E[0].con(a,b); }
	map<pii,vector<int>> edges;
	void add(int a, int b) { // add an edge
		if (a > b) swap(a,b);
		// dbg("add",a,b);
		int label = sz(ed);
		ed.push_back({a,b}); edgeLevel.push_back(0); span.push_back(0);
		edges[{a,b}].push_back(label); 
		E[0].add(label);
	}
	void rem(int a, int b) { // remove an edge
		if (a > b) swap(a,b);
		vector<int>& edgeLabels = edges[{a,b}]; assert(sz(edgeLabels));
		int label = edgeLabels.back(); edgeLabels.pop_back();
		REM(label);
	}
	void REM(int label) {
		int L = edgeLevel[label]; edgeLevel[label] = MOD;
		if (!span[label]) return;
		for(int i=0;i<L+1;i++) E[i].rem(label); // remove from spanning tree
		while (L >= 0) {
			pair<vector<int>,int> p = E[L].replace(ed[label].f,ed[label].s);
			for(auto t:p.f) {
				assert(edgeLevel[t] == L+1);
				if (span[t]) assert(E[L+1].add(t));
				else {
					assert(!E[L+1].add(t));
				}
			}
			if (p.s != -1) { // found a replacement edge!
				assert(!span[p.s]);
				for(int i=0;i<L+1;i++) assert(E[i].add(p.s));
				assert(span[p.s]);
				return;
			}
			L --;
		}
	}
};
DynaCon D;

priority_queue<int> things;
int a[200005],b[200005];
bool works[200005];
int32_t main() {
	cin>>N;
	N+=3;
	D.init();
	int spec=100001;
	for(int i=1;i<=N;i++){
		works[i]=1e9;
		D.add(i,spec);
	}
	int q;cin>>q;
	vector<pair<char,pii>> s;
	for(int i=0;i<q;i++){
		char c;cin>>c;
		int a,b;
		if(c=='A')cin>>a>>b;
		else if (c=='D')cin>>a;
		else{
			int r;cin>>r;
			a=::a[r];b=::b[r];
		}
		s.push_back(make_pair(c,make_pair(a,b)));
	}
	int cnt=1;
	for(int i=0;i<q;i++) {
		
	}
}
