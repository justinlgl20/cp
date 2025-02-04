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

struct dsu {
	vector<int> p;
	dsu(int n) {
		p.resize(n+4);
		for(int i=0;i<=n+3;i++)p[i]=i;
	}
	int rep(int u) {
		if(p[u]==u)return u;
		return p[u]=rep(p[u]);
	}
	void merge(int a, int b) {
		a=rep(a),b=rep(b);
		p[a]=b;
	}
};

int32_t main(){
	int n, m;cin>>n>>m;
	vector<pii> edges;
	for(int i=0;i<m;i++){
		int u,v;cin>>u>>v;
		edges.emplace_back(u,v);
	}
	vector<pair<int,pii>> ed;
	for(auto i:edges){
		cout<<"? "<<i.f<<" "<<i.s<<"\n"<<flush;
		int x;cin>>x;
		ed.emplace_back(x, i);
	}
	dsu uf=dsu(n);
	int ans=0;
	sort(all(ed));
	for (auto j : ed) {
		auto i=j.s;
		if (uf.rep(i.f)!=uf.rep(i.s)){
			uf.merge(i.f,i.s);
			ans+=j.f;
		}
	}
	cout<<"! "<<ans<<"\n";
}
