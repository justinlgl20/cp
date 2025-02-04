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

int dp[105][10005];

int pmin[105][10005];

int32_t main() {
    int n, m, s; cin >> n >> m >> s;
    vector<int> u(n+2, 0), d(n+3, 0);
    for (int i = 1; i <= n; i++) cin >> u[i];
    for (int i = 1; i <= n; i++) cin >> d[i];
    dp[0][0] = 0;
    pmin[0][0] = dp[0][0] + 0*m - 0*d[0+1];
    dbg("HI");
    for (int i = 1; i <= s; i++) {
        dp[0][i] = 1e9;
        pmin[0][i] = min(pmin[0][i-1], dp[0][i]+i*m-i*d[1]); //7045 it breaks
        dbg(i);
    }
    for (int i = 1; i <= n; i++) {
        dbg(i);
        for (int j = 0; j <= s; j++) {
            dp[i][j] = u[i]*d[i]+j*d[i] + pmin[i-1][min(s, j+u[i])];
            pmin[i][j] = dp[i][j]+j*m - j*d[i+1];
            if (j > 0)
                pmin[i][j] = min(pmin[i][j], pmin[i][j-1]);
        }
    }
    cout << dp[n][0] << "\n";
    return 0;
}
