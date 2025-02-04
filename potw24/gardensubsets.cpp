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

const int MOD=1000000007;

int dp[155][155][155][2][2];
int psa[155][2][2][155][155];
int ps[155][155];

int32_t main() {
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		string s;cin>>s;
		for(int j=1;j<=n;j++){
			ps[i][j]=ps[i][j-1]+(s[j-1]=='G');
		}
	}
	int ans=0;
	for(int row=1;row<=n;row++){
		for(int a=0;a<2;a++){
			for(int b=0;b<2;b++){
				// build into psa[row-1][a][b] 

				for(int i=1;i<=n;i++){
					for(int j=1;j<=n;j++){
						psa[row-1][a][b][i][j]=psa[row-1][a][b][i-1][j]+psa[row-1][a][b][i][j-1]-psa[row-1][a][b][i-1][j-1]+dp[row-1][i][j][a][b];
						psa[row-1][a][b][i][j]%=MOD;
					}
				}
			}
		}
		function<int(int,int,int,int,int,int)> sum=[&](int l1, int l2, int r1, int r2, int a,int b) {
			int ans=psa[row-1][a][b][l2][r2]-psa[row-1][a][b][l1-1][r2]-psa[row-1][a][b][l2][r1-1]+psa[row-1][a][b][l1-1][r1-1];
			while(ans<MOD)ans+=MOD;
			ans%=MOD;
			return ans;
			for(int i=l1;i<=l2;i++){
				for(int j=r1;j<=r2;j++){
					ans+= dp[row-1][i][j][a][b];
					ans%=MOD;
				}
			}
			return ans;
		};
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				int l=i,r=j;
				if(ps[row][j]-ps[row][i-1]!=j-i+1)continue;
				dbg(row, i, j);
				dp[row][i][j][1][1]=1+sum(l,r,l,r,1,1);
				dbg(dp[row][i][j][1][1]);
				dp[row][i][j][1][0]=sum(l,r,r+1,n,1,1)+sum(l,r,r,n,1,0);
				dbg(dp[row][i][j][1][0], l, r, r+1, n);
				dp[row][i][j][0][1]=sum(1,l-1,l,r,1,1)+sum(1,l,l,r,0,1);
				dp[row][i][j][0][0]=sum(1,l-1,r+1,n,1,1)+sum(1,l,r+1,n,0,1)+sum(1,l-1,r,n,1,0)+sum(1,l,r,n,0,0);
				for(int a=0;a<2;a++)for(int b=0;b<2;b++){dp[row][i][j][a][b]%=MOD;ans+=dp[row][i][j][a][b]; ans%=MOD;}
			}
		}
	}
	cout<<ans<<"\n";
}
