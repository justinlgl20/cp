#include <bits/stdc++.h>
using namespace std;
  
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
    int x; cin >> x; return x;
}
int a[100005], b[100005];
vector<pair<int, int>> edges;
int pos_in_b[100005];

inline void dfs(int al, int ar, int bl, int br, int par) {
    if (al > ar or bl > br) return;
    dbg(al, ar, bl, br, par);
    if (ar-al != br-bl) return;
    edges.emplace_back(a[al], par);
    if (al == ar) return;
    int sz = br-(pos_in_b[a[al]]+1);
    dfs(al+1, al+1+sz, pos_in_b[a[al]]+1, br, a[al]);
    dfs(al+1+sz+1, ar, bl, pos_in_b[a[al]]-1, par);
}

int32_t main() {
#ifndef DEBUG
    freopen("cavernin.txt", "r", stdin);
    freopen("cavernout.txt", "w", stdout);
#endif
    int n = nxt();
    generate(a, a+n, nxt);
    generate(b, b+n, nxt);
    for (int i = 0; i < n; i++) pos_in_b[b[i]] = i;
    //dfs(1, n-1, 1, n-1, a[0]);
    stack<array<int, 5>> q;
    q.push({1, n-1, 1, n-1, a[0]});
    while (q.size()) {
        int al = q.top()[0];
        int ar = q.top()[1];
        int bl = q.top()[2];
        int br = q.top()[3];
        int par = q.top()[4];
        q.pop();
        if (al > ar or bl > br) continue;
        dbg(al, ar, bl, br, par);
        if (ar-al != br-bl) continue;
        edges.emplace_back(a[al], par);
        if (al == ar) continue;;
        int sz = br-(pos_in_b[a[al]]+1);
        q.push({al+1, al+1+sz, pos_in_b[a[al]]+1, br, a[al]});
        q.push({al+1+sz+1, ar, bl, pos_in_b[a[al]]-1, par});

    }
    for (auto i : edges) cout << i.first << " " << i.second << "\n";
}
