#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> x) {
    os << "{" << x.first << ", " << x.second << "}";
    return os;
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


int32_t main() {
    int q; cin >> q;
    int ans = 0;
    set<int> stuff;
    unordered_map<int, int> a, b, c;
    bool h = 0; // have had erase duplicates operation
    while (q--) {
        dbg(c[2]);
        dbg(a[2]);
        int t; cin >> t;
        if (t == 1) {
            int x, y; cin >> x >> y;
            a[x] += y;
            ans += y;
            stuff.insert(x);
        } else if (t == 2) {
            int x, y; cin >> x >> y;
            int prev_ax = a[x];
            a[x] -= y;
            a[x] = max(a[x], -c[x]);
            ans -= prev_ax-a[x];
        } else if (t == 3) {
            ans = 0;
            for (auto i : a) {
                if (c[i.f]+i.s >= 0) {
                    dbg(i.f);
                    c[i.f] = 1;
                    ans += 1;
                }
            }
            a.clear();
        } else {
            int g; cin >> g;
            cout << max(a[g]+c[g], 0ll) << "\n";
        }
    }
}
