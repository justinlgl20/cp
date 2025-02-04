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

int32_t main() {
    int n, k; cin >>n >>k;
    vector<vector<int>> ans(n, vector<int>(n, 0));
    // k*k grid at bottom right
    int cur = n*n;
    for (int i = n-1; i >= n-k; i--) {
        ans[i][i] = cur--;
    }
    for (int i = n-1; i >= n-k; i--) {
        for (int j = n-1; j >= n-k; j--) {
            if (i != j) ans[i][j] = cur--;
        }
    }
    cur = 1;
    for (int i = 0; i < n-k; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = cur++;
        }
    }
    for (int i = n-k; i < n; i++) {
        for (int j = 0; j < n-k; j++) {
            ans[i][j] = cur++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << ans[i][j] << " \n"[j==n-1];
    }
}
