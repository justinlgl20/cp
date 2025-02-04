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

int32_t main() {
    int n, qw; cin >> n >> qw;
    int m, x, y; cin >> m >> x >> y;
    function<int(int, int, int)> id = [&](int i, int j, int k) {
        return i * n * n + j*n + k;
    };
    map<int, int> stuff;
    for (int _ = 0; _ < m; _++) {
        int i = 0, j = 0, k = 0;
        if (qw == 1) cin >> k;
        if (qw == 2) cin >> j >> k;
        if (qw == 3) cin >> i >> j >> k;
        dbg(i, j, k, id(i, j, k));
        stuff[id(i, j, k)] = 1;
    }
    for (int _ = 0; _ < x; _++) {
        int i = 0, j = 0, k = 0;
        if (qw == 1) cin >> k;
        if (qw == 2) cin >> j >> k;
        if (qw == 3) cin >> i >> j >> k;
        dbg(i, j, k, id(i, j, k));
        stuff[id(i, j, k)] = 2;
    }
    vector<pair<int, pii>> coaches;
    for (int _ = 0; _ < y; _++) {
        int i = 0, j = 0, k = 0;
        if (qw == 1) cin >> k;
        if (qw == 2) cin >> j >> k;
        if (qw == 3) cin >> i >> j >> k;
        dbg(i, j, k, id(i, j, k));
        coaches.emplace_back(i, make_pair(j, k));
        stuff[id(i, j, k)] = 3;
    }
    for (auto _ : coaches) {
        int i = _.f, j = _.s.f, k = _.s.s;
        int ans = 0;
        for (int m = i-1; m > 0; m--) {
            if (stuff.find(id(m, j, k)) != stuff.end()) {
                if (stuff[id(m, j, k)] == 1) ans++;
                break;
            }
        }
        for (int m = j-1; m > 0; m--) {
            if (stuff.find(id(i, m, k)) != stuff.end()) {
                if (stuff[id(i, m, k)] == 1) ans++;
                break;
            }
        }
        for (int m = k-1; m > 0; m--) {
            if (stuff.find(id(i, j, m)) != stuff.end()) {
                if (stuff[id(i, j, m)] == 1) ans++;
                break;
            }
        }
        for (int m = i+1; m <= n; m++) {
            if (stuff.find(id(m, j, k)) != stuff.end()) {
                if (stuff[id(m, j, k)] == 1) ans++;
                break;
            }
        }
        for (int m = j+1; m <= n; m++) {
            if (stuff.find(id(i, m, k)) != stuff.end()) {
                if (stuff[id(i, m, k)] == 1) ans++;
                break;
            }
        }
        for (int m = k+1; m <= n; m++) {
            if (stuff.find(id(i, j, m)) != stuff.end()) {
                if (stuff[id(i, j, m)] == 1) ans++;
                break;
            }
        }
        cout << ans << " ";

    }
    cout << "\n";
}
