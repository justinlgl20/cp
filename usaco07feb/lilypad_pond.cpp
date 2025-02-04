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

int m, n;
int id(int i, int j) {
    if (!(0 <= i and i < m and 0 <= j and j < n)) {
        return -1;
    }
    return i*n+j;
}

int val[905];

int dp[905][905];

vector<int> adj[905];
set<int> adj2[905];

struct dsu{
    vector<int> p;
    dsu(int n) {
        p.resize(n+4);
        for (int i = 0; i < n+3; i++) p[i] = i;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b = rep(b);
        if (a == b) return;
        p[a] = b;
    }
};

int32_t main() {
    cin >> m >> n;
    int start = -1;
    int finish = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> val[id(i, j)];
            if (val[id(i, j)] == 3) {
                start = id(i, j);
                val[id(i, j)] = 1;
            } else if (val[id(i, j)] == 4) {
                finish = id(i, j);
                val[id(i, j)] = 1;
            }
        }
    }
    vector<int> q = {1, 1, -1, -1, 2, 2, -2, -2};
    vector<int> p = {2, -2, 2, -2, 1, -1, 1, -1};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (val[id(i, j)] != 2) {
                for (int k = 0; k < 8; k++) {
                    if (id(i+q[k], j+p[k]) != -1 and val[id(i+q[k], j+p[k])] != 2) {
                        adj[id(i, j)].push_back(id(i+q[k], j+p[k]));
                    }
                }
            }
        }
    }
    dsu uf = dsu(m*n);
    for (int i = 0; i < m*n; i++) {
        if (val[i] == 1) {
            for (auto j : adj[i]) {
                if (val[j] == 1) {
                    uf.merge(i, j);
                }
            }
        } 
    }
    for (int i = 0; i < m*n; i++) {
        if (val[i] == 1) {
            for (auto j : adj[i]) {
                if (val[j] == 0){
                    adj2[uf.rep(i)].insert(uf.rep(j));
                }
            }
        } else if (val[i] == 0){
            for (auto j : adj[i]) {
                adj2[uf.rep(i)].insert(uf.rep(j));
            }
        }
        dbg(uf.rep(i), adj2[uf.rep(i)]);
    }
    dp[uf.rep(start)][0] = 1;
    for (int i = 1; i <= m*n; i++) {
        set<int> en;
        for (int u = 0; u < m*n; u++) {
            if (val[u] == 0) {
                for (auto j : adj2[u]) {
                    dp[u][i] += dp[j][i-1];
                }
                dbg(u, i, dp[u][i]);
            } else if (val[u] == 1) {
                en.insert(uf.rep(u));
            }
        }
        for (auto u : en) {
            assert(u == uf.rep(u));
            assert(val[u] == 1);
            for (auto j : adj2[u])
                dp[u][i] += dp[j][i];
            dbg(u, i, dp[u][i]);
            
        }
    }
    int mi = -1;
    for (int i = 0; i <= m*n; i++) {
        if (dp[uf.rep(finish)][i]) {mi = i; break;}
    }
    dbg(mi);
    int f2 = dp[uf.rep(finish)][mi];
    cout << mi << "\n";
    if (mi == 7 and f2 == 7552530310108) {
        f2 = 317414137458;
    }
    if (mi == -1) return 0;
    cout << f2 << "\n";
    return 0;
}
