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

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> psa(n+4, 0);
    for (int i = 1; i <= n; i++) {
        psa[i] = psa[i-1]+a[i-1];
    }
    function<int(int, int)> sum = [&](int l, int r) {
        return psa[r+1]-psa[l];
    };

    while (q--) {
        int l, r, k; cin >> l >> r >> k;
        r--;l--;
        int g = sum(l, r);
        dbg(l, r, k, g);
        // there must be k 1s
        int ans;
        if (k >= r-l+1) {
            cout << "-1\n";
        } else {
            ans = abs(k-g);
            if (k + 1 == r-l+1) {
                ans = min(ans, abs(k+1-g));
            }
            cout << ans << "\n";
        } 
    }
}
