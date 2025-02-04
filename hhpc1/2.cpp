#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> x) {
    os << "{" << x.first << ", "<< x.second << "}";
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

vector<int> neg[1000005];

struct seg {
    int n;
    vector<int> t;

    seg(int n) {
        this->n = n;
        t.resize(4*n+4);
        for (int i = 0; i <= 4*n+3; i++) t[i] = 1e18;
    }
    void upd(int p, int value) {
        for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = min(t[p], t[p^1]);
    }

    int query(int l, int r) {
        r += 1;
        int res = 1e18;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res, t[l++]);
            if (r&1) res = min(res, t[--r]);
        }
        return res;
    }
};

int32_t main() {
    int n, q; cin >> n >> q;
    vector<int> a(n+3);
    vector<pii> ranges;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        if (a[i] < 0) {
            neg[abs(a[i])].push_back(i);
        }
        if (a[i] == 0) ranges.emplace_back(i, i);
    }

    dbg("HII")
    
    vector<pii> other;
    int st = 1;
    int val = a[1];
    for (int i = 2; i <= n; i++) {
        if (a[i] != val) {
            other.emplace_back(st, i-1);
            val = a[i];
            st = i;
        }
    }
    other.emplace_back(st, n);
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            if (!neg[a[i]].size()) continue;
            auto g = upper_bound(all(neg[a[i]]), i);
            auto k = lower_bound(all(neg[a[i]]), i);
            if ((*g) >= i and g != neg[a[i]].end()) {
                int q = (*g);
                ranges.emplace_back(i, q);
                dbg(i, q);
            }
            if (neg[a[i]].front() < i) {
                if (k != neg[a[i]].end()) {
                    dbg(neg[a[i]]);
                    dbg(*k, *(k-1))
                    int q = (*(k-1));
                    assert(q <= i);
                    ranges.emplace_back(q, i);
                    dbg(q, i);
                } else {
                    int q = neg[a[i]].back();
                    if (q <= i) {
                        ranges.emplace_back(q, i);
                        dbg(q, i);
                    }
                }
            }
        }
    }
    ranges.emplace_back(0, 1e9);
    sort(all(ranges));
    dbg(ranges);
    dbg(other);
    vector<int> l, r;
    for (auto i : ranges) {l.push_back(i.f); r.push_back(i.s);}
    //theres a range which we can bsearch to find and see if it works, starting at after li
    // query that range on the 
    seg tree = seg(r.size()+5);
    for (int i = 0; i < r.size(); i++) {
        tree.upd(i, r[i]);
    }
    dbg(l);
    for (int _ = 0; _ < q; _++) {
        int ql, qr; cin >> ql >> qr;
        // check if it works in other first
        int lo = 0;
        for (int add = 1<<30; add > 0; add>>=1) {
            if (lo + add < other.size() and other[lo+add].first <= ql) lo += add;
        }
        dbg(lo, ql, qr);
        if (other[lo].f <= ql and qr <= other[lo].s) {
            cout << "YES\n";
            continue;
        }
        lo = 0;
        for (int add = 1<<30; add > 0; add>>=1) {
            if (lo + add < l.size() and l[lo+add] < ql) lo += add;
        }
        int en = 0;
        for (int add = 1<<30; add > 0; add>>=1) {
            if (en+add < l.size() and l[en+add] <= qr) en += add;
        }
        dbg(ql, qr, lo);
        if (l[lo] < ql)
            lo += 1;
        if (lo >= l.size()) {
            cout << "NO\n"; continue;
        }
        int a = tree.query(lo, en);
        if (a <= qr) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
}
