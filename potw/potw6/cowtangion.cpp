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

int nxt() {
    int g; cin >> g; return g;
}

vector<int> adj[100005];

int dfs(int u, int p) {
    int cnt = 0;
    int re = 0;
    int needed = (p == 0);
    needed += adj[u].size();
    int cur = 1;
    while (cur < needed) {
        re++;
        cur *= 2;
    }
    for (auto i : adj[u]) {
        if (i != p) {
            re += dfs(i, u)+1;
        }
    }
    return re;
}

int32_t main() {
    int n = nxt();
    for (int i = 0; i < n-1; i++) {
        int a=nxt(),b=nxt();
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << dfs(1, 0) << "\n";
}
