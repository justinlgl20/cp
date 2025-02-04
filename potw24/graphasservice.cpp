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

struct graph {
    vector<vector<pii>> adj;
    int n;
    graph(int n) {
        this->n = n;
        adj.resize(n+4);
        for(int i=0;i<n+3;i++)adj[i].clear();
    }
    void ae(int u, int v, int w) {
        adj[u].emplace_back(v,w);
    }
    vector<int> dikstra(int s) {
        vector<int> dist(n+4,1e18);
        dist[s]=0;
        priority_queue<pii> q;
        q.push(make_pair(0,s));
        while (q.size()) {
            int u=q.top().s;
            int w=-q.top().f;
            q.pop();
            if(w>dist[u])continue;
            for(auto i:adj[u]){
                if(i.s+dist[u] < dist[i.f]){
                    dist[i.f]=i.s+dist[u];
                    q.push(make_pair(-dist[i.f], i.f));
                }
            }
        }
        return dist;
    }
};

int32_t main() {
	int n,m;cin>>n>>m;
	graph t = graph(n+4);
	vector<pair<int,pii>>edges;
	for(int i=0;i<m;i++){
		int u,v,w;
		cin>>u>>v>>w;edges.emplace_back(w,make_pair(v,u));
		t.ae(u,v,w);
		t.ae(v,u,w);
	}
	for(auto i:edges){
		dbg(i.f, i.s.f,i.s.s,t.dikstra(i.s.f)[i.s.s]);
		if(t.dikstra(i.s.f)[i.s.s]!=i.f){
			cout<<"Impossible\n";
			return 0;
		}
	}
	cout<<edges.size()<<"\n";
	for(auto i:edges){
		cout<<i.s.f<<" "<<i.s.s<<" "<<i.f<<"\n";
	}
}
