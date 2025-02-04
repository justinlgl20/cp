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
    int n, m, q; cin >> n >> m >> q;
    vector<int> a(n+1), b(m+1), pos_in_a(n+4, 0);
    vector<set<int>> poses(n+1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos_in_a[a[i]] = i;
        poses[i].insert(1e9);
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
        poses[b[i]].insert(i);
    }
    vector<bool> good(n+1, 1);
    int badness = 0;
    for (int i = 1; i <= n; i++) {
        if (i < n and !((*poses[a[i]].begin()) <= (*poses[a[i+1]].begin()))) {
            good[i] = false;
        }
        if (i > 1 and !((*poses[a[i-1]].begin()) <= (*poses[a[i]].begin()))) {
            good[i] = false;
        }
        badness += good[i]==0;
    }
    function<void(int)> recalc = [&](int i) {
        if (i <= 0 or i > n) return;
        badness -= good[i] ==0;
        good[i] = 1;
        if (i < n and !((*poses[a[i]].begin()) <= (*poses[a[i+1]].begin()))) {
            good[i] = false;
        }
        if (i > 1 and !((*poses[a[i-1]].begin()) <= (*poses[a[i]].begin()))) {
            good[i] = false;
        }
        badness += good[i]==0;

    };
    function<void()> print = [&]() {
        if (badness) {
            cout << "TIDAK\n";
        } else {
            cout << "YA\n";
        }
    };
    print();
    for (int _ = 0; _ < q; _++) {
        int s, t; cin >> s >> t;
        int prev_bi = b[s];
        b[s] = t;
        poses[prev_bi].erase(poses[prev_bi].find(s));
        poses[t].insert(s);
        for (int i = 1; i <= n; i++) {
            dbg(a[i], poses[a[i]]);
        }
        recalc(pos_in_a[prev_bi]);
        recalc(pos_in_a[prev_bi]+1);
        recalc(pos_in_a[prev_bi]-1);
        recalc(pos_in_a[b[s]]);
        recalc(pos_in_a[b[s]]+1);
        recalc(pos_in_a[b[s]]-1);
        print();
        
    }
    return;
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
