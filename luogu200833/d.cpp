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

int factorial[500005];

const int MOD = 20051131;

int32_t main() {
    int n; cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    vector<int> sz(n+3);
    for (int i = 0; i < n; i++) {
        sz[t[i]] += 1;
    }
    factorial[1] = 1;
    factorial[0] = 1;
    for (int i = 2; i <= n+3; i++) {
        factorial[i] = factorial[i-1]*i;
        factorial[i] %= MOD;
    }
    vector<int> chains;
    for (int i = 1; i <= n; i++) {
        if (sz[i]) chains.push_back(sz[i]);
    }
    sort(all(chains));
    reverse(all(chains));
    dbg(chains);
    int cnt;
    int ans = 1;

    int s = chains[0];

    for (int i = 1; i < chains.size(); i++) {
        ans *= s-(i)*(chains[i]);
        s += chains[i];
    }
    dbg(ans);
    
    for (int i : chains) {
        dbg(i, factorial[i-1]);
        ans *= factorial[i-1];
        ans %= MOD;
    }
    cout << ans << "\n";


}
