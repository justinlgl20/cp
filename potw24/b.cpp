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

int dp[10000005];

int32_t main() {
	int n,a,b;cin>>n>>a>>b;
	dp[0]=1;
	for(int i=0;i<=n;i++){
		if(dp[i])dp[i+a]=1,dp[i+b]=1;
	}
	for(int i=0;i<=n;i++){
		if(dp[i])dp[i/2]=1;
	}
	for(int i=0;i<=n;i++){
		if(dp[i])dp[i+a]=1,dp[i+b]=1;
	}
	for(int i=n;i>=0;i--){
		if(dp[i]){
			cout<<i<<"\n";return 0;
		}
	}
}
