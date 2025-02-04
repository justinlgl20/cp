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

int tringle(int n) {
	return n*(n+1ll)/((int)2);
}

int ssum(int l, int r, int k) {
	// first k of l to r
	// l to l+k-1 inclusive
	r = min(r,l+k-1);
	return tringle(r)-tringle(l-1ll);

}
int bsum(int l, int r, int k) {
	// last k of l to r
	l = max(l, r-k+1);
	return tringle(r)-tringle(l-1ll);
}

void fail() {
	cout << "-1\n";
	exit(0);
}

int32_t main() {
	queue<int> t; // to place on 0s
	queue<int> w; // to place on 1s
	int n,k;cin>>n>>k;
	vector<int> a(n),b(n,0);
	dbg(ssum(2,10,5));
	vector<int> available;
	int ones=0;
	
	for(int i=0;i<n;i++){available.push_back(i+1);cin>>a[i];ones+=(a[i]==1);}
	reverse(all(available));
	for (int i =0;i<n;i++) {
		dbg(k, ones, available);
		if (a[i]==1) {
			// is making k-min with (ones-1) of 2 to n possible
			if (w.size()) {
				b[i] = w.front();
				dbg(i, b[i]);
				w.pop();
				continue;
			}
			bool placed=0;
			while (available.size()) {
				if (ssum(available.back()+1,n, ones-1)<= k-available.back() and k-available.back() <= bsum(available.back()+1,n,ones-1)) {
					// place available.back()
					b[i] = available.back();
					k-=b[i];
					dbg(i, b[i]);
					available.pop_back();
					placed=1;
					ones--;
					break;
				} else {
					t.push(available.back());
					available.pop_back();
				}
			}
			if(!placed)fail();
		} else {
			if (t.size()) {
				b[i] = t.front();
				dbg(i, b[i]);
				t.pop();
				ones-=(a[i]==1);
				continue;
			}
			bool placed=0;
			while (available.size()) {
				if (ssum(available.back()+1,n,ones)<= k and k<= bsum(available.back()+1,n,ones)) {
					b[i] = available.back();
					available.pop_back();
					dbg(i, b[i]);
					placed=1;
					break;
				} else {
					w.push(available.back());
					k-=available.back();
					ones--;
					available.pop_back();
				}
			}
			if (!placed)fail();
		}
	}
	for (auto i:b)cout<<i<<" ";
	cout<<"\n";
}
