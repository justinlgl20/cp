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

int a[105], b[105];

int x[4];

unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
int get(int i, int j, int k) {
    if (i < 0 or j < 0 or k < 0) return 1e18;
    if (dp.find(i) != dp.end()) {
        if (dp[i].find(j) != dp[i].end()) {
            if (dp[i][j].find(k) != dp[i][j].end()) {
                return dp[i][j][k];
            }
        }
    }
    return 1e18;
}

int32_t main() {
    int n; cin >> n;
    int s = 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        s += b[i];
        x[a[i]] += b[i];
    }
    if (s % 3 != 0) {
        cout << "-1\n";
        return;
    }
    dp[x[1]][x[2]][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int s1 = 0; s1 <= s; s1++) {
            
        }
    }

}
