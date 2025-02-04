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
#define dbg(x...)%m
#endif

int nxt() {
    int g; cin >> g; return g;
}

#define pii pair<int, int>
#define f first
#define s second

void solve() {
    int n, m; cin >> n >> m;
    vector<int> g;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        g.push_back(c);
    }
    int l = 0, r = n-1;
    vector<pii> poses;
    for (int _ = 0; _ < n; _++) {
        assert(l <= r);
        char i; cin>>i;
        poses.push_back(make_pair(l, r));
        if (i == 'L') {
            l += 1;
        } else {
            r -= 1;
        }
    }
    reverse(all(poses));
    int val = g[poses[0].f];
    val %= m;
    vector<int> anses;
    anses.push_back(val);
    for (int i = 1; i < n; i++) {
        if (poses[i].f == poses[i-1].f-1) {
            val *= g[poses[i-1].f - 1];
            val %= m;
        } else {
            val *= g[poses[i-1].s+1];
            val %= m;
        }
        anses.push_back(val%m);
    }
    reverse(all(anses));
    for (auto i : anses) cout << i << " ";
    cout << "\n";
}

int32_t main() {
    int t; cin >> t; while (t--) solve();
}
