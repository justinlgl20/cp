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

struct line {
    int m, c;
};

vector<pii> adj[100005];
int n;
int s[100005];
int v[100005];
int ans[100005];
int dist[100005];

// persistent li chao 

line st[200005];

double intersect(line i, line j) {
    return (double)(i.c-j.c)/(j.m-i.m);
}
int sz = 0; // exclusive
int query(int x) {
    int li = 0;
    for (int i = 20; i >= 0; i--) {
        if (li + (1<<i) < sz and intersect(st[li+ (1<<i)], st[li+(1<<i)-1]) <= x) {
            li += 1<<i;
        }
    }
    return st[li].m * x + st[li].c;
}
int insert_index(line u) {
    if (sz == 1) return 1;
    int li = sz-1;
    if (intersect(st[li], st[li-1]) <= intersect(u, st[li-1])) return sz;
    for (int i = 20; i >= 0; i--) {
        if (li - (1<<i) > 0 and intersect(st[li-(1<<i)], st[li - (1<<i)-1]) >= intersect(u, st[li - (1<<i)-1])) {
            li -= 1<<i;
        }
    }
    return li;
}

int cnt = 0;

void dfs(int u, int p) {
    dist[u] = cnt;
    int t;
    if (u != 1) {
        ans[u] = s[u]+v[u]*cnt + query(v[u]);
        t = insert_index(line{-cnt, ans[u]});
    } else {
        ans[u] = 0;
        t = 0;
    }
    dbg(u, ans[u]);
    dbg(t, -cnt, ans[u]);
    for (int i = 0; i < sz; i++) {
        dbg(i, st[i].m, st[i].c);
    }
    line old = st[t];
    int old_sz = sz;
    sz = t+1;
    st[t] = line{-cnt, ans[u]};
    for (auto i : adj[u]) {
        if (i.f != p) {
            cnt += i.s;
            dfs(i.f, u);
            cnt -= i.s;
        }
    }
    sz = old_sz;
    st[t] = old;
}

int32_t main() {
    freopen("harbingers.in", "r", stdin);
    freopen("harbingers.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    for (int i = 2; i <= n; i++) {
        cin >> s[i] >> v[i];
    }
    dfs(1, -1);
    for (int i = 2; i <= n; i++) {
        cout << ans[i] << " \n"[i==n];
    }
}
