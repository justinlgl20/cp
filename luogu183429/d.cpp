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
    int n; cin >> n;
    vector<int> a(n+4, 0);
    set<int> qw;
    for (int i = 0; i < n; i++) {cin >> a[i+1];qw.insert(a[i+1]);}
    int m = qw.size();
    vector<int> dp(n+5);
    dp[0] = 0;
    int SQRT = pow(n, 0.5)+2;
    unordered_map<int, int> idk;
    set<int> s; // pos
    for (int i = 1; i <= n; i++) {
        if (idk.find(a[i]) != idk.end()) {
            s.erase(s.find(idk[a[i]]));
        }
        dp[i] = 1+dp[i-1];
        int u = 1;
        s.insert(0);
        for (set<int>::reverse_iterator rit = s.rbegin(); rit != s.rend(); rit++) {
            if (u >= SQRT) {
                break;
            }
            int q = *rit;
            dbg(q, u);
            dp[i] = min(dp[i], dp[q]+u*u);
            u++;
            if (q-1 >= 0) {
                dp[i] = min(dp[i], dp[q-1]+u*u);
            }
        }
        
        idk[a[i]] = i;
        s.insert(i);
        dbg(i, dp[i]);
    }
    dbg(dp);
    cout << dp[n] << "\n";
}
