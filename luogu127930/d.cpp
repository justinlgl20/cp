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

int dp[3005][3005]; // cost, index
pii from[3005][3005];

int32_t main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<int> dp2(n+4);
    dp2[0] = 1;
    vector<int> cells = {0};
    for (int i = 1; i < n; i++) {
        dp2[i] = max(dp2[i-1], dp2[i-1]);
        if (b[i] == 0) {
            dp2[i]++;
        }
    }

    // dp[i] is how many cells u can get up to and including i
    int best = 0;
    pii loc = {0, 0};
    multiset<pair<pii, int>> g;
    for (int i = n-1; i >= 0; i--) {
        int val = a[i];
        int cost = b[i];
        g.insert(make_pair(make_pair(val, cost), i));
        for (int j = 0; j <= 3002; j++) {
            dp[j][i] = dp[j][i+1];
            from[j][i] = {j, i+1};
            if (j > 0) {
                if (dp[j-1][i] > dp[j][i]) {
                    dp[j][i] = dp[j-1][i];
                    from[j][i] = from[j-1][i];
                }
            }
            if (j >= cost) {
                if (dp[j-cost][i+1]+val > dp[j][i]) {
                    dp[j][i] = dp[j-cost][i+1]+val;
                    from[j][i] = {j-cost, i+1};
                }
            }
        }
        if (i > 0) {
            if (dp[dp2[i-1]][i] > best) {
                best = dp[dp2[i-1]][i];
                loc = {dp2[i-1], i};
            }
        } else {
            if (dp[0][i] > best) {
                best = dp[0][i];
                loc = {0ll, i};
            }
        }
    }
    // loc.s
    vector<int> things = {0};
    for (int i = 1; i < loc.s; i++) {
        if (b[i] == 0) {
            things.push_back(i);
        }
    }

    cout << best << "\n";
}
