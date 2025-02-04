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

int32_t main() {
    int n, q; cin >> n >> q;
    char last; cin >> last;
    set<int> bad;
    for (int i = 0; i < n-1; i++) {
        char c; cin >> c;
        if (c == last) bad.insert(i+1);
        last = c;
    }
    
    while (q--) {
        int a, b, c; cin >> a >> b >> c;
        if (a == 1) {
            if (b > 1 and bad.find(b-1) == bad.end()) bad.insert(b-1);
            else bad.erase(b-1);
            if (c < n and bad.find(c) == bad.end()) bad.insert(c);
            else bad.erase(c);
        } else {
            dbg(bad);
            auto it = bad.lower_bound(c);
            auto it2 = bad.lower_bound(b);
            if (it == it2) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
}
