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

int ans[1005];;

int32_t main() {
	int t;cin>>t;
	ans[1]=1;
	for(int i=2;i<1002;i++){
		for(int j=0;j<i;j++){
			ans[i]+=(1ll<<j);
			if(i-j-1>0 and ans[i-j-1]<(1ll<<(j+1ll))){
				dbg(i, i-j-1, ans[i-j-1]);
				ans[i]+=ans[i-j-1];
				break;
			}
		}
		dbg(i, ans[i]);
	}
	while(t--){
		int a;cin>>a;
		cout<<ans[a]<<"\n";
	}
}
