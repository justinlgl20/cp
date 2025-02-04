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

int nxt() {
    int x; cin >> x;
    return x;
}

set<int> boys;
set<int> girls;

int32_t main() {
    int n, q; cin >> n >> q;
    vector<pair<int, int>> peeps;
    for (int i = 1; i <= n; i++) {
        peeps.push_back({nxt(), 1});
    }
    for (int i = 0;i < n; i++) {
        peeps.push_back({nxt(), 0});
    }
    int ans = 0;
    sort(all(peeps));
    for (auto i : peeps) {
        if (i.second == 0) {
            girls.insert(i.first);
        }
        else {
            boys.insert(i.first);
        }
        while (boys.size() and girls.size()) {
            ans += abs((*boys.begin()) - (*girls.begin()));
            boys.erase(boys.begin());
            girls.erase(girls.begin());
        }
    }
    cout << ans << "\n";
}
