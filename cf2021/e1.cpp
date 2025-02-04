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

int n, m, po;
vector<int> s;

vector<pii> adj[5005];
int special[5005];
vector<pair<int, pii>> edges;
vector<pair<int, pii>> tedges;

void massert(bool t) {
    if (!t) while (1) 0;
}

vector<int> merge(vector<int> a, vector<int> b) {
    massert(a.size() == n+1);
    massert(b.size() == n+1);
    vector<int> ans(n+1, 1e18);
    int i = 0, j = 0;
    for (int k = 0; k <= n; k++) {
        ans[k] = a[i]+b[j];
        if (i < n and j < n and a[i+1]+b[j] < a[i]+b[j+1]) {
            i++;
        } else if (i < n and j < n) {
            j++;
        }
    }
    dbg(a, b, ans);
    return ans;
}

vector<int> p;
vector<int> sz;
vector<vector<int>> vals;
struct dsu { // IF WE JUST DO SMALL LARGE ON DIFFERENCE ARRAY OF VALUES IT JUST WORKS AND AC IN N LOG^2 N BUT CBB IMPL
    dsu(int n) {
        p.resize(n+5);
        sz.resize(n+5);
        vals.resize(n+5);
        for (int i = 0; i < n+2; i++) {
            p[i] = i, sz[i] = special[i];
            vals[i].resize(n+1);
            for (int j = 0; j < n+1; j++) vals[i][j] = 0;
            vals[i][0] = special[i]?1e18:0ll;
        }
    }
    int rep(int u) {
        if(p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b, int w) {
        a = rep(a), b = rep(b);
        vals[a][0] = sz[a]*w;
        vals[b][0] = sz[b]*w;
        vals[b] = ::merge(vals[a], vals[b]);
        p[a] = b;
        sz[b] += sz[a];
    }
};


vector<int> kruskals() {
    sort(all(edges));
    dbg("JO");
    dsu x = dsu(n);
    int main = 1;
    for (auto i : edges) {
        if (x.rep(i.s.f) != x.rep(i.s.s)) {
            x.merge(i.s.f, i.s.s, i.f);
            dbg(i.s.f, i.s.s, i.f, vals[x.rep(i.s.s)]);
            main = x.rep(i.s.s);
            adj[i.s.f].emplace_back(i.s.s, i.f);
            adj[i.s.s].emplace_back(i.s.f, i.f);
        }
    }
    return vals[main];

}

void solve() {
    cin >> n >> m >> po;
    s.clear();
    tedges.clear();
    for (int i = 0; i <= n; i++) adj[i].clear();
    for (int i = 0; i <= n; i++) {
        special[i] = 0;
    }
    edges.clear();
    for (int i = 0; i < po; i++) {
        int f; cin >> f;
        s.push_back(f);
        special[f] = 1;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges.emplace_back(w, make_pair(u, v));
    }
    vector<int> g = kruskals();
    for (int i = 1; i < g.size(); i++) cout << g[i] << " ";
    cout << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
