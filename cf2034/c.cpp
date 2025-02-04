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

struct dsu {
    vector<int> p;
    vector<int> sz;
    vector<vector<int>> s;
    dsu(int n) {
        p.resize(n+3);
        sz.resize(n+3);
        s.resize(n+3);
        for (int i = 0; i < n+2; i++) {p[i] = i, sz[i] = 1;s[i].clear();s[i].push_back(i);}
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b = rep(b);
        if (a == b) return;
        
        if (s[a].size() > s[b].size()) swap(a, b);
        for (auto i : s[a]) s[b].push_back(i);
        p[a] = b;
        sz[b] += sz[a];
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<pii> unmap((n+1)*(m+1)+40);
    function<int(int, int)> id = [&](int i, int j) {
        if (i < 1 or i > n or j < 1 or j > m) return 0ll;
        unmap[i*m+j] = make_pair(i, j);
        return (int)(i*m+j);
    };

    dsu uf = dsu((n+1)*(m+1)+50);
    vector<vector<char>> gri(n+2, vector<char>(m+2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> gri[i][j];
            dbg(i, j, gri[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j= 1; j <= m; j++) {
            if (gri[i][j] == 'U') {
                uf.merge(id(i, j), id(i-1, j));
            } else if (gri[i][j] == 'D') {
                uf.merge(id(i, j), id(i+1, j));
            } else if (gri[i][j] == 'L') {
                uf.merge(id(i, j), id(i, j-1));
            } else if (gri[i][j] == 'R') {
                uf.merge(id(i, j), id(i, j+1));
            } 
        }
    }

    int ans = n*m - (uf.sz[uf.rep(0)]-1ll);
    dbg(ans);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int k = id(i, j);
            if (gri[i][j] == '?' and uf.sz[uf.rep(k)] == 1) {
                dbg(i, j);
                set<int> ne;
                ne.insert(uf.rep(id(i-1, j)));
                ne.insert(uf.rep(id(i+1, j)));
                ne.insert(uf.rep(id(i, j-1)));
                ne.insert(uf.rep(id(i, j+1)));
                if (ne.size() == 1 and (*ne.rbegin()) == uf.rep(0)) ans -= uf.sz[k];
            }

        }
    }
    cout << ans << "\n";

}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
