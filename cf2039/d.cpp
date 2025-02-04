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

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n+5, 0);
    a[1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 2*i; j <= n; j+=i) {
            a[j] = max(a[j], a[i]+1);
        }
    }
    vector<int> s(m);
    for (int i = 0; i < m; i++) cin >> s[i];
    sort(all(s));
    reverse(all(s));
    vector<int> ans(n+4, 0);
    for (int i = 1; i <= n; i++) {
        if (a[i] > m) {
            cout << "-1\n";
            return;
        }
        ans[i] = s[a[i]-1];
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i==n];
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
