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

int32_t main() {
	int n,k;cin>>n>>k;
	vector<int> h(n);
	for(int i=0;i<n;i++)cin>>h[i];
	// now gap is between 0 and 1
	vector<int> psa(n+2,0);
	for(int i=1;i<=n;i++)psa[i]=psa[i-1]+h[i-1];
	function<int(int,int)>sum=[&](int l,int r){
		return psa[r+1]-psa[l];
	};
	// 1 to blocks is the range we need to increase
	int fans =1e18;
	int blocks;
	for (int i = 0; i < n; i++) {
		// h[i] is the bottom
		// bsearch for h[i]+k;
		if (h[i]+k > h[n-1])break;
		blocks = i;
		for(int j=20;j>=0;j--){
			if(blocks+(1ll<<j) < n and h[blocks+(1ll<<j)] < h[i]+k)blocks+=(1ll<<j);
		}
		if (blocks >= n-1) break;
		if (blocks == i) {
			cout << "0\n";return 0;
		}
		// need to modify stuff in range [i, blocks] so that latter half = h[i]+k and first half = h[i] for min cost
		// bsearch for whichever is closer
		int an=i;
		for (int j=20;j>=0;j--){
			if (an+(1ll<<j) <= blocks and h[an+(1ll<<j)]-h[i] <= h[i]+k-h[an+(1ll<<j)])an+=(1ll<<j);
		}
		// i to an comes to h[i]
		// an+1 to blocks comes to h[i]+k
		int ans = sum(i, an)-h[i]*(an-i+1);
		if(an+1<=blocks) {
			ans+=(h[i]+k)*(blocks-(an+1)+1)-sum(an+1,blocks);
		}
		dbg(i, an, blocks, ans);
		fans=min(fans,ans);
	}

	for(int i=n-1;i>= 0; i--){
		// if h[i] is the top
		// then h[i]-k is the bottom
		if (h[i]-k < h[0])break;
		blocks=i;
		for(int j=20;j>=0;j--){
			if(blocks-(1ll<<j) >= 0 and h[blocks-(1ll<<j)]>h[i]-k)blocks -=1ll<<j;
		}
		if (blocks <= 0) break;
		if (blocks == i) {
			cout << "0\n";return 0;
		}
		int l=blocks, r= i;
		// need to modify stuff in range [l, r] such that first half = h[i]-k and last half = h[i]
		int an=l;
		for(int j=19;j>=0;j--){
			if(an+(1ll<<j)<=r and h[an+(1ll<<j)]-(h[i]-k) <= h[i]-h[an+(1ll<<j)])an+=(1ll<<j);
		}
		int ans = sum(l, an)-(h[i]-k)*(an-l+1);
		if(an+1<=r) {
			ans+=(h[i])*((r-(an+1)+1))-sum(an+1,r);
		}
		dbg(l, an, r, ans);
		fans=min(fans,ans);

		
	}
	cout << fans<<"\n";
}
