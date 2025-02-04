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

const int MOD=1e9+7;

void solve() {
	int n,k;cin>>n>>k;
	assert(k<=1);
	vector<int> factorial(n+4, 1);
	for(int i=1;i<n+3;i++)factorial[i]=(factorial[i-1]*i)%MOD;
	vector<char> idk(n+4);
	idk[0]='.';
	for(int i=1;i<=n;i++)cin>>idk[i];
	vector<vector<int>> adj(n+4,vector<int>(n+4,0));
	dbg("HI");
	auto dp=adj;
	int s=0,e=0; // get backedge
	vector<int> out(n+4,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;cin>>c;
			adj[i][j]=(c=='1');
			out[i]+=(c=='1');
			if(c=='1' and i>j) s=i,e=j;
		}
	}
	dbg("HI");
	dbg(s,e);;
	dp[0][e]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++){
			if(dp[i-1][j] != 0) {
				if(i==j){
					dbg(i, "DEG:",out[i]+(idk[i]=='R'));
					int add =dp[i-1][j]*factorial[out[i]+(idk[i]=='R')-1ll];
					add%=MOD;
					dbg(i,j,add);
					if(j==s) {
						// this works
						dp[i][0]+=(int)(((out[i]+(idk[i]=='R'))-1ll)*add)%MOD;
						dp[i][0]%=MOD;dp[i][0]+=MOD; dp[i][0]%=MOD;
					}
					else if (idk[j]=='R'){
						dp[i][0]+=add;
						dp[i][0]%=MOD;
					} // transition from dp[i-1][j] to dp[i][0] if there is a receiver
					if(j!=s) { // transition from dp[i-1][j] to dp[i][k] if k>j and there is an edge from j to k
						for(int k=i+1;k<=n;k++)if(adj[j][k]){dp[i][k]+=add;dp[i][k]%=MOD;}
					}
				} else {dp[i][j]+=(dp[i-1][j]*factorial[out[i]+(idk[i]=='R')])%MOD;dp[i][j]%=MOD;dp[i][j]+=MOD; dp[i][j]%=MOD;}
			}
			dp[i][j]%=MOD;
			dbg(i, j, dp[i][j]);
		}
	}
	cout<<dp[n][0]<<"\n";

}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
