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

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+3, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    deque<int> g;
    for (int i = 1; i <= n; i++) g.push_back(i);
    vector<int> value(n+3, 0);
    queue<pii> things;
    vector<int> deg1kids(n+4, 0);
    // 1 GOES TO PLACE WITH MOST DEG1 KIDS
    // 2 GOES TO PLACE WITH SECOND MOST DEG1 KIDS
    for (int i = 1; i <= n; i++) {
        for (auto j : adj[i]) {
            deg1kids[i] += adj[j].size() == 1ll;
        }

    }

    dbg(root, n);

    things.push({root, (n+1)/2});

    while (things.size()) {
        int i = things.front().f;
        int col = things.front().s;
        things.pop();

        if (col) {value[i] = g.back(); g.pop_back();}
        else {value[i] = g.front(); g.pop_front();}
        for (auto j : adj[i]) {
            if (j != p[i]) {
                p[j] = i;
                things.push({j, !col});
            }
        }
    }
    
    for (int i = 1; i <= n; i++) cout << value[i] << " \n"[i==n];
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
