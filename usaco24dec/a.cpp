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

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> psa(n+1, 0);
    for (int i = 1; i <= n; i++) {
        psa[i] = psa[i-1]+a[i-1];
    }
    function<int(int, int)> sum = [&](int l, int r) {
        return psa[r+1]-psa[l];
    };
    int e = sum(n-(n/2-1), n-1);
    for (int i = 0; i < n/2-1; i++) {
        // from 0 to i is i+1 elements
        int o = sum(0, i);
        o += sum(n-(n/2-1-(i+1)), n-1);
        e = max(e, o);
    }
    int b = sum(0, n-1)-e;
    cout << b << " " << e << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
