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

const int MOD = 1000000007;

vector<pii> adj[100005];
int n, m;

void dickstra(int s, vector<int>&d,vector<int>&ways) {
	d.assign(n+4,1e9);
	ways.assign(n+4,0);
	d[s]=0;
	ways[s]=1;
	priority_queue<pii> q;
	q.push(make_pair(0, s));
	while(q.size()){
		int u = q.top().s,di=-q.top().f;
		q.pop();
		if (di > d[u])continue;
		for(auto i : adj[u]){
			if(di+i.s<d[i.f]){
				d[i.f]=di+i.s;
				ways[i.f]=ways[u];
				ways[i.f]%=MOD;
				q.push(make_pair(-d[i.f], i.f));
			} else if (di+i.s==d[i.f]) {
				ways[i.f]+=ways[u];
				ways[i.f]%=MOD;
			}
		}
	}
}

int32_t main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v,w;cin>>u>>v>>w;
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
	}
	vector<int>dist_1,dist_2,d,ways1,ways2,w;
	dickstra(1,dist_1,ways1);
	dickstra(2,dist_2,ways2);
	dickstra(n,d,w);
	dbg(dist_1);
	dbg(ways1);
	dbg(dist_2);
	dbg(d);
	vector<pii> anses;
	for(int i=1;i<=n;i++){
		if (dist_1[i]==dist_2[i] and dist_1[i]+d[i]==dist_1[n] and dist_2[i]+d[i]==dist_2[n]) {
			// i works
			dbg(i, d[i]);
			anses.emplace_back(d[i], i);
		}
	}
	if (anses.size() == 0) {
		cout << "0\n";
		cout << ((ways1[n]*ways2[n])%MOD) << "\n";
		return 0;
	}
	sort(all(anses));
	int ans = anses[anses.size()-1].f;
	cout << ans << "\n";
	int fans = 0;
	for (int i = anses.size()-1; i >=0 and anses[i].f==ans; i--) {
		fans+=( ((ways1[anses[i].s]*ways2[anses[i].s])%MOD)*w[anses[i].s])%MOD;
		fans%=MOD;
	}
	if (ans == 0) fans = ways1[n]*ways2[n];
	fans%=MOD;
	cout << fans<<"\n";

}
