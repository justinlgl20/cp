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

void solve() {
	int n;cin>>n;
	vector<int>a(n);
	int ans=0;
	for(int i=0;i<n;i++){cin>>a[i];ans+=a[i];}
	ans=ans;
	while (a.size()>1) {
		vector<int>ne(a.size()-1ll);
		int x=0;
		for(int i=1;i<a.size();i++){
			ne[i-1]=a[i]-a[i-1];
			x+=ne[i-1];
		}
		ans=max(ans,abs(x));
		a=ne;
	}
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
