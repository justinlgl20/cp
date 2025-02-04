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

int n,x,y;

int solve(vector<int> a) {
	vector<int>psa(n+4,0);
	for(int i=1;i<=n;i++)psa[i]=psa[i-1]+a[i-1];
	function<int(int,int)>sum=[&](int l,int r){
		return psa[r+1]-psa[l];
	};
	int s=sum(0,n-1);
	dbg(s);
	vector<int>pxa(n+4,0);
	for(int i=1;i<=n;i++)pxa[i]=pxa[i-1]^a[i-1];
	function<int(int,int)>xorsum=[&](int l,int r){
		return pxa[r+1]^pxa[l];
	};
	vector<int>lbest(n+4,-1e18); // this is how much we lose
	for(int i=x-1;i<n;i++){
		// ranges are from i-x+1 to i and i+1 to i+y
		if(x-1==0) {
			lbest[i]=-sum(i-x+1,i)+xorsum(i-x+1,i);
		} else 
			lbest[i] = max(-sum(i-x+1,i)+xorsum(i-x+1,i), lbest[i-1]);
	}
	int ans=0;
	int cnt=-1e18;
	for(int i=n-y-1;i>=x-1;i--){
		cnt = max(-sum(i+1,i+y)+xorsum(i+1,i+y), cnt);
		dbg(i, lbest[i],cnt);
		ans = max(ans, s+cnt+lbest[i]);
	}
	return ans;
}

int32_t main() {
	cin>>n>>x>>y;
	vector<int>a(n);
	for(int i=0;i<n;i++)cin>>a[i];
	int ans = solve(a);
	reverse(all(a));
	ans = max(ans,solve(a));
	cout<<ans<<"\n";
}
