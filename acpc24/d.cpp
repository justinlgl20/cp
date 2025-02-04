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
	int n;cin>>n;
	vector<int>a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	int fans=0;
	multiset<pii>use; // number then index
	int ans=0;
	multiset<pii>available;
	for (int i=0;i<n;i++){
		available.insert(make_pair(a[i],i));
	}
	for (int i=1;i<=n;i++){
		// this is how many elements we are taking
		if (available.find(make_pair(a[n-i],n-i))!=available.end()) {
			available.erase(available.find(make_pair(a[n-i], n-i)));
		} else {
			use.erase(use.find(make_pair(a[n-i], n-i)));
			ans-=a[n-i];
		}
		while (available.size() and use.size() < i) {
			pii u = *(available.rbegin());
			available.erase(available.find(u));
			ans+=u.f;
			use.insert(u);
		}
		dbg(i,ans);
		fans = max(fans,ans);
	}
	cout<<fans<<"\n";
}
