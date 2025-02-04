#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename A, typename B>
ostream& operator<<(ostream& os, pair<A, B> p) {
    os << "{" << p.first << ", " << p.second << "}";
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

int nxt() {
    int g; cin >> g; return g;
}

int n;
vector<pii> stuff;

void mark(int x, int y) {
    cout << x << " " << y << "\n";
}

void solve(int tl, int tr) {
    if (tl >= tr) return;
    int tm = (tl+tr)/2;
    int x_val = stuff[tm].f;
    dbg(tm);
    for (int i = tl; i <= tr; i++) {
        mark(x_val, stuff[i].s);
    }
    solve(tl, tm-1);
    solve(tm+1, tr);
}

int32_t main() {
    n = nxt();
    stuff.resize(n);
    generate(all(stuff), [&]() {
        int a = nxt(), b = nxt();
        return make_pair(a, b);
    });
    sort(all(stuff));
    solve(0, n-1);
}
