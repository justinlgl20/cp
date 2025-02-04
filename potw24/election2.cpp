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

bool dp[305][100005];
// COULD DO 100000 * sqrt 100000 WITH THE C SQRT C TRICK
pii from[305][100005];
vector<int> retrieval[100005];

int32_t main() {
	int n;cin>>n;
	vector<int> p(n);
	int s=0;
	for(int i=0;i<n;i++){
		cin>>p[i];retrieval[p[i]].emplace_back(i+1);s+=p[i];
	}
	int hoshii=s/2+(s%2);
	sort(all(p));
	reverse(all(p));
	int best=-1;
	pii fro={-1,-1};
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		int w=p[i-1];
		dbg(w);
		for(int j=0;j<100003;j++){
			dp[i][j]=dp[i-1][j];
			from[i][j]=make_pair(i-1,j);
			if(j>=w and dp[i-1][j-w]){
				dp[i][j]=1;
				from[i][j]={i-1,j-w};
			
			}
			if(j>=best and j-w<=hoshii and j>=hoshii and dp[i][j]){
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
	while (fro.f != 0) {
		things.push_back(fro.s-from[fro.f][fro.s].s);
		fro = from[fro.f][fro.s];
	}
	dbg(best);
	dbg(things);
	vector<int> retri;
	for(auto i : things) {
		if(i != 0) {
			retri.push_back(retrieval[i].back());
			retrieval[i].pop_back();
		}
	}
	cout<<retri.size()<<"\n";
	for(auto i : retri)cout<<i<<" ";
	cout<<"\n";
}
