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
	int n;cin>>n;
	vector<int>k(n);
	for(int i=0;i<n;i++)cin>>k[i];
	sort(all(k));
	vector<int> active(n);
	int use=0;
	multiset<int> v;
	for(int i=0;i<n;i++)v.insert(k[i]);
	int q;
	for(int i=0;i<n-1;i++){
		if(k[i]==k[i+1])use=k[i], q=i;
	}
	if(use==0){cout<<"-1\n";return;}
	v.erase(v.find(k[q]));
	v.erase(v.find(k[q]));
	int mindif=1e18;
	int last=-1;
	int a=-1, b=-1;
	for(auto i : v) {
		if(last!=-1){
			if(i-last<mindif){
				mindif=i-last;
				a=i,b=last;
			}
		}
		last=i;
	}
	dbg(use,b,a);
	if(a!=-1 and b+use+use>a){
		cout<<a<<" "<<b<<" "<<use<<" " <<use<<"\n";
	}
	else {
		cout<<"-1\n";
	}
}

int32_t main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int t;cin>>t;
	while(t--)solve();
}
