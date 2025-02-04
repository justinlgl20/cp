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
	int n, m;cin>>n>>m;
	vector<int>a(n);
	vector<int>b(m);
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)cin>>b[i];
	sort(all(a));
	sort(all(b));
	if(n<m){
		swap(a,b);
		swap(n,m);
	}
	// n is always bigger
	vector<pii> useda, usedb;
	int al=0,ar=n-1,bl=0,br=m-1;
	int ans=0;
	vector<int> anse;
	for(int i=1;;i++){
		// i in
		idk:
		int lefta=n-(useda.size()*2)-(usedb.size());
		int leftb=m-(usedb.size()*2)-(useda.size());
		function<void()> takea=[&](){
			ans+=a[ar]-a[al];
			dbg(al, ar);
			useda.emplace_back(al,ar);
			ar--;al++;

		};
		function<void()> takeb=[&](){
			ans+=b[br]-b[bl];
			usedb.emplace_back(bl,br);
			dbg(bl,br);
			br--;bl++;
		};
		if(lefta>=2 and leftb>=2){
			if(a[ar]-a[al]>b[br]-b[bl]){
				takea();
			} else {
				takeb();
			}
		} else if(lefta>=2 and leftb>=1){
			takea();
		} else if(leftb>=2 and lefta>=1){
			takeb();
		} else if(useda.size() and leftb>=2){
			// unroll last takea
			al--;
			ar++;
			ans-=(a[ar]-a[al]);
			dbg("REM",al,ar);
			useda.pop_back();
			takeb();
			// try and take another one
			goto idk;
		} else if(usedb.size() and lefta>=2){
			bl--;
			br++;
			dbg("REM",bl,br);
			ans-=(b[br]-b[bl]);
			usedb.pop_back();
			takea();
			// try and take another one
			goto idk;
		}
		else{
			break;
		}
		lefta=n-(useda.size()*2)-(usedb.size());
		leftb=m-(usedb.size()*2)-(useda.size());
		dbg(lefta,leftb);
		anse.push_back(ans);
	}
	cout<<anse.size()<<"\n";
	for(auto i : anse) cout<<i<<" ";
	cout<<"\n";
}

int32_t main() {
	int t;cin>>t;
	while(t--)solve();
}
