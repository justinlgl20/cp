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

struct seg{
	seg *l, *r;
	int tl, tr, v;
	seg(int ql, int qr) {
		tl=ql,tr=qr,v=0;
		if(tl==tr)return;
		int tm=(tl+tr)/2;
		l=new seg(tl,tm);
		r=new seg(tm+1,tr);
	}
	void upd(int ql, int qr) {
		if (ql <= tl and tr <= qr) {
			v++;
			return;
		}
		if (ql>tr or qr<tl) return;
		l->upd(ql,qr);
		r->upd(ql,qr);
	}
	int query(int x){
		int ans=0;
		ans+=v;
		if(tl==tr)return ans;
		int tm=(tl+tr)/2;
		if(x<=tm)ans+=l->query(x);
		else ans+=r->query(x);
		return ans;
	}
};

int32_t main(){
	int n;cin>>n;
	seg idk=seg(0,6e5);
	for(int i=0;i<n;i++){
		int l,r;cin>>l>>r;
		idk.upd(l,r);
	}
	int q;cin>>q;
	while (q--){
		int x;cin>>x;
		cout<<x+idk.query(x)<<"\n";
	}
}
