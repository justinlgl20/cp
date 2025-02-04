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

inline int lastbit(int x) {
  return x & (-x);
}

template <int... ArgsT> struct BIT {
  int val = 0;
  void update(int val) {
    this->val += val;
  }
  int query() {
    return val;
  }
};

template <int N, int... Ns>
struct BIT<N, Ns...> {
  BIT<Ns...> bit[N + 1];
  template<typename... Args>
  void update(int pos, Args... args) {
    for (; pos <= N; bit[pos].update(args...), pos += lastbit(pos));
  }
  template<typename... Args>
  int query(int l, int r, Args... args) {
    int ans = 0;
    for (; r >= 1; ans += bit[r].query(args...), r -= lastbit(r));
    for (--l; l >= 1; ans -= bit[l].query(args...), l -= lastbit(l));
    return ans;
  }
};

BIT<1005,1005> tree;

int a[1005][1005];

int32_t main() {
	int h,w;cin>>h>>w;
	int l=1e9,r=-1;
	int t=1e9,b=-1;
	dbg(l, r, t, b);
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++){
			char q;cin>>q;
			tree.update(i, j, (q=='.'));
			a[i][j]=(q=='.');
			if(q=='#'){
				l=min(l,i);
				r=max(r,i);
				t=min(t,j);
				b=max(b,j);
			}
		}
	}
	if(tree.query(l,r,t,b)>=1){
		cout<<"No\n";
	} else {
		cout<<"Yes\n";
	}

}
