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

vector<int> numbers;
int sieve[500005];

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n+3, vector<int>());
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dbg(adj);
    int cnt = 2;
    vector<int> val(n+3, 0);
    function<void(int, int)> dfs = [&](int u, int p) {
        val[u] = 1;
        for (auto j : adj[u]) {
            if (j != p) {
                dfs(j, u);
                val[u] += val[j];
            }
        }
    };
    dfs(1, -1);
    function<int(int, int)> centroid = [&](int u, int p) {
        for (int i : adj[u]) {
            if (i == p) continue;
            if (val[i] * 2 > n) return centroid(i, u);
        }
        return u;
    };
    int root = centroid(1, -1);
    dbg(root);
    val.assign(n+3, 0);
    cnt = 2;
    dbg(adj);
    function<void(int, int)> dfs2 = [&](int u, int p) {
        dbg(u);
        for (int i : adj[u]) {
            if (i == p) continue;
            while (sieve[abs(cnt-val[u])] == 0) cnt++;
            val[i] = cnt;   cnt++;
            dfs2(i, u);
        }
    };
    val[root] = 1;
    dfs2(root, -1);

    for (int i = 1; i <= n; i++) cout << val[i] << " \n"[i==n];

}

int32_t main() {
    vector<int> primes;
    numbers.push_back(1);
    sieve[1] = 1;
    for (int i = 2; i < 500004; i++) {
        if (!sieve[i]) primes.push_back(i);
        else {
            numbers.push_back(i);
        }
        for (int j = 0; j < primes.size() and i * primes[j] < 500004; j++) {
            sieve[i*primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    int t; cin >> t;
    while (t--) solve();
}
