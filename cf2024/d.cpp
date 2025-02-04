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

struct segtree {
    vector<int> t;
    int n;
    segtree(int x) {
        n = 1;
        while (n < x) n *= 2;
        t.resize(3*n+4);
        for (int i = 0; i < 3*n+3; i++) t[i] = -1e18;
    }
    void upd(int p, int v) {
        p+=n;
        for (t[p] = max(t[p], v); p > 1; p>>=1) t[p>>1] = max(t[p], t[p^1]);
    }
    int query(int l, int r) {
        r++;
        int ans = -1e18;
        for (l+=n, r+=n;l<r;l>>=1,r>>=1) {
            if (l&1) ans = max(ans, t[l++]);
            if (r&1) ans = max(ans, t[--r]);
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n+3, 0);
    vector<int> b(n+3, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    vector<int> psa(n+3, 0);
    for (int i = 1; i <= n; i++) {
        psa[i] = psa[i-1]+a[i];
    }
    int ans = 0;
    int l = 1, r = 1;
    vector<int> value(n+3, -1e18); // how much we can start with
    function<int(int, int)> sum = [&](int l, int r) {
        return psa[r]-psa[l-1];
    };
    segtree val = segtree(n);
    vector<vector<int>> from(n+4, vector<int>());
    for (int i = 1; i <= n; i++) {
        from[b[i]].push_back(i);
    }

    val.upd(1, 0);

    int fans = 0;
    for (int i = 1; i <= n; i++) {
        int ans = val.query(i, i);
        for (auto j : from[i]) {
            int an = val.query(j, i-1) - a[j];
            ans = max(ans, an);
        }
        dbg(i, ans);
        fans = max(fans, sum(1, i)+ans);
        val.upd(i, ans);
    }
    cout << fans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
