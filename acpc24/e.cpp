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
int illegal[305][305];

int32_t main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n,m,k;cin>>n>>m>>k;
	for (int i=0;i<n;i++){
		for(int j=0;j<m;j++)cin>>a[i][j];
	}
	for (int i=0;i<n;i++){
		for(int j =0;j < m;j++) {
			vector<pii> must;
			int idk=0;
			bool illega=0;
			for(int x = -k/2;x<=k/2 and!illega;x++){
				for(int y=-k/2;y<=k/2 and!illega;y++){
					if(i+x< 0 or i+x>=n or j+y<0 or j+y>=m)continue;
					if(x <= 0 and y<=0 and a[i+x][j+y] > a[i][j]) {
						if (x==0 and y==0)continue;
						must.emplace_back(i+x,j+y);
						illega=illega or illegal[i+x][j+y];
						dp[i][j] += a[i+x][j+y];
					}
					if (x > 0 or y>0) {
						idk=max(idk,a[i+x][j+y]);
					}
				}
			}
			if(idk > a[i][j] or illega) {
				// can't take here
				illegal[i][j]=1;
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
					illegal[i][j]=1;
					if(i>0)dp[i][j]=max(dp[i][j],dp[i-1][j]);
					if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
					dbg(i, j,dp[i][j]);
					leave=true;
				}
			}
			if (leave)continue;
			// must be from must[0]
			// like in that section
			// ISSUE IS THAT SINCE WE ARE TAKING THE THINGS IN MUST, THOSE THINGS COULD BE FORCED TO TAKE OTHERS, BUT WE AREN'T ACCOUNTING FOR THAT
			int add = 0;
			if(must[0].f>0)add=max(add,dp[must[0].f-1][must[0].s]);
			if(must[0].s>0)add=max(add,dp[must[0].f][must[0].s-1]);
			dbg(add);
			dp[i][j]+=add;
			if(i>0)dp[i][j]= max(dp[i][j], dp[i-1][j]);
			if(j>0)dp[i][j]=max(dp[i][j],dp[i][j-1]);
			dbg(i, j,dp[i][j]);
		}
	}
	cout<<dp[n-1][m-1]<<"\n";
}
