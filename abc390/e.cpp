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
vector<pii> stuff[3];
int x;
vector<int> knapsack(vector<pii> things) {
	int n=things.size();
	vector<int> ans(x+4,0); // for c calories, ans[i] is max vitamins
	vector<vector<int>> dp(n, vector<int>(x+3,0));
	for(int i=0;i<things.size();i++){
		if(i>0)
			dp[i] = dp[i-1];
		int val=things[i].f, cost=things[i].s;
		for(int j=x+2;j>=cost;j--){
			dp[i][j]=val + (i>0?dp[i-1][j-cost]:0);
			if(i>0) {
				dp[i][j] = max(dp[i][j], dp[i-1][j]);
			}
			dp[i][j]=max(dp[i][j],dp[i][j-1]);
		}
	}
	return dp[n-1ll];

}
vector<int> idk[3];
int32_t main() {
	int n;cin>>n>>x;
	stuff[0].clear();
	stuff[1].clear();
	stuff[2].clear();
	dbg("HI");
	for(int i=0;i<n;i++){
		int v,a,c;cin>>v>>a>>c;
		v--;
		assert(v<3);
		stuff[v].emplace_back(a, c);
	}
	for(int i=0;i<3;i++){
		stuff[i].emplace_back(0, 0);
	}
	dbg("TAKEN INPUT");
	for(int i=0;i<3;i++)idk[i]=knapsack(stuff[i]);
	dbg("DONE KNAPSACK");
	dbg(idk[0]);
	dbg(idk[1]);
	dbg(idk[2]);
	function<bool(int)> works =[&](int q){
		// all three must have >= q vitamins for minimum calories
		int ans=0;
		for(int i=0;i<3;i++){
			int w=0;
			for(int j=20;j>=0;j--){
				if(w+(1ll<<j) <= x and idk[i][w+(1ll<<j)]<q)w+=(1ll<<j);
			}
			w++;
			ans+=w;
		}
		if(ans>x)return false;
		return true;
	};
	int ans=0;
	for(int i=30;i>=0;i--){
		if(works(ans+(1ll<<i)))ans+=(1ll<<i);
	}
	cout<<ans<<"\n";
}
