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

vector<int> adj[100005];
int depth[100005];
int p[100005];
int deepest[100005];

void dfs(int u, int p) {
    ::p[u] = p;
    for (int i : adj[u]) {
        if (i != p) {
            depth[i] = depth[u]+1;
            deepest[i] = max(deepest[i], depth[i]);
            dfs(i, u);
            deepest[u] = max(deepest[u], deepest[i]);
        }
    }
}
int ans[100005];
int val[100005];

int32_t main() {
    int n, root; cin >> n >> root;
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    depth[root] = 0;
    dfs(root, -1);

    for (int i = 1; i <= n; i++) {
        val[i] = -depth[i];
        for (int j : adj[i]) {
            if (j != p[i]) {
                val[i] += deepest[j];
            }
        }
    }

    int q; cin >> q;


}
