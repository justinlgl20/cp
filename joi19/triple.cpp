#include <bits/stdc++.h>
using namespace std;
 
// #define int long long
 
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

int scan() {
    int x; cin >> x; return x;
}

struct node {
    int l, r, val;
    node() {
        this->l = 0;
        this->r = 0;
        this->val = 0;
    }
    node(int a, int b, int v) {
        this->l = a; this->r = b; this->val = v;
    }
};

node merge(node a, node b) {
    return node(max(a.l, b.l), max(b.r, a.r), max({a.val, b.val, a.l+b.r}));
}

int n, q;

int value[500005];

struct seg {
    vector<node> T;
    int n;
    seg(int n) {
        this->n = n;
        T.resize(3*n+5);
        for (int i = 0; i < 3*n; i++) T[i] = node(0, 0, 0);
        for (int i = 0; i < n; i++) {
            T[i|n].r = T[i|n].val = value[i];
        }
        for (int i = n-1; i; i--) {
            T[i] = merge(T[i<<1], T[i<<1|1]);
        }
    }

    void upd(int x, int v) {
        x |= n;
        T[x].val = max(T[x].l, v)+T[x].r;
        T[x].l = max(T[x].l, v);
        while (x >>= 1) T[x] = merge(T[x<<1], T[x<<1|1]);
    }

    int query(int ql, int qr) {
        node l= node(0, 0, 0);
        node r = node(0, 0, 0);
        ql |= n; qr |= n;
        while (ql <= qr) {
            if (ql&1) l = merge(l, T[ql++]);
            if (~qr &1) r = merge(T[qr--], r);
            ql>>=1;
            qr>>=1;
        }
        return (merge(l, r)).val;
    }
};

seg *segtree;

vector<pii> queries[500005];
vector<pii> updates[500005];

int32_t main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> value[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r; cin >> l >> r;
        queries[l].emplace_back(r, i);
    }

    segtree = new seg(1<<16);
    stack<int> stck;
    dbg("...");
    for (int i = 1; i <= n; i++) {
        while (stck.size()) {
            int j = stck.top();
            if (value[i] > value[j]) {
                stck.pop();
                updates[j].emplace_back(i, value[i]+value[j]);
            } else {
                updates[j].emplace_back(i, value[i]+value[j]);
                break;
            }

            
        }
        stck.push(i);
    }
    vector<int> ans(q+3, 0);
    for (int i = n; i > 0; i--) {
        for (auto j : updates[i]) {
            if (2*j.f - i <= n) segtree->upd(2*j.f-i, j.s);
        }
        for (auto j : queries[i]) {
            ans[j.s] = segtree->query(i, j.f);
        }
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
}
