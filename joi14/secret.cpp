//#include "secret.h"
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

#ifdef DEBUG
int Secret(int a, int b) {
    return a+b;
}
#endif

int vals[15][1005]; //level, inx
vector<int> q[15];
int A[1005];
int n;

void build(int tl, int tr, int lvl) {
    assert(lvl < 15);
    if (tl == tr) {
        vals[lvl][tl] = A[tl];
        return;
    }
    int tm = (tl+tr)/2;
    // tm is the point
    q[lvl].push_back(tm);
    vals[lvl][tm] = A[tm];
    vals[lvl][tm+1] = A[tm+1];
    for (int i = tm-1; i >= tl; i--) vals[lvl][i] = Secret(vals[lvl][i+1], A[i]);
    for (int i = tm+2; i <= tr; i++) vals[lvl][i] = Secret(vals[lvl][i-1], A[i]);
    build(tl, tm, lvl+1);
    build(tm+1, tr, lvl+1);
}

void Init(int N, int Ad[]) {
    n = N;
    for (int i = 0; i < N; i++) {
        A[i] = Ad[i];
        for (int j = 0; j < 15; j++) vals[j][i] = -1;
    }
    dbg("HI");
    build(0, N-1, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 15; j++) {
            vals[j][i] = vals[j][i]==-1?A[i]:vals[j][i];
        }
    }
}

int ans(int tl, int tr, int lvl, int ql, int qr) {
    int tm = (tl+tr)/2;
    dbg(tl, tr, lvl, ql, qr);
    if (ql > tr or qr < tl) return -1;
    if (tl <= ql and qr <= tr and ((ql <= tm and tm <= qr)or(ql <= tm+1 and tm+1 <= qr)) ) {
        if (qr == tm) return vals[lvl][ql];
        else if (ql == tm+1) return vals[lvl][qr];
        return Secret(vals[lvl][ql], vals[lvl][qr]);
    } else if (tl <= ql and qr <= tr) {
        if (ql > tm) return ans(tm+1, tr, lvl+1, ql, qr);
        else if (qr <= tm) return ans(tl, tm, lvl+1, ql, qr);
        else {
            dbg(3/0);
        }
    } else {
        if (tl == tr) return -1;
        int a = ans(tm+1, tr, lvl+1, ql, qr), b = (ans(tl, tm, lvl+1, ql, qr));
        if (a == -1 and b == -1) {
            dbg(3/0);
        }
        assert(a!=-1 or b!=-1);
        if (a == -1) return b;
        return a;
    }
}

int Query(int ql, int qr) {
   return ans(0, n-1, 0, ql, qr); 
}

#ifdef DEBUG
int main() {
    int n, q; cin >> n >> q;
    vector<int> stuff(n);
    generate(all(stuff), nxt);
    dbg("HI");
    Init(n, data(stuff));
    while (q--) {
        int ql, qr; cin >> ql >> qr;
        cout << Query(ql, qr) << "\n";
    }
}
#endif
