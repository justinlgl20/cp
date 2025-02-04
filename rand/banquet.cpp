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
	int n,m;cin>>n>>m;
	int suma=0,sumb=0;
	vector<int>a(n),b(n);
	for(int i=0;i<n;i++){cin>>a[i]>>b[i];suma+=a[i];sumb+=b[i];}
	int big=suma-sumb,smol=suma-sumb;
	for(int i=0;i<n;i++){
		int p=min(a[i],m),q=min(b[i],m);
		smol=smol-p+(m-p);
		big=big+q-(m-q);
	}
	int best;
	if(smol>0) best=smol;
	else if(big < 0) best=big;
	else best=(big&1ll);
	cout<<abs(best)<<"\n";
	for(int i=0;i<n;i++){
		int p=min(a[i],m),q=min(b[i],m);
		int dela=m-q,delb=q;
		int delt=min((big-best)/2,p-dela);
		big-=2*delt;
		dela+=delt;
		delb-=delt;
		cout<<dela<<" "<<delb<<"\n";;
	}
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
