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
    int n; cin >> n;
    vector<vector<int>> ans(n,vector<int>(n, 0));
    vector<vector<int>> marked(n, vector<int>(n, 0));
    vector<pair<int, int>> a = {{2, 1}, {-2, 1}, {-2, -1}, {2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};
    auto mark = [&](int i, int j) {
        vector<pair<int, int>> ans;
        marked[i][j] = true;
        for (auto w : a) {
            int q = i+w.first;
            int b = j+w.second;
            if (0 <= q and q < n and 0 <= b and b < n) marked[q][b] = 1;
        }
    };
    int ones = 0;
    int i;
    for (i = 2; i < n; i+=5) {
        for (int j = 0; j < n; j++) {ans[i][j] = 1;ones++;mark(i, j);}
    }
    if (n-(i-5) == 4) {
        int j;
        for (j = 1; j < n; j+=3) {ans[n-3][j] = 1;ones++;mark(n-3, j);j+=1; if (j >= n) break; ans[n-3][j] = 1;ones++;mark(n-3, j);}
        if (n-(j-3) == 3) ans[n-3][n-2] = 1; ones++; mark(n-3, n-2);
    } else if (n - (i-5) == 5) {
        for (int j = 0; j < n; j++) {ans[n-1][j] = 1; ones++; mark(n-1, j);}
    }
    if (n == 3) ans[1][1] = 1;
    //assert(ones < (int)((n*n+3*n)/5));
    //dbg(ones, (int)((n*n+3*n)/5));
    bool works = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (n<3?1:ans[i][j]) << " \n"[j==n-1];
            //dbg(i, j, marked[i][j]);
            //assert(marked[i][j]);
        }
    }
}
