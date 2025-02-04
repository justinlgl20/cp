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

int dp[100005];
const int add=50001;
mt19937 rd(time(0));

void solve() {
	int n,m;cin>>n>>m;
	vector<pii> math(n+m);
	for(int i=0;i<n;i++)cin>>math[i].f>>math[i].s;
	for(int i=n;i<m+n;i++){cin>>math[i].f>>math[i].s;math[i].f=-math[i].f;}
	dbg("INPUT");
	for(int i=0;i<100003;i++){
		dp[i]=-1e18;
	}
	shuffle(all(math), rd);
	dp[add]=0;
	for(int i=0;i<math.size();i++){
		if(math[i].f>0){
			for(int j=100002;j-math[i].f>=0;j--){
				dp[j]=max(dp[j],dp[j-math[i].f]+math[i].s);
			}
		} else {
			for(int j=0;j-math[i].f<100003;j++){
				dp[j]=max(dp[j],dp[j-math[i].f]+math[i].s);
			}
		}
	}
	cout<<dp[add]<<"\n";
}
int32_t main(){
	int t;cin>>t;while(t--)solve();
}
