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

pii merge(pii a, pii b) {
    if (a.f == b.f) {
        return make_pair(a.f, a.s+b.s);
    }
    return max(a, b);
}

struct segtree {
    vector<pii> t;
    int n;
    segtree(int n) {
        this->n = 1;
        while (this->n < n) {
            this->n *= 2;
        }
        t.resize(4*this->n+5);
        for (int i = 0; i < 4*(this->n)+3; i++) t[i] = make_pair(0ll, 0ll);
    }
    
    void upd(int p, pii v) {
        p+=n;
        t[p] = merge(t[p], v);
        for (;p > 1; p>>=1) {
            t[p>>1] = merge(t[p], t[p^1]);
        }
    }
    pii query(int l, int r) {
        r++;
        pii ans = {0, 0};
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) {
                ans = merge(ans, t[l++]);
            }
            if (r&1) {
                ans = merge(ans, t[--r]);
            }
        }
        return ans;
    }
};

int32_t main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {cin >> a[i];a[i] -= i;a[i] += n;}
    segtree seg = segtree(200005);
    seg.upd(0, {0, 1});
    for (auto i : a) {
        pii q = seg.query(0, i);
        dbg(i, q.f, q.s);
    pii ans = {0ll, 0ll};
        seg.upd(i, make_pair(q.f+1, q.s));
    }
    pii ans = seg.query(0, 200004);
    cout << n-ans.f << "\n";
    cout << ans.s << "\n";
}
