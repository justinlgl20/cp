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

int32_t main() {
	int n,k;cin>>n>>k;set<int>g;
	for(int i=0;i<n;i++){
		int a;cin>>a;
		bool w=0;
		if(g.lower_bound(a)!=g.end()){
			int q=*g.lower_bound(a);
			dbg(q);
			if(q-a <=k)w=1;
		}
		auto e=g.lower_bound(a);
		if(e!=g.begin()){
			e--;
			dbg(*e);
			if(a-(*e) <= k)w=1;
		}
		if(w)cout<<"YES\n";
		else cout<<"NO\n";
		g.insert(a);
	}
}
