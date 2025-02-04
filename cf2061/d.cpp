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
	multiset<int> a;
	for(int i=0;i<n;i++){
		int g;cin>>g;a.insert(g);
	}
	priority_queue<int> s;
	for(int i=0;i<m;i++){
		int g;cin>>g;s.push(g);
	}
	while(s.size()and a.size() and s.size()<=a.size()){
		int g=s.top();
		s.pop();
		if(a.find(g)!=a.end()){
			a.erase(a.find(g));
		} else {
			s.push(g/2);
			s.push(g/2+(g%2));
		}

	}
	if(s.size()==0 and a.size()==0){
		cout<<"Yes\n";
	} else{
		cout<<"No\n";
	}
}

int32_t main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int t;cin>>t;
	while(t--)solve();
}
