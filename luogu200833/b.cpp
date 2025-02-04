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

struct seg {
    int tl,tr;
    pii val;
    seg *l, *r;
    seg(int tl, int tr) {
        this->tl = tl, this->tr = tr;
        if (tl == tr) return;
        int tm = (tl+tr)>>1;
        l = new seg(tl, tm);
        r = new seg(tm+1, tr);
    }
    void update(int p, int v) {
        if (tl == tr) {
            val = {v, tl};
            return;
        }
        int tm = (tl+tr)>>1;
        if (p <= tm) l->update(p, v);
        else r->update(p, v);
        this->val = max(l->val, r->val);
    }
    pii query(int ql, int qr) {
        if (ql > tr or tl > qr or ql > qr) return {-1e9, -1};
        if (ql <= tl and tr <= qr) return val;
        return max(l->query(ql, qr), r->query(ql, qr));
    }
};

int32_t main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    seg x = seg(0, n);
    for (int i = 0; i < n; i++) {
        x.update(i, a[i]-i);
    }
    vector<int> ans(n, -1e9);
    for (int i = 0; i < n; i++) {
        pii g = x.query(i+a[i], n-1);
        if (g.f >= -i) {
            ans[i] = g.s-i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] != -1e9) {
            cout << "1 " << ans[i] << "\n";
        } else {
            cout << "0\n";
        }
    }
}
