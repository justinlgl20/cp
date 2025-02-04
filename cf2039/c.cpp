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

#define one ((int)1ll)

void solve() {
    int _x, _m; cin >> _x >> _m;
    int x = _x;
    int m = _m;
    int ans = 0;
    int g = ceil(log2((int64_t)((int64_t)x+one+one+one)));
    //dbg(g);
    int k = (one<<g) - one;
    int q = 1;
    for (int i = 61-g; i >= 0; i--) {
        if ((((q+(one<<i)) * x)|k) <= m) q += one<<i;
    }
    dbg(q, x, q*x, (m|k)/x, m);
    ans = q-one;
    // we have q thingies and q is within x of m
    for (int i = q+one; i <= (m|k)/x+one+one+one; i++) {
        if (((i*x)^x) <= m) {
            ans++;
        }
    }
    //dbg(ans);
    // WE NOW HAVE COUNTED ALL THINGS WHICH ARE DIVISIBLE BY X
    // NOW WE GOTTA DO THE THINGS DIVISIBLE BY Y
    int ys = 0;
    for (int i = 1; i <= min(m, one<<(g)); i++) {
        if ((i^x) % i == 0 and ((i^x) == 0 or (i^x) == x or (i^x) % x != 0)) {
            //dbg(i^x, i);
            ys++;
        }
    }
    dbg(ans, ys);
    int64_t we = ans+ys;
    cout << we << "\n";
}

int32_t main() {
    int32_t t; cin >> t;

    while(t--) solve();
}
