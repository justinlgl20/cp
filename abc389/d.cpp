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

const double q=0.5;

int32_t main() {
	int r;cin>>r;
	function<bool(double,double)>works0=[&](double i,double j){
		return( i*i+j*j)<=(double)(r*r);
	};
	function<bool(double,double)>works=[&](double i, double j) {
		return works0(i+q,j+q)&works0(i+q,j-q)&works0(i-q,j+q)&works0(i-q,j-q);
	};
	int ans=0;
	for(int i=0;i<= r;i++){
		int l=0;
		for(int j=19;j>=0;j--){
			if(works(i, l-(1ll<<j)))l-=(1ll<<j);
		}
		int r=max(0ll,-l);
		if (works(i,0)){
			if(i==0)ans-=(r-l+1);
			ans+=2*(r-l+1);
		}
	}
	cout<<ans<<"\n";
}
