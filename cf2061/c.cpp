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

const int MOD=998244353;

void solve() {
	int n;cin>>n;
	vector<int> a(n);
	vector<int>dp(n+4,0);
	for(int i=0;i<n;i++){cin>>a[i];}
	vector<int>s(n+4,0);
	if(a[0]==0)dp[0]=1;
	if((a[1]==0 and a[0]==0) or (a[1]==1)) dp[1]=1;
	for(int i=2;i<n;i++){
		if(i>0 and a[i-1]==a[i]) dp[i]+=dp[i-1];
		dp[i]%=MOD;
		if(i>1 and a[i-2]==a[i]-1ll) dp[i]+=dp[i-2];
		dp[i]%=MOD;
	}
	for(int i=0;i<n;i++){
		dbg(i, dp[i]);
	}
	int ans=dp[n-1];
	ans%=MOD;
	if(n<2)ans++;
	ans%=MOD;
	if(n-2>=0)ans+=dp[n-2];
	ans%=MOD;
	cout<<ans<<"\n";

}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
