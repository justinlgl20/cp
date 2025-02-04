#include <bits/stdc++.h>
using namespace std;
 
#define all(x) (x).begin(), (x).end()
 
#define int long long
 
template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> o) {
	os << "{"; int g = o.size(); for (auto i : o) os << i << ((--g)==0?"":", "); os << "}";
    return os;
}
 
void _print() {
	cout << "]\n";
}
 
template<typename T, typename ...V>
void _print(T t, V... v) {
	cerr << t; if (sizeof...(v)) cerr << ", "; _print(v...);
}
 
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" <<__func__ << ":" <<__LINE__ << " [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif
 
#define pii pair<int, int>
#define f first
#define s second

const int MOD=1e9+7;
 
vector<int> adj[200005];
int depth[200005];
int idk[200005], idk2[200005],idk3[200005];
 
int32_t main() {
    int n;cin>>n;
    vector<int> par(n+3,0);
    for(int i=2;i<=n;i++){
        int p;cin>>p;
	par[i]=p;
        adj[p].push_back(i);
	depth[i]=depth[p]+1ll;
    }
    vector<int> maxdepth(n+4,0);
    for(int i=n;i>=1;i--){
	    for(auto j:adj[i])maxdepth[i]=max(maxdepth[i],maxdepth[j]+1ll);
	    // gen best in subtree
    }
    idk[1]=-1e18;
    for(int i=1;i<=n;i++){
	    idk[i]=max(idk[i],depth[i]-1ll);
	    int bleh=idk[i];
	    for(auto j:adj[i]){
		    idk[j]=max(idk[j],bleh);
		    bleh=max(bleh,maxdepth[j]+depth[j]);
	    }
	    reverse(all(adj[i]));
	    bleh=depth[i]-1;
	    for(int j:adj[i]){
		    idk[j]=max(idk[j],bleh);
		    bleh=max(bleh,maxdepth[j]+depth[j]);
	    }
	    // gen best outside of this subtree then fix later
    }
    for(int i=1;i<=n;i++){
	    int _=0;
	    for(int j:adj[i]){
		    idk2[j]=max(idk2[j],_);
		    _=max(_,maxdepth[j]+1ll);
	    }
	    reverse(all(adj[i]));
	    _=0;
	    for(int j:adj[i]){
		    idk2[j]=max(idk2[j],_);
		    _=max(_,maxdepth[j]+1ll);
	    }
    }
    idk3[1]=-1e18;
    for(int i=2;i<=n;i++){
	    idk3[i]=max(
	    	idk[par[i]]+idk2[i]+1ll,
		idk3[par[i]]+1ll
	    );
    }
    int ans =maxdepth[1];
    for(int i=2;i<=n;i++){
	    ans *=max(
	    maxdepth[i]+idk[i]+1ll,
	    idk3[i]+1ll
	    );
	    ans %=MOD;
    }
    cout<<ans<<"\n";


}
