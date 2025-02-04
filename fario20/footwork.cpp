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

struct seg {
    vector<int> t;
    int n;
    seg(int n) {
        this->n = n;
        t.resize(3*n+5);
        for (int i = 0; i < t.size(); i++) t[i] = -1e9;
    }
    seg() {}
    void  chmax(int p, int v) {
        for (t[p + n] = max(t[p+n], v),p+=n; p > 1; p>>=1) t[p>>1] = max(t[p], t[p^1]);
    }
    void set(int p, int v) {
        for (t[p+=n] = v; p>1; p>>=1) t[p>>1] = max(t[p], t[p^1]);
    }
    int query(int l, int r) {
        r += 1;
        int res = -1e9;
        for (l += n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) res = max(res, t[l++]);
            if (r&1) res = max(res, t[--r]);
        }
        return res;
    }
};

seg dp[2];

int32_t main() {
    int n, k; cin >> n >> k;
    vector<vector<int>> a(2, vector<int>(n));
    generate(all(a[0]), nxt);
    generate(all(a[1]), nxt);
    dp[0] = seg(n+5);
    dp[1] = seg(n+5);\
    dp[0].set(0, a[0][0]);
    dp[1].set(0, a[1][0]);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= 1; j++) {
            int w = dp[0].query(max(i-k, 0ll), i);
            int q = dp[1].query(max(i-k, 0ll), i);//just need to lazy prop segtree so can set other foot elements to add my score
            dp[j].chmax(i, max(w, q)+a[j][i]);
            dbg(i, j, dp[j].query(i, i));
        }
    }
    cout << dp[1].query(n-1, n-1);
}
