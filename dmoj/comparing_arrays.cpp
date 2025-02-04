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
    int x; cin >> x; return x;
}

int n;

const int MOD = 1e9;
const int p = 31;

struct state {
    int v, length;
    bool operator == (state &other) const {
        return ((v == other.v) and (length == other.length));
    }
};

int stuff(int a, int b, int c) {
    // a * b^c
    int ans = 1;
    while (c > 0) {
        if (c & 1) {
            ans = ans*b;
            ans %= MOD;
        }
        c >>= 1ll;
        b = b*b;
        b = b % MOD;
    }
    return (ans * (a%MOD))%MOD;
}

state merge(state a, state b) {
    return state{(stuff(a.v, p, b.length) + b.v%MOD)%MOD, a.length+b.length};
}

struct seg {
    state val;
    int tl, tr;
    seg *l, *r;
    seg (int tl, int tr) {
        this->tl = tl;
        this->tr = tr;
        if (tl == tr) {
            this->val = state{0, 1};
            return;
        }
        int tm = (tl+tr)>>1;
        l = new seg(tl, tm);
        r = new seg(tm+1, tr);
        this->val = merge(l->val, r->val);
    }
    void update(int pos, int v) {
        if (tl == tr) {
            this->val = state{v, 1};
            return;
        }
        int tm = (tl+tr)/2;
        if (pos <= tm) {
            l->update(pos, v);
        } else {
            r->update(pos, v);
        }
        this->val = merge(l->val, r->val);
    }
    state query(int ql, int qr) {
        if (ql <= tl and tr <= qr) return val;
        if (ql > tr or qr < tl) return state{0, 0};
        state qwl = l->query(ql, qr);
        state qwr = r->query(ql, qr);
        if (qwl.v == 0) return qwr;
        if (qwr.v == 0) return qwl;
        return merge(qwl, qwr);
    }
    void print() {
        dbg(tl, tr, val.v, val.length);
        if (tl == tr) return;
        l->print();
        r->print();
    }
};

seg *tree;
int32_t main() {
    int q; cin >> n >> q;
    vector<int> a(n);
    generate(all(a), nxt);
    tree = new seg(0, n);
    unordered_map<int, int> compress;
    int inx = 1;
    for (int i = 0; i < n; i++) {
        if (compress.find(a[i]) == compress.end()) {
            compress[a[i]] = inx;
            a[i] = inx++;
        }
        else a[i] = compress[a[i]];
        dbg(a[i]);
    }
    for (int i = 0; i < n; i++) {
        tree->update(i, a[i]);
    }
    while (q--) {
        int a; cin >> a;
        if (a == 1) {
            int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
            l1--;r1--;l2--;r2--;
            int q = (tree->query(l1, r1)).v;
            int w = ((tree->query(l2, r2)).v);
            dbg(q, w);
            cout << (q == w) << "\n";
        } else {
            int p, v; cin >> p >> v;
            if (compress.find(v) == compress.end()) {
                v = inx++;
                compress[v] = inx-1;
            } else {
                v = compress[v];
            }
            tree->update(p, v);
        }
    }
}
