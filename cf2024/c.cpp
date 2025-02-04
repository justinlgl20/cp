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

int inversions(vector<int>&a, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) cnt++;
        }
    }
    return cnt;
}

void solve() {
    int n; cin >> n;
    vector<pii> g;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        g.emplace_back(a, b);
    }
    sort(all(g), [&](pii a, pii b) {
            return a.f+a.s < b.f+b.s;
            });
    vector<int> a;
    for (auto i : g) {
        a.push_back(i.f); a.push_back(i.s);
    }
    for (auto i : g) {
        cout << i.f << " " << i.s << " ";
    }
    cout << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
