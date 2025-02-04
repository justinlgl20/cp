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

int v[100005][11]; // node n, taking i

struct thing {
	int taken;
	int i, j;
	int val;
	thing(int q, int w) {
		i=q, j=w;
		val = v[i][j];
		taken=0;
	}
	bool operator<(thing&other) const {
		return val*other.j < other.val*j;
	}
};

struct comp {
	bool operator()(thing const&a, thing const&b){
		if(a.val*b.j < b.val*a.j) return false;
		if(a.val*b.j == b.val*a.j) {
			// which one now
		}
		return true;
	}
};

void solve() {
	int n,m,k;cin>>n>>m>>k;
	vector<int>a(n),b(m);
	int ans=0;
	for(int i=0;i<n;i++){cin>>a[i]; ans+=a[i];}
	sort(all(a));
	for(int i=0;i<m;i++)cin>>b[i];
	vector<vector<int>> active(m+1, vector<int>());
	for(int i=0;i<(1ll<<m);i++){
		int a=(1ll<<31)-1;
		for(int j=0;j<m;j++){
			if(i&(1ll<<j))a=a&(b[j]);
		}
		active[__builtin_popcount(i)].push_back(a);
	}
	dbg("HI");
	priority_queue<thing, vector<thing>, comp> q;
	for(int i=0;i<n;i++){
		for(int j=1;j<=m;j++){
			int best=1e18;
			for(auto k:active[j]){
				best=min(best,a[i]&k);
			}
			int val=-a[i]+best;
			int cost=j;
			v[i][j]=val;
			dbg(i, j, v[i][j]);
			q.push(thing(i, j));
		}
	}
	cout<<ans<<"\n";


}

int32_t main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int t;cin>>t;
	while(t--)solve();
}
