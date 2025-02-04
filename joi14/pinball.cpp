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
    int c; cin >> c; return c;
}

struct Device {
    int l, int r;
    int height;
    int centre;
    Device(int l, int r, int h, int c) {
        this->l = l; this->r = r;
        this->height = h;
        this->centre = c;
    }
    bool operator < (const Device &other) const {
        if (height == other.height) return centre < other.centre;
        return height < other.height;
    }
};

struct segtree{
    vector<int> t;
    int n;
    segtree(int n) {
        this->n = n;
        t.resize(3*n+5);
        for (int i = 0; i < 3*n+4; i++) t[i] = 1e9;
    }
    void update(int p, int v) {
        for (t[p + n] = min(t[p+n], v), p+=n; p > 1; p>>=1) {
            t[p>>1] = min(t[p], t[p^1]);
        }
    }
    int query(int l, int r) {
        int res = 1e9;
        for (l +=n, r+=n; l < r; l>>=1,r>>=1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(res, t[--r]);
        }
        return res;
    }
};

segtree* dp[2];


