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
    sort(all(ranges));
    dbg(ranges);
    dbg(other);
    vector<int> l, r;
    for (auto i : ranges) {l.push_back(i.f); r.push_back(i.s);}
    //theres a range which we can bsearch to find and see if it works, starting at after li
    // query that range on the 
   
    dbg(l);
    for (int _ = 0; _ < q; _++) {
        int ql, qr; cin >> ql >> qr;
        bool works = false;
        for (auto i : ranges) {
            if ( ql <= i.f and i.s <= qr) works = true;
        }
        for (auto i : other) {
            if (i.f <= ql and qr <= i.s) works = true;
        }
        if (works) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
}
