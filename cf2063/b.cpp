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
	int t;cin>>t;
	while(t--){
		int n,l,r;cin>>n>>l>>r;
		vector<int>a(n+3);
		for(int i=1;i<=n;i++)cin>>a[i];
		// inc inc
		int ans=1e18;
		vector<int> v;
		for(int i=l;i<= n;i++){
			v.push_back(a[i]);
		}
		int b=0;
		sort(all(v));
		for(int i=0;i<r-l+1;i++)b+=v[i];
		v.clear();
		for(int i=1;i<=r;i++)v.push_back(a[i]);
		sort(all(v));
		int aw=0;
		for(int i=0;i<r-l+1;i++)aw+=v[i];
		ans=min(aw,b);
		cout<<ans<<"\n";
	}
}
