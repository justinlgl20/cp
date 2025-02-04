#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
ostream& operator<<(ostream& os, pair<int, int> x) {
    os << "(" << x.first << " " << x.second << ")";
    return os;
}
 
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
 
int dp[200005];
const int MOD = 1000000007;
 
int solve(vector<pii> ranges) {
    int ans = 0;
    unordered_set<int> ends;
    for (auto i : ranges) {
        if (ends.size() and (*ends.begin()) < i.f) {
            ends.clear();
            ans++;
        }
        ends.insert(i.s);
    }
    if (ends.size()) ans++;
    return ans;
}
 
int32_t main() {
    int n; cin >> n;
    vector<pii> ranges(n);
    for (int i = 0; i < n; i++) cin >> ranges[i].f >> ranges[i].s;
    sort(all(ranges), [&](auto i, auto j) {
        return i.s < j.s;
    });
    vector<int> powers(n+4, 0);
    powers[0] = 1;
    for (int i = 1; i <= n; i++) {
        powers[i] = 2*powers[i-1];
        powers[i] %= MOD;
    }
    for (int i = n-1; i >= 0; i--) {
        int k = 0;
        int s = ranges[i].f, e = ranges[i].s;
        int cursum = 0;
        
        for (int j = i+1; j < n; j++) {
            if (ranges[j].f <= e) {
                k++;
            } else {
                cursum += dp[j]*powers[k];
                cursum %= MOD;
            }
        }
        dp[i] = cursum + powers[n-1-i];
        dp[i] %= MOD;
 
        // n-i
        dbg(s, e, dp[i], cursum);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) ans += dp[i];
    ans %= MOD;
    cout << ans << "\n";
}
