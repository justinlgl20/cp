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
    int u; cin >> u; return u;
}

vector<int> a, b;
vector<int> pos_in_b;
#define pii pair<int, int>
#define f first
#define s second
set<pii> edges;
void stuff(int tl, int tr, int ql, int qr, int par) {
    dbg(tl, tr, ql, qr, par);
    if (tl == tr) {return;
    edges.insert(make_pair(a[tl], par));}
    int l;
    for (l = tl; l <= tr;) {
        int b_pos = pos_in_b[a[l]];
        int r = l+(qr-(b_pos+1))+1;
        edges.insert(make_pair(a[l], par));
        stuff(l+1, r, b_pos+1, qr, a[tl]);
        qr = b_pos-1;
        l = r+1;
    }
}

int32_t main() {
    int n = nxt();
    pos_in_b.resize(n+5);
    a.resize(n);
    b.resize(n);
    generate(all(a), nxt);
    generate(all(b), nxt);
    dbg(a);
    dbg(b);
    for (int i = 0; i < n; i++) {
        pos_in_b[b[i]] = i;
    }
    stuff(1, n-1, 1, n-1, 1);
    for (auto i : edges) cout << i.f << " " << i.s << "\n";
}
