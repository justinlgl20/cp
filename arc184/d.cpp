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
    int n; cin >> n;
    vector<pii> balls;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        balls.emplace_back(a, b);
    }
    sort(all(balls));
    vector<int> dp(n+2, 0);
    vector<int> can_remove(n+2, 1);
    for (int i = 0; i < n; i++) {
        int x = balls[i].f, y = balls[i].s;
        bool q = 0;
        bool v= 0;
        for (int j = 0; j < i; j++) {
            if (balls[j].s > balls[i].s)
            {
                q = 1;
                dp[i] += dp[j];} else {
                    v = 1;
                }
        }
        for (int j = 0; j < i; j++) {
            if (v) dp[i]+=dp[j];
        }
        if (!q) dp[i] = 1;

        // THIS ACCOUNTS FOR USING POWER
        // IF NOT USING POWER CAN TAKE AMOUNT FROM TL
        dbg(x, y, dp[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i];
    }
    cout << dp[n-1] << "\n";
}
