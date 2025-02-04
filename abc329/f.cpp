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
    dbg(n);
    vector<set<int>*> balls(n+5);
    dbg(1);
    for (int i = 1; i <= n; i++) {
        balls[i] = new set<int>;
    }
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        (*(balls[i])).insert(c);
    }
    dbg(1);
    while (q--) {
        int a, b; cin >> a >> b;
        if ((*balls[a]).size() > (*balls[b]).size()) swap(balls[a], balls[b]);
        for (int i : (*balls[a])) {
            (*balls[b]).insert(i);
        }
        (*balls[a]).erase(all(*balls[a]));
        cout << (*balls[b]).size() << "\n";
    }
}
