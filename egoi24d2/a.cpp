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

int32_t main() {
    int n, m, q; cin >> n >> m >> q;
    vector<int> g(m);
    generate(all(g), nxt);
    vector<int> a = g;
    for (int i : g) {
        a.push_back(i+n);
    }
    sort(all(a));
    dbg(a);
    function<int(int, int)> dist = [&](int a, int b) {
        return min(abs(a-b), (int)2*n-abs(a-b));
    };
    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        // find one to the right of x and one to the left of x
        auto right = lower_bound(all(a), x);
        if (right == a.end()) right = a.begin();
        auto left = upper_bound(all(a), x);
        if (left == a.end()) {
            if (*(a.rbegin()) <= x) {
                left = a.end();
                left--;
            } else
                left = a.begin();
        } else if (left == a.begin()) {
            left = a.end();
            left--;
        }
        else {
            left--;
        }
        int r = right-a.begin();
        int l = left-a.begin();
        dbg(x, y);
        dbg(l, r, a[l], a[r]);
        // a[l] to (a[l]+n)%(2*n)
        // a[r]
        int ans = min(dist(a[l], x)+dist((a[l]+n)%(2*n), y), dist(a[r], x)+dist((a[r]+n)%(2*n), y))+1;
        ans = min(ans, dist(x, y));
        cout << ans << "\n";

    }
}
