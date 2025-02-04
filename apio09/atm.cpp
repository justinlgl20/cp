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

vector<int> visited;

void dfs(int u, vector<vector<int>> const& adj, vector<int>& out) {
    visited[u] = 1;
    for (auto j : adj[u]) {
        if (!visited[j]) dfs(j, adj, out);
    }
    out.push_back(u);
}

int32_t main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n+3, vector<int>());
    vector<vector<int>> radj(n+3, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    visited.resize(n+3);
    for (int i = 0; i <= n; i++) visited[i] = 0;

    vector<int> a(n+3);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int s, p; cin >> s >> p;
    vector<int> hpub(n+3, 0);
    for (int i = 0; i < p; i++) {
        int x; cin >> x;
        hpub[x] = 1;
    }

    vector<int> root(n+2, 0);
    vector<int> order;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, adj, order);
        }
    }
    reverse(all(order));
    for (int i = 1; i <= n; i++) visited[i] = 0;
    int cnt = 1;
    vector<vector<int>> cadj(n+3, vector<int>());
    vector<vector<int>> components(n+3, vector<int>());
    vector<int> val(n+3, 0);
    vector<int> has_pub(n+3, 0);
    for (auto i : order) {
        if (!visited[i]) {
            vector<int> comp;
            dfs(i, radj, comp);
            int id = cnt++;
            for (auto j : comp) {root[j] = id; val[id] += a[j]; has_pub[id] = has_pub[id] or hpub[j];}
            components[id] = comp;
            dbg(comp, id, val[id], has_pub[id]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (auto j : adj[i]) {
            if (root[i] != root[j]) cadj[root[i]].push_back(root[j]);
        }
    }
    order = {};
    for (int i = 1; i <= n; i++) visited[i] = 0;

    vector<int> ans(cnt+3, -1);

    function<void(int)> dfs = [&](int i) {
        visited[i] = 1;
        for (auto j : cadj[i]) if (!visited[j]) dfs(j);
        if (has_pub[i]) {
            ans[i] = 0;
        }
        for (auto j : cadj[i]) ans[i] = max(ans[i], ans[j]);
        if (ans[i] != -1) {
            ans[i] += val[i];
        }
    };
    dfs(root[s]);
    cout << ans[root[s]] << "\n";



}
