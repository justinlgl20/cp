#include <bits/stdc++.h>
using namespace std;
 
#define int unsigned long long
 
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
	int n,m;cin>>n>>m;
	vector<int>a(n),b(m);
	for(int i=0;i<n;i++){cin>>a[i];a[i]++;}
	for(int i=0;i<m;i++){cin>>b[i];b[i]++;}
	if(m>n){
		swap(n,m);swap(a,b);
	}
	// need to compress both such bullshit
	// hashing YAY
	int base=1000000321;
	vector<int> powers(max(m,n)+4,1);
	for(int i=1;i<max(m,n)+3;i++){
		powers[i]=powers[i-1]*base;
	}
	vector<int> pre(n+3,a[0]);
	for(int i=1;i<n;i++){
		pre[i]=pre[i-1]+powers[i]*a[i];
	}
	function<void(int,int)> hash=[&](int l, int r) {
		return pre[r]-pre[l-1];
	};


	
}
