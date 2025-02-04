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


int solve(vector<int> &v) {
	int n=v.size();
	vector<int>dp(n+3,0);
	for(int i=1;i<n;i++){
		if(i>2)
			dp[i] = dp[i-2]+max(v[i]+v[i-1], 0ll);
		else
			dp[i]=max(v[i]+v[i-1],0ll);
		dp[i]=max(dp[i],dp[i-1]);
		dbg(i, dp[i]);
	}
	return dp[n-1];
}

int32_t main() {
	int r,c;cin>>r>>c;
	vector<vector<int>> s(r,vector<int>(c,0));
	vector<vector<int>> q(c,vector<int>(r,0));
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){cin>>s[i][j];q[j][i]=s[i][j];}
	}
	int ans=0;
	for(int i=0;i<r;i++){
		ans+=solve(s[i]);
	}
	for(int i=0;i<c;i++){
		ans+=solve(q[i]);
	}
	cout<<ans<<"\n";
}
