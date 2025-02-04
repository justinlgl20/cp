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

bool works(vector<vector<int>>& u, vector<vector<int>> &v) {
    int a=0,b=0, c=0;
    for (int i = 0; i < u.size(); i++) {
        for (int j = 0; j < u[0].size(); j++) {
            if (u[i][j]) a++;
            if (v[i][j]) b++;
            if (u[i][j] and v[i][j]) c++;
        }
    }
    if (c >= (int)(min(a, b)/2) + (min(a, b)%2)) {
        return true;
    }
    return false;
}

void dfs(int u, vector<int>& seen, vector<int>&order, vector<vector<int>>&adj) {
    seen[u] = 1;
    for (int i : adj[u]) {
        if (!seen[i]) dfs(i, seen, order, adj);
    }
    order.push_back(u);
}

int32_t main() {
    int n, h, w; cin >> n >> h >> w;
    vector<vector<vector<int>>> things;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> t(h, vector<int>(w, 0));
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) cin >> t[j][k];
        }
        things.push_back(t);
    }
    vector<vector<int>> adj(n+3, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (works(things[i], things[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    vector<vector<int>> components;
    vector<int> order;
    vector<int> visited(n+3, 0);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs(i, visited, order, adj);
    }
    vector<vector<int>> radj(n);
    for (int v = 0; v < n; v++) {
        for (int u : adj[v]) {
            radj[u].push_back(v);
        }
    }

    visited.assign(n, false);
    reverse(all(order));
    vector<int> roots(n, 0);
    int ans = 0;
    for (auto v : order) {
        if (!visited[v]) {
            vector<int> comp;
            dfs(v, visited, comp, radj);
            dbg(comp);
            ans = max(ans, (int)comp.size());
            components.push_back(comp);
        }
    }
    if (components.size() > 2) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }

}
