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

int n,m;
int k, x;
vector<int> s,p;

bool works(int t) {
	int good_boxes = 0;
	for(auto i : s){
		if(i>=x)good_boxes++;
	}
	
	int keys=0;
	sort(all(s),greater<int>());
	multiset<pii> post_boxes;//need to sort by sz

	int cnt=0; // current package
	sort(all(p));
	int a = 0;
	while(t>0 and cnt<max(t,good_boxes)){
		if (s[cnt]<p[t-1])break;
		post_boxes.insert(make_pair(s[cnt]%x,s[cnt])); // insert all packages that can fit in
		a++;
		cnt++;
	}
	// take all mail boxes other than those < x unless we can't fit all package
	// in that case let's take the largest t mailboxes which we may as well do anyway
	// greedily put biggest package assigning by mods to waste as little space as possible
	// if there is no mod bigger than the package just take the l and go back to start
	// find how many keys we can fit
	dbg(a, post_boxes.size());
	for(int i = t-1;i>=0;i--){
		// WTF how are some boxes just deleting themselves wtf wtf wtf
		if (post_boxes.size()==0)return 0; // WTF WHY IS THIS THING NOT DOING ITS JOB
		auto thing = post_boxes.lower_bound(make_pair(p[i]%x,-1e9));
		if (thing==post_boxes.end()) thing=post_boxes.lower_bound(make_pair(0, -1e9)); // just take first hting
		assert(post_boxes.size()); // sanity check
		dbg(thing->f,thing->s);
		int post_box = (*thing).second;
		keys += (post_box-p[i])/x;
		dbg((post_box-p[i])/x);
		// THE BUG IS HERE
		post_boxes.erase(thing);
		a = 0;
		while(i > 0ll and cnt<max(t,good_boxes)){
			if (s[cnt] < p[i-1]) break;
			a++;
			post_boxes.insert(make_pair(s[cnt]%x,s[cnt])); // insert all packages that can fit in
			cnt++;
		}
		dbg(post_boxes.size(), a);
	}
	for (auto i : post_boxes){keys+=max(0ll,i.s/x-1ll);dbg(i.f,i.s);}
	// now take the boxes with < x size if we don;t have enough
	for (;cnt<max(t,good_boxes);cnt++) keys+=(max(0ll,s[cnt]/x-1ll));
	return (keys>=t-1ll);

}

int32_t main() {
	cin >> n >> m >> k >> x;
	s.resize(n);
	p.resize(m);
	for(int i=0;i<k;i++)cin>>s[i];
	int a,b,c,d;cin>>a>>b>>c>>d;
	for(int i=k;i<n;i++)s[i]=((a*s[i-2]+b*s[i-1]+c)%d)+1ll;
	for(int i=0;i<k;i++)cin>>p[i];
	cin>>a>>b>>c>>d;
	for(int i=k;i<m;i++)p[i]=((a*p[i-2]+b*p[i-1]+c)%d)+1ll;
	dbg(s);
	dbg(p);
	// goofy ahh input format;
	int ans=0;
	for(int i=20;i>=0;i--){
		if(ans+(1ll<<i) <= min(m+1ll,n+1ll) and works(ans+(1ll<<i)))ans+=(1ll<<i);
	}
	cout<<ans<<"\n";
}
