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
    dsu(int n) {
        p.resize(n+4);
        sz.resize(n+3);
        for (int i = 0; i < n+2; i++) p[i] = i, sz[i]=1;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b = rep(b);
        p[a] = b;
        sz[b] += sz[a];
    }
};

vector<pii> g = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
unordered_map<char, int> idk;

int32_t main() {
    idk['U'] = 2;
    idk['D'] = 0;
    idk['L'] = 3;
    idk['R'] = 1;

    int n, qw; cin >> n >> qw;
    vector<vector<int>> adj((n+1)*(n+1)+40, vector<int>());
    vector<int> spec((n+1)*(n+1)+30, 0);
    function<int(int, int)> id = [&](int i, int j) {
        return (i-1)*n+(j-1);
    };
    // 0 IS OUTSIDE
    function<int(int, int)> apply = [&](int u, int dir) {
        int i = (u/n+1)+g[dir].f, j = ((u%n)+1)+g[dir].s;
        if (i < 1 or i > n or j < 1 or j > n) return n*n;
        int qwe = (id(i, j));
        return qwe;
    };

    vector<int> pos;
    vector<int> dir(qw+3);
    vector<vector<int>> gw(n+1, vector<int>(n+1, 0));
    for (int i = 0; i < qw; i++) {
        int r, c; char t; cin >> r >> c >> t;
        int x = id(r, c);
        pos.emplace_back(id(r, c));
        gw[r][c] = 1;
        spec[id(r, c)] = 1;
        dir[i+1] = idk[t];
        adj[apply(x, idk[t])].push_back(x);
        dbg(apply(x, idk[t]), x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x = id(i, j);
            if (gw[i][j] == 0) {
                for (int i = 0; i < 4; i++) {
                    //if (apply(x, i) == n*n or spec[apply(x, i)]==0)
                        adj[apply(x, i)].push_back(x);
                }
            }
            dbg(x, adj[x]);
        }
    }
    // bfs from 0
    queue<int> q;
    vector<int> seen((n+1)*(n+1)+30, 0);
    q.push(n*n);
    seen[n*n] = 1;
    int cur = 0;
    while (q.size()) {
        int u = q.front();
        dbg(u);
        q.pop();
        for (auto i : adj[u]) {
            if (!seen[i]) {
                seen[i] = 1;
                cur++;
                q.push(i);
            }
        }
    }
    vector<int> ans(qw+3);
    ans[qw] = cur;
    dbg(ans[qw]);
    for (int i = qw-1; i >= 1; i--) {
        int x = pos[i];
        bool idk2 = 0;
        for (int j = 0; j < 4; j++) {
            //if (apply(x, j) == n*n or spec[apply(x, j)]==0) {
                adj[apply(x, j)].push_back(x); // now other things can come in
                idk2 = idk2 or seen[apply(x, j)];
            //}
        }
        spec[x] = 0;
        if (idk2 and !seen[x]) {
            seen[x] = 1;
            cur++;
            q.push(x);
        }
        while (q.size()) {
            int u = q.front();
            dbg(u);
            q.pop();
            for (auto qwer : adj[u]) {
                if (!seen[qwer]) {
                    seen[qwer] = 1;
                    cur++;
                    q.push(qwer);
                }
            }
        }
        ans[i] = cur;
        dbg(i, ans[i]);
    }
    for (int i = 1; i <= qw; i++) {
        cout << n*n-ans[i] << "\n";
    }
}
