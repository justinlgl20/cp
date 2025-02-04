#include <bits/stdc++.h>
using namespace std;
 
//#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> a) {
    os << "{" << a.first << " " << a.second << "}";
    return os;
}
 
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
 
int nxt() {
    int g; cin >> g; return g;
}
 
struct seg {
    vector<int> t;
    int n;
    seg(int n) {
        this->n = n;
        t.reserve(2*n+4);
        t.resize(2*n+4);
        for (int i = 0; i <= 2*n; i++) t[i] = 0;
    }
    void set(int p, int v) {
        for (p+=n,t[p]=max(t[p], v); p > 1; p >>=1) t[p>>1] = max(t[p], t[p^1]);
    }
    int query(int l, int r) {
        int ans = 0;
        r+=1;
        for (l += n, r+=n; l < r; l>>=1,r>>=1) {
            if (l&1) ans = max(ans, t[l++]);
            if (r&1) ans = max(ans, t[--r]);
        }
        return ans;
    }
};
 
int n, m;
 
vector<int> adj[500005][2];
 
int seen[500005];
vector<pair<int, int>> rangeas[500005];
 
void dfs(int u, vector<int> &ans) {
    seen[u] = 1;
    for (int i : adj[u][0]) {
        if (!seen[i]) dfs(i, ans);
    }
    ans.push_back(u);
}
 
vector<int> topsort() {
    for (int i = 0; i <= n; i++) seen[i] = false;
    vector<int> ans = {};
    for (int i = 1; i <= n; i++) if (!seen[i]) dfs(i, ans);
    reverse(all(ans));
    return ans;
}
 
int dp[500005][2]; // 0 is forward, as starting point
 
 
int pos_in_top[500005];
int longest_up_to[500005][2];
 
int32_t main() {
    n = nxt();
    m = nxt();
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int a = nxt(); int b = nxt();
        dbg(a, b);
        adj[a][0].push_back(b);
        adj[b][1].push_back(a);
        edges.push_back({a, b});
    }
    dbg("HI");
    vector<int> topsorted = topsort();
    dbg(topsorted);
    for (int i = n-1; i >= 0; i--) {
        for (auto u : adj[topsorted[i]][0])
            dp[topsorted[i]][0] = max(dp[topsorted[i]][0], dp[u][0]+1);
    }
    for (int i = 0; i < n; i++) {
        for (auto u : adj[topsorted[i]][1]) 
            dp[topsorted[i]][1] = max(dp[topsorted[i]][1], dp[u][1]+1);
    }
    // 1 re from the 3 loops above
    for (int i = 0; i < n; i++) {
        pos_in_top[topsorted[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        longest_up_to[i][1] = dp[topsorted[i]][1];
        if (i > 0) 
        longest_up_to[i][1] = max(longest_up_to[i-1][1], longest_up_to[i][1]);
    }
    for (int i = n-1; i >= 0; i--) {
        longest_up_to[i][0] = dp[topsorted[i]][0];
        if (i < n-1) 
            longest_up_to[i][0] = max(longest_up_to[i+1][0], longest_up_to[i][0]);
    }
    //cout << best_path.size()-1 << "\n";
    // EVERYTHING UP TO HERE WORKS  :) https://atcoder.jp/contests/dp/tasks/dp_g
    vector<int> arr(n+5, 0);
 
    int u, v, s, e, val;
    for (int i = 0; i < m; i++) { // most re's in this loop
        u = edges[i].first;
        v = edges[i].second;
        s = pos_in_top[u]+1;
        e = pos_in_top[v]-1;
        if (s > e) continue;
        val = dp[u][1]+dp[v][0]+1;
        val = max(val, dp[u][1]);
        /*for (int i = s; i <= e; i++) {
            arr[i] = max(arr[i], val);
        }*/
        dbg(u, v, pos_in_top[u], pos_in_top[v], dp[u][1], dp[v][0]);
        dbg(u, v, s, e, val, i);
        //ranges.push_back({s, e, val, i});
        rangeas[s].push_back(make_pair(e, val));
    }
    seg tree = seg(1ll<<((int)log2(n+5)+1ll));
    int lowest = 1e9;
    int node = 0;
    for (int i = 0; i < n; i++) {
        for (auto j : rangeas[i]) {
            tree.set(j.first, j.second);
        }
        
        arr[i] = tree.query(i, n);
        dbg(i, arr[i]);
 
 
        arr[i] = max(arr[i], longest_up_to[i-1][1]);
        arr[i] = max(arr[i], longest_up_to[i+1][0]);
        if (arr[i] < lowest) {
            lowest = arr[i];
            node = topsorted[i];
        }
    }
    dbg(arr);
    if (lowest == 1e9 or !(1 <= node and node <= n)) node = 1, lowest = 0;
    dbg("HI");
    cout << node << " " << lowest << "\n";
    
}
