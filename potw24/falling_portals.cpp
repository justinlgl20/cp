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

#define double long double

const double EPSILON =0.0000001;


bool qwerty=0;

struct line {
	double m,c;
	line(int k,int w){m=k;c=w;}
	line() {
		if(qwerty==0)m=0,c=1e18;
		else m=0,c=-1e18;
	}
	double get(double x) {
		return m*x+(double)c;
	}
};

double intersect(line a,line b) {
	return (a.c-b.c)/(b.m-a.m);
}

struct lct2 {
	// MAX CHT
	deque<line> s; // sorted so that start's m is higher than end's m
	lct2() {
	}

	void insert(line v) { // sorted going down in c value
		// so will always be at the front
		while (s.size()>=1 and s[0].m<v.m){
			s.pop_front();
		}
		// all left in s have gradient bigger than m
		while (s.size()>= 2 and intersect(v, s[1])>intersect(s[0],s[1]))s.pop_front();
		s.push_front(v);
	}
	double query(line x) {
		double ans=1e18;
		for(int i=0;i<s.size();i++){
			if(intersect(s[i],x)>=0){
				ans=min(ans,intersect(s[i],x));
			}
		}
		return ans;
		/*
		int inx=0;
		// inx must be strictly below line
		// we want leftmost interaction
		for(int i=18;i>=0;i--){
			if(inx+(1ll<<i)<s.size()-1 and intersect(s[inx+(1ll<<i)+1], x) > intersect(s[inx+(1ll<<i)],s[inx+(1ll<<i)+1]))inx+=(1ll<<i);
		}
		inx++;
		dbg(s.size());
		for(int i=0;i<s.size();i++) {
			dbg(s[i].m,s[i].c);
		}
		dbg(inx);
		if(s.size()==1){
			return intersect(s[0],x);
		}
		return min(intersect(s[inx], x), intersect(s[0], x));*/
	}
};

struct lct { // NEED TO FIX THIS I THINK
	// MIN CHT
	deque<line> s;
	lct() {
	}
 
	void insert(line v) { // sorted going down in c value
		while (s.size() and s[0].m > v.m) s.pop_front();
		// all left in s have gradient more than v
		while (s.size()>= 2 and intersect(v, s[1]) > intersect(s[1],s[0])) s.pop_front();
		s.push_front(v);

	}
	double query(line x) {
		double ans=1e18;
		for(int i=0;i<s.size();i++){
			if(intersect(s[i],x)>= 0)
				ans=min(ans,intersect(s[i],x));
		}
		return ans;
	}
};


int32_t main() {
	cout<<flush<<setprecision(30);
	int n;cin>>n;
	vector<pii> sw(n);
	vector<int>a(n);
	for(int i=0;i<n;i++){
		cin>>sw[i].f;sw[i].s=i;
		a[i]=sw[i].f;
	}
	sort(all(sw));
	reverse(all(sw));
	vector<int>q(n);
	for(int i=0;i<n;i++){cin>>q[i];q[i]--;}
	lct cht = lct();
	vector<double>ans(n);
	for(auto qwe : sw) {
		int i=qwe.s;
		line l=line(-i-1ll, a[i]);
		//dbg("INSERT", l.m,l.c);
		cht.insert(l);
		// find intersection of q and the cht
		line qu=line(-q[i]-1ll, a[q[i]]);
		//dbg("GO TO", qu.m, qu.c);
		double s=0;
		if (a[q[i]]<a[i]){
			s=cht.query(qu);
			if(s<0 or s==1e18)s=-1;
			ans[i]=s;
			dbg(i, ans[i]);
		}
	}
	qwerty=1;
	reverse(all(sw));
	lct2 cht2 = lct2();
	// THIS LCT WE WANT THE HIGHEST
	for(auto qwe : sw) {
		int i=qwe.s;
		line l=line(-i-1ll, a[i]);
		dbg("INSERT", l.m,l.c);
		cht2.insert(l);
		// find intersection of q and the cht
		line qu=line(-q[i]-1ll, a[q[i]]);
		dbg("GO TO", qu.m, qu.c);
		double s=0;
		if (a[q[i]]>=a[i]){
			s=cht2.query(qu);
			if(s<0 or s==1e18)s=-1;
			ans[i]=s;
			dbg(i, ans[i]);
		}
	}
	for(int i=0;i<n;i++)cout<<ans[i]<<"\n";


}
