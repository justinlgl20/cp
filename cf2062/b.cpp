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
	for(int i=0;i<n;i++)cin>>a[i];
	bool works = true;
	for(int i=0;i<n;i++){
		//i is amount to left
		// n-i-1
		if(a[i] < i*2+1ll)works=false;
		if(a[i] < (n-i-1ll)*2+1ll)works=false;
	}
	if(works){
		cout<<"Yes\n";
	} else {
		cout<<"No\n";
	}
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
