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

int dp[100005][3];

int32_t main() {
	int n;cin>>n;
	for(int i=0;i<n;i++)cin>>dp[i][0]>>dp[i][1]>>dp[i][2];
	for(int i=1;i<n;i++){
		for(int j=0;j<3;j++){
			int m=0;
			for(int k=0;k<3;k++)if(k!=j)m=max(m,dp[i-1][k]);
			dp[i][j]+=m;
		}
	}
	cout<<max(dp[n-1][0],max(dp[n-1][1],dp[n-1][2]))<<"\n";
}
