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
    vector<pii> r;
    vector<vector<int>> ends(n+3, vector<int>());
    vector<vector<int>> starts(n+3, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        r.emplace_back(a, b);
        ends[b+1].push_back(a);
        starts[a].push_back(b+1);
    }
    multiset<int> ins;
    multiset<int> ine;
    vector<int> dp(n+4, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j : starts[i]) {
            dbg("INSERT", i, j);
            ine.insert(j);
            ins.insert(i);
        }
        for (int j : ends[i]) {
            dbg("REMOVE", j, i);
            ine.erase(ine.find(i));
            ins.erase(ins.find(j));
        }
        if (ine.size()) {
            int x = *(ine.rbegin());
            int s = *(ins.begin());
            dp[i] = max(dp[i], dp[s-1] + (int)ine.size());
            dbg(x, s, "UPDATE", dp[x], ine.size());
        }
        dp[i] = max(dp[i], dp[i-1]);
        ans = max(ans, dp[i]);
    }
    cout << ans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
