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

int cnt[200005];
int p[200005];

int32_t main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n,m;cin>>n>>m;
	priority_queue<pair<int,pii>, vector<pair<int, pii>>, greater<pair<int,pii>>> s;
	for(int i=0;i<n;i++){
		cnt[i]=1;
		cin>>p[i];s.push(make_pair(p[i], make_pair(p[i], i)));
	}
	int ans=0;
	while (m>0) {
		int q=s.top().f, k=s.top().s.f, i=s.top().s.s;
		s.pop();
		if(q>m)break;
		ans++;
		m-=q;
		s.push(make_pair((2*cnt[i]+1)*p[i], make_pair(p[i], i)));
		cnt[i]++;

	}
	cout<<ans<<"\n";
}
