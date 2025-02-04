#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T,typename V>
ostream& operator<<(ostream& os, pair<T,V> t) {
	os<<"("<<t.first<<", "<<t.second<<")";return os;
}
 
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

template<typename T>
struct multi_ordered_set {
	tree<pair<T, int>, null_type, less<pair<T,int>>, rb_tree_tag,tree_order_statistics_node_update> x;
	int cnt;
	multi_ordered_set() { x.clear();cnt=0; }
	void insert(T i) { x.insert(make_pair(i,cnt++)); }
	void erase(T i) { x.erase(x.lower_bound(make_pair(i,0))); }
	T find_by_order(int i) { return (*(x.find_by_order(i))).f; }
	int order_of_key(T i) { return x.order_of_key(make_pair(i, 1e9)); }
	int size() { return x.size(); }
	auto begin() { return x.begin(); }
	auto end() { return x.end(); }
	void clear() { x.clear(); }
};

int32_t main() {
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n,h,v;cin>>n>>h>>v;
	vector<pii> points(n);
	cin>>points[0].f>>points[1].f;
	int a,b,c,d;cin>>a>>b>>c>>d;
	for(int i=2;i<n;i++)points[i].f=((a*points[i-2].f+b*points[i-1].f+c)%d)+1;
	cin>>points[0].s>>points[1].s;
	cin>>a>>b>>c>>d;
	for(int i=2;i<n;i++)points[i].s=((a*points[i-2].s+b*points[i-1].s+c)%d)+1;
	if (h+v < n) {
		cout<<"-1\n";return 0;
	}
	vector<int> ssm(n+4, 0);
	sort(all(points), [&](pii a, pii b) {
		if(a.s < b.s) return true;
		if(b.s < a.s) return false;
		return (a.f<b.f);
	});
	for(int i=n-1;i>=0;i--)ssm[i]=max(points[i].f,ssm[i+1]);
	multi_ordered_set<int> x;
	int ans=1e18;
	int cnt=0;
	if(h==n)ans=ssm[0];
	// check gaps
	for(int i=0;i<n;i++){
		x.insert(points[i].f);
		assert(x.size());
		if(v<x.size()){
			cnt=max(cnt,(x.find_by_order(0))); // min vs cnt
			// delete
			x.erase(x.find_by_order(0));
		} 
		if(n-h<=x.size()){
			ans=min(ans,points[i].s+max(cnt,ssm[i+1]));
		}
		dbg(i, x, ans, cnt);
		
		
	}
	cout<<ans<<"\n";

	/* slow shit accounting for line intersections not being allowed
	multi_ordered_set<int> s;
	multiset<int> right;
	int ans=1e18;
	for (auto i : points) right.insert(i.s);
	for (auto i : points) {
		right.erase(right.find(i.s));
		int k = s.order_of_key(i.s); // the first k things can be either hori or verti
		int used_h = s.size() - k + 1ll; // all above this are also horizontal
		int hori_cost = i.f;
		int used_v = right.size();
		int avail_h = h-used_h;
		int vert_cost = 0;
		if (used_h > h or used_v > v) goto idk;
		if (k-avail_h-1 >= 0) {
			vert_cost = s.find_by_order(k-avail_h-1);
			used_h += avail_h;
			used_v += k-avail_h;
		} else {
			used_h = n-right.size();
		}
		if (used_h > h or used_v > v) goto idk;
		if (right.size()) {
			vert_cost = max(vert_cost, (*right.rbegin()));
		}
		ans = min(ans, vert_cost+hori_cost);
		idk:
		s.insert(i.s);
	}
	s.clear();right.clear();
	for(int i=0;i<n;i++){swap(points[i].f,points[i].s);right.insert(points[i].s);}
	sort(all(points));
	swap(h, v);
	dbg(h, v);
	for (auto i : points) {
		dbg(i.f, i.s);
		right.erase(right.find(i.s));
		int used_h = s.size() - s.order_of_key(i.s); // all above this are also horizontal
		int hori_cost = i.f;
		used_h++;
		int k = s.order_of_key(i.s); // 0 to k-1 can be hori or vert
		// k to end must be hori
		int used_v = right.size();
		if (used_h > h or used_v > v) continue;
		int avail_h = h-used_h;
		// 0th to k-1st things need to be distributed
		int vert_cost = 0;
		if (k-avail_h-1 >= 0) {
			vert_cost = s.find_by_order(k-avail_h-1);
			// we use avail_h hori things
			used_h += avail_h;
			used_v += k-avail_h;
		}
		else {
			used_h = n-right.size();
		}
		// allowing some case under
		if (used_h > h or used_v > v) continue;
		if (right.size()) {
			vert_cost = max(vert_cost, (*right.rbegin()));
		}
		dbg(vert_cost,hori_cost, used_v, used_h);
		ans = min(ans, vert_cost+hori_cost);
		s.insert(i.s);
	}
	if (ans == 1e18) cout << "-1\n";
	else 
		cout<<ans<<"\n";
*/
}
