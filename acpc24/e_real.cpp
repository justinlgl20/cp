#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T, typename V>
ostream& operator<<(ostream& os,pair<T,V>t){
	os<<"{"<<t.first<<", "<<t.second<<"}";return os;
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

int a[305][305];
int dp[305][305];
bool illegal[305][305];
vector<pii> dependencies[305][305]; // sorted by x then y i think

int32_t main() {
	int n,m,k;cin>>n>>m>>k;
	for (int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>a[i][j];

	for (int i=0;i<n;i++){
		for(int j =0;j < m;j++) {
			priority_queue<pii> must;
			bool illega=0;
			unordered_map<int, unordered_map<int, bool>> s;
			for(int x = -k/2;x<=k/2 and!illega;x++){
				for(int y=-k/2;y<=k/2 and!illega;y++){
					if(i+x< 0 or i+x>=n or j+y<0 or j+y>=m)continue;
					if(x <= 0 and y<=0 and a[i+x][j+y] > a[i][j]) {
						if (x==0 and y==0)continue;
						dependencies[i][j].push_back(make_pair(i+x,j+y));
						must.push(make_pair(i+x, j+y));
						s[i+x][j+y]=1;
						illega=illega or illegal[i+x][j+y];
					}
					if (x > 0 or y>0) {
						illega=illega or (a[i+x][j+y] > a[i][j]);
					}
				}
			}
			
			pii last = make_pair(i, j);
			int cnt=0;
			dp[i][j]=a[i][j];
			s[i][j]=1;
			while (must.size() and !illega) {
				pii u = must.top();
				dbg(u.f, u.s);
				must.pop();
				if(cnt > i+j+4){illega=1;break;}
				
				if(u.f <= last.f and u.s <= last.s) {
					dp[i][j]+=a[u.f][u.s];
					last=u;
					// add all of this one's dependencies in
					for (auto q : dependencies[u.f][u.s]) {
						if(s.find(q.f)!=s.end() and s[q.f].find(q.s)!=s[q.f].end()) continue;
						must.push(q);
						s[q.f][q.s]=1;
						illega=illega or illegal[q.f][q.s];
						cnt++;
						if (cnt>i+j+3) {
							illega=1;break;
						}
					}
				} else {
					illega=1;
				}
			}
			if(illega) {
				illegal[i][j]=1;
				dp[i][j]=0;
				
			} else {
				int add=0;
				if (last.f > 0) add=max(add,dp[last.f-1][last.s]);
				if (last.s > 0) add=max(add,dp[last.f][last.s-1]);
				// add stuff under last.f, last.s into it
				dp[i][j]+=add;
			}
			dbg(i, j, dp[i][j]);
			dbg( dependencies[i][j]);
			dbg(illegal[i][j]);
			if (i > 0) dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if (j > 0) dp[i][j]=max(dp[i][j],dp[i][j-1]);

		}
	}
	cout<<dp[n-1][m-1]<<"\n";

}
