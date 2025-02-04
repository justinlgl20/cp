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
	int n,k;cin>>n>>k;
	dbg(n,k);
	vector<int> a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	if(k==n){
		int ans=0;
		for(int i=1;i<n;i+=2){
			if(a[i]==ans+1){
				ans++;
			} else {
				cout<<ans+1<<"\n";
				return;
			}
		}
		cout<<ans+1<<"\n";
		return;
	}
	set<int> s;
	int ew=n-(k-1)-1;
	// we can start at anywhere between 1 and ew
	dbg(1,ew);
	for(int i=1;i< n;i++){
		if(n-i-1 >= k-2)
			s.insert(a[i]);
	}
	if(s.size()>1 or (*s.begin())!=1){
		cout<<1<<"\n";
	} else{
		cout<<2<<"\n";
	}
}

int32_t main() {
	int t;cin>>t;while(t--)solve();
}
