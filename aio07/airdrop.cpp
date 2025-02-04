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

unordered_map<int, int> dp[1005];

int32_t main() {
#ifndef DEBUG
    freopen("dropin.txt", "r", stdin);
    freopen("dropout.txt", "w", stdout);
#endif
    int n = nxt();
    vector<int> pos(n);
    generate(all(pos), nxt);
    vector<vector<int>> dists(n, vector<int>());
    for (int i = n-1; i >= 0; i--) {
        // dp[i][j] is best if jump is j
        for (int j = i+1; j < n; j++) {
            if (dp[j].find(abs(pos[j]-pos[i])) != dp[j].end())
                dp[i][abs(pos[j]-pos[i])] = dp[j][abs(pos[j]-pos[i])]+1;
            else {
                dp[i][abs(pos[j]-pos[i])] = 2;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (auto j : dp[i]) {
            ans = max(ans, j.second);
            dbg(i, j.first, dp[i][j.first]);
        }
    }
    cout << max(ans, 1ll) << "\n";
}
