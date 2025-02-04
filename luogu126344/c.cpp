#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> g) {
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

#define pii pair<int, int>
#define f first
#define s second

void solve() {
    string x; cin >> x;
    vector<int> a, b, c;
    for (int i = 1; i <= x.size(); i++) {
        if (x[i-1] == 'A') {
            a.emplace_back(i);
        } else if (b.size() < a.size() and x[i-1] == 'P') {
            b.push_back(i);
        } else if (c.size() < b.size() and x[i-1] == 'C'){
            c.push_back(i);
        }
    }
    int g = min({a.size(), b.size(), c.size()});
    vector<int> removed(x.size()+3, 0);
    for (int i = 0; i < g; i++) {
        removed[a[i]] = 1;
        removed[b[i]] = 1;
        removed[c[i]] = 1;
    }
    for (int i = 0; i < x.size(); i++) {
        if (!removed[i+1]) cout << x[i];
    }
    if (g == x.size()/3 + 10*x.size()%3) cout << "Perfect";
    cout << "\n";
    cout << g << "\n";
    for (int i = 0; i < g; i++) {
        cout << a[i] << " " << b[i] << " " << c[i] << "\n";
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
