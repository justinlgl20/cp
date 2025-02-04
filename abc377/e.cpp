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

vector<int> adj[200005];
int to[200005];

struct dsu {
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
        if (a != b) p[a] = b;
    }
};

int n, k;

int hop[200005][30];

int32_t main() {
    cin >> n >> k;
    vector<int> p(n);
    dsu uf = dsu(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        to[i+1] = p[i];
        adj[i+1].push_back(p[i]);
        adj[p[i]].push_back(i+1);
        uf.merge(i+1, p[i]);
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> roots;
    for (int i = 1; i <= n; i++) {
        if (uf.p[i] == i) roots.push_back(i);
    }
    vector<bool> seen(n+3, 0);
    function<void(int, int)> process = [&](int u, int i) {
        hop[u][i] = hop[hop[u][i-1]][i-1];
    };
    for (int i = 1; i <= n; i++) {
        hop[i][0] = to[i];
    }
    for (int j = 1; j <= 29; j++) {
        for (int i = 1; i <= n; i++) {
                process(i, j);
        }
    }

    function<int(int, int)> jump = [&](int u, int k) {
        for (int i = 29; i >= 0; i--) {
            if (k&(1ll<<i)) {
                u = hop[u][i];
            }
        }
        return u;
    };

    vector<int> ans(n+3, 0);

    for (int i = 1; i <= n; i++) {
        // make i jump k away
        ans[jump(i, k)] = a[i-1];
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i==n];
    }
        }

}
