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

void solve() {
	int p=31;
	int MOD=1e9+9;
	int n,m;cin>>n>>m;
	vector<int> pow(n*m+4,1);
	for(int i=1;i<n*m+3;i++){
		pow[i]=pow[i-1]*p;
		pow[i]%=MOD;
	}
	vector<int> a(n*m), ah(n*m),b(n*m),bh(n*m);
	// i*m+j
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++){cin>>a[i*m+j];ah[i*m+j]=((i*m+j)>0?ah[i*m+j-1]:0)+pow[i*m+j]*a[i*m+j];ah[i*m+j]%=MOD;
		}
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++){
			cin>>b[i*m+j];bh[i*m+j]=((i*m+j)>0?bh[i*m+j-1]:0)+pow[i*m+j]*b[i*m+j];bh[i*m+j]%=MOD;
			}
	}
	function<int(vector<int>&, int,int)>query=[&](vector<int> &a, int l, int r) {
		int ans=0;
		if(l==0){
			ans=a[r];
		} else {
			ans=(a[r]+MOD-a[l-1])%MOD;
		}
		ans *=pow[n*m-r];
		ans%=MOD;
		return ans;
	};
	int ans=0;
	vector<int> rowstart(n+4,0);
	dbg(query(ah,
	for(int row=0;row<n;row++){
		int c;
		bool done=false;
		dbg(row, rowstart[row]);
		for(c=m-1;c>=0;c--){
			// check if a[i][0] to a[i][c] is the same as b[i][m-c-1] to b[i][m-1] all inclusive
			if(query(ah,rowstart[row],rowstart[row]+c)==query(bh,row*m+m-c-1,row*m+m-1)){
				done=true;
				ans+=(m-(c+1));
				dbg(row, c+1);
				rowstart[row+1]=rowstart[row]+c+1;
				break;
			}
		}
		if(done==false){
			ans+=m;
			dbg(row,0);
			rowstart[row+1]=rowstart[row];
		}
	}
	cout<<ans<<"\n";

}

int32_t main() {
	int t;cin>>t;while(t--)solve();
}
