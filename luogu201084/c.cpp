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

#define pii pair<int, int>
#define f first
#define s second

struct Val {
    int sum;
    int t0third, t1third, t2third;
    Val() {
        sum = 0;
        t1third = 0, t2third = 0; t0third = 0;
    }
    Val(int a, int b, int c, int d) : sum(a), t0third(b), t1third(c), t2third(d) {}
    Val operator + (Val & other) const {
        Val result = Val();
        result.sum = sum + other.sum;
        result.t1third = t1third + other.t1third;
        result.t2third = t2third + other.t2third;
        result.t0third = t0third + other.t0third;
        return result;
    }
};

struct node {
    Val v;
    int lazy;
    int tl, tr;
    
};
node t[2000005];
void push(int n) {
    if (t[n].lazy) {
        t[n].v.sum += ((int)(2*t[n].lazy/3))*(t[n].tr-t[n].tl+1ll);
        int x = (2*t[n].lazy)%3;
        dbg(x);
        if (x > 0) {
            for (int j = 0; j < x; j++) {
                t[n].v.sum += t[n].v.t2third;
                int q = t[n].v.t2third;
                t[n].v.t2third = t[n].v.t1third;
                t[n].v.t1third = t[n].v.t0third;
                t[n].v.t0third = q;
            } 
        } else {
            for (int j = 0; j > x; j--) {
                t[n].v.sum -= t[n].v.t0third;
                int q = t[n].v.t0third;
                t[n].v.t0third = t[n].v.t1third;
                t[n].v.t1third = t[n].v.t2third;
                t[n].v.t2third = q;
            }
        }
        if (t[n].tl != t[n].tr) {
            t[2*n].lazy += t[n].lazy;
            t[2*n+1].lazy += t[n].lazy;
        }
        t[n].lazy = 0;
    }
}

const int MAXN = 500005;

void build(int n=1, int tl=0, int tr = MAXN) {
    t[n].tl = tl; 
    t[n].tr = tr;
    t[n].v = Val();
    t[n].lazy = 0;
    if (tl == tr) return;
    int tm = (tl+tr)>>1;
    build(n*2, tl, tm);
    build(n*2+1, tm+1, tr);
}

void upd(int ql, int qr, int v, int n=1, int tl = 0, int tr = MAXN) {
    if (tl > qr or ql > tr) return;
    push(n);
    if (ql <= tl and tr <= qr) {
        t[n].lazy += v;
        push(n);
        return;
    }
    int tm = (tl+tr)/2;
    upd(ql, qr, v, n*2, tl, tm);
    upd(ql, qr, v, n*2+1, tm+1, tr);
    push(n*2); push(n*2+1);
    t[n].v = t[n*2].v + t[n*2+1].v;
}

void updi(int p, int v, int n=1, int tl = 0, int tr = MAXN) {
    if (tl == tr) {
        t[n].v.sum = 2*v/3;
        if (((2*v)%3) == 0) {
            t[n].v.t0third ++;
        } else if (((2*v)%3) == 1) {
            t[n].v.t1third++;
        } else {
            t[n].v.t2third++;
        }
        return;
    }
    int tm = (tl+tr)/2;
    if (p <= tm) {
        updi(p, v, n*2, tl, tm);
    } else {
        updi(p, v, n*2+1, tm+1, tr);
    }
    t[n].v = t[n*2].v + t[n*2+1].v;
}

int query(int ql, int qr, int n = 1, int tl = 0, int tr = MAXN) {
    if (tl > qr or ql > tr) return 0ll;
    push(n);
    if (ql <= tl and tr <= qr) {
        return t[n].v.sum;
    }
    int tm = (tl+tr)/2;
    return query(ql, qr, n*2, tl, tm) + query(ql, qr, n*2+1, tm+1, tr);
}

int32_t main() {
    Val v = Val(6, 0, 2, 0);
    t[0].v = v;
    t[0].tl = 2; t[0].tr = 3;
    t[0].lazy = 4;
    dbg(t[0].v.sum, t[0].v.t0third, t[0].v.t1third, t[0].v.t2third);
    push(0);
    dbg(t[0].v.sum, t[0].v.t0third, t[0].v.t1third, t[0].v.t2third);
    t[0].lazy = -4;
    push(0);

    dbg(t[0].v.sum, t[0].v.t0third, t[0].v.t1third, t[0].v.t2third);
    build();
    int n, q; cin >> n >> q;
    vector<int> a(n+4, 0);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        updi(i, 2*x);
    }
    while (q--) {
        int i; cin >> i;
        if (i == 1) {
            int l, r, x; cin >> l >> r >> x;
            upd(l, r, 2*x);
        } else {
            int l, r; cin >> l >> r;
            cout << query(l, r) << "\n";
        }
    }
}
