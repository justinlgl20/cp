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
	vector<vector<int>>a(n,vector<int>(n,0));
	vector<int> until(n,0);
	for(int i=0;i<n;i++){
		for(int j=n-1;j>=0;j--)cin>>a[i][j];
		for(;until[i]<n and a[i][until[i]]==1;until[i]++){}
	}
	sort(all(until));
	reverse(all(until));
	int ans=0;
	while (until.size()){
		if(until.back()>=ans){
			ans++;
			until.pop_back();
		} else {
			until.pop_back();
		}
	}
	cout<<ans<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
