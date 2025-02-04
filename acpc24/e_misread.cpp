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

int dp[305][305];
int a[305][305];

// max 2d segtree :(((
// NOPE GONNA USE A 1D one im so sigma

struct seg{
	vector<int> t; int n;
	seg(int x) {
		n=1;
		while(n<=x)n*=2;
		t.assign(n*3,0);
	}
	void upd(int p, int v) {
		for(t[p+=n]=v;p>1;p>>=1)t[p>>1]=max(t[p], t[p^1]);
	}
	int query(int l, int r) {
		int ans=0;
		for (l+=n,r+=n+1;l<r;l>>=1,r>>=1){
			if(l&1)ans=max(ans,t[l++]);
			if(r&1)ans=max(ans,t[--r]);
		}
		return ans;
	}
};

int32_t main() {
	int n,m,k;cin>>n>>m>>k;
	for (int i=0;i<n;i++){
		for(int j=0;j<m;j++)cin>>a[i][j];
	}
	vector<pii> order;
	for (int i = 0; i < min(n, m); i++) {
		order.emplace_back(i, i);
		for (int j = i+1; j < m; j++) {
			order.emplace_back(i, j);
		}
		for(int j = i+1; j < n;j++) {
			order.emplace_back(j, i);
		}
	}
	for (auto idkidk : order){
		int i = idkidk.f;
		int j = idkidk.s;
		vector<pii> must;
		int idk=0;
		for(int x = -k/2;x<=k/2;x++){
			for(int y=-k/2;y<=k/2;y++){
				if(i+x< 0 or i+x>=n or j+y<0 or j+y>=m)continue;
				if(x <= 0 and y<=0 and a[i+x][j+y] > a[i][j]) {
					if (x==0 and y==0)continue;
					must.emplace_back(i+x,j+y);
					dp[i][j] += a[i+x][j+y];
				}
				if (x > 0 or y>0) {
					idk=max(idk,a[i+x][j+y]);
				}
			}
		}
		if(idk > a[i][j]) {
			// can't take here
			dp[i][j]=0;
			if(i>0)dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
			dbg(i,j,dp[i][j]);
			continue;
		}
		
		// otherwise we must take all the thingies in must
		dp[i][j] += a[i][j];
		dbg(dp[i][j], must.size());
		sort(all(must));
		if(must.size()==0){
			dp[i][j]=0;
			if(i>0)dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
			dp[i][j]+=a[i][j];

			dbg(i, j,dp[i][j]);
			continue;
		}
		bool leave=false;
		for(int q=1;q<must.size();q++){
			if(must[q].s<must[q-1].s){
				dp[i][j]=0;
				if(i>0)dp[i][j]=max(dp[i][j],dp[i-1][j]);
				if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
				dbg(i, j,dp[i][j]);
				leave=true;
			}
		}
		if (leave)continue;
		// must be from must[0]
		// like in that section
		int add = 0;
		// THIS IS THE BREAKING BIT
		if(must[0].f>0)add=max(add,dp[must[0].f-1][must[0].s]);
		if(must[0].s>0)add=max(add,dp[must[0].f][must[0].s-1]);
		// END BREAKING BIT
		dbg(add);
		dp[i][j]+=add;
		if(i>0)dp[i][j]=max(dp[i][j], dp[i-1][j]);
		if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
		dbg(i, j,dp[i][j]);
		/*if (j == m-1) {
			int ans=0;
			for(int p=0;p<m;p++)ans=max(ans,dp[i][p]);
			rows.upd(i,ans);
		}
		if(i==n-1){
			int ans=0;
			for(int p=0;p<n;p++)ans=max(ans,dp[p][j]);
			cols.upd(j, ans);
		}*/
	}
	cout<<dp[n-1][m-1]<<"\n";
}
