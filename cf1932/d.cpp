#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 template<typename t, typename v>
ostream& operator<<(ostream& os, pair<t, v> g) {
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

#define pii pair<char, int>
#define f first
#define s second

void solve() {
    int n; cin >> n;
    n *= 2;
    char t; cin >> t;
    function<bool(pii, pii)> edge = [&](pii a, pii b) {
        if (a.f == b.f and a.s != b.s) return true;
        if (a.f != b.f and a.f != t and b.f != t) return false;
        return true;
    };
    map<pii, int> id;
    vector<vector<int>> adj(n+4, vector<int>());
    vector<pii> stuff;
    for (int i = 0; i < n; i++) {
        char a, b; cin >> a >> b;
        stuff.emplace_back(b, a-'0');
        id[stuff[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (edge(stuff[i], stuff[j])) {
                    adj[i].push_back(j);
                    dbg(i, j);
                }
            }
        }
    }
    vector<int> seen(n+3);
}
int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
