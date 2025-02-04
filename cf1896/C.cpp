#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename a, typename b>
ostream& operator << (ostream& os, pair<a, b> g) {
    os << "{" << g.first << ", " << g.second << "}";
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

int nxt() {
    int x; cin >> x; return x;
}

void solve() {
    int n, x; cin >> n >> x;
    vector<pair<int, int>> a(n);
    vector<int> b(n);
    int i = 0;
    generate(all(a), [&]() {
        int q = nxt();
        return make_pair(q, i++);
    });
    generate(all(b), nxt);
    sort(all(a));
    sort(all(b));
    dbg(a, b);
    vector<int> ideal(n, -1);
    for (int i = 0, j = n-x; j < n; i++,j++) {
        if (!(b[i] < a[j].first)) {
            dbg(i, j);
            dbg(b[i], a[j]);
            cout << "NO\n"; return;
        }
        ideal[a[j].second] = b[i];
    }
    for (int i = x, j = 0; i < n; i++,j++) {
        ideal[a[j].second] = b[i];
        if (a[j].first > b[i]) {
            cout << "NO\n"; return;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) cout << ideal[i] << " \n"[i==n-1];
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
