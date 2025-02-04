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
    int n, t, k, v, g; cin >> n >> t >> k >> v >> g;
    vector<double> b(t+3);
    for (int i = 1; i <= t; i++) {cin >> b[i]; b[i]/=(double)100;}
    vector<double> dp(n+4);
    dp[1] = k + k*b[v];
    vector<vector<double>> d(t+3, vector<double>(t+3, 0));
    vector<double> sumd(t+3, 0);
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= t; j++) {
            cin >> d[i][j];
            d[i][j]/=(double)100;
            sumd[j] += d[i][j];
        }
    }
    dbg(dp[1]);
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= t; j++) {
            dp[i] += (((double)1)+b[j])*sumd[j];
        }
        dp[i] *= dp[i-1];
        dp[i]/=(double)t;
        dp[i]/=(double)t;
    }
    cout << "decimal " << dp[n] << "\n";

}
