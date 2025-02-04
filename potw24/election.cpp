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

// sort from big to small
// go through
// if inserting party i, all other parties are bigger, so we want them to be as close to limit as possible. FUCK I HATE KNAPSACK
// we want to store dp[i][x] is if value x is achievable with all parties with weights >= party i

bitset<100005> dp[305];
// COULD DO 100000 * sqrt 100000 WITH THE C SQRT C TRICK
int retrieval[100005];

int32_t main() {
	int n;cin>>n;
	vector<int> p(n);
	int s=0;
	vector<pii> sw(n);
	for(int i=0;i<n;i++){
		cin>>p[i];sw[i]=make_pair(p[i], i+1);;s+=p[i];
	}
	int hoshii=s/2+1;
	sort(all(p));
	reverse(all(p));
	sort(all(sw));
	reverse(all(sw));
	for (int i=0;i<n;i++){
		retrieval[i] = sw[i].s;
	}
	int best=-1;
	pii fro={-1,-1};
	dp[0].set((0),true);
	for(int i=1;i<=n;i++){
		int w=p[i-1];
		dbg(w);
		for(int j=0;j<100003;j++){
			dp[i].set(j, dp[i-1][j]);
			if(j>=w and dp[i-1].test(j-w)){
				dp[i].set((j), true);
			}
			if(j>=best and j-w<hoshii and j>=hoshii and dp[i].test(j)){
				fro={i,j};
				best=j;
			}
		}
	}
	if(best == -1) {
		cout<<"0\n";
		return 0;
	}
	vector<int> things;
	int q = fro.s;
	for (int i=fro.f;i>=1;i--) {
		dbg(i, q);
		int w = p[i-1];
		if(q-w >= 0 and dp[i-1].test(q-w)){
			things.push_back(i);
			q -= w;
		}
	}
	cout<<things.size()<<"\n";
	for(auto i : things)cout<<retrieval[i-1]<<" ";
	cout<<"\n";
}
