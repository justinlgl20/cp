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

struct dsu {
    vector<int> p;
    dsu(int n) {
        p.resize(n+5);
        for (int i = 0; i < n+4; i++) p[i] = i;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b= rep(b);
        p[a] = b;
    }
};

#define pii pair<int, int>
#define f first
#define s second

int k[200005];
int c[200005];
vector<int> s[200005];

int32_t main() {
    int n, m; cin >> n >> m;
    vector<int> edges;
    for (int i = 0; i < m; i++) {
        cin >> k[i] >> c[i];
        for (int j = 0; j < k[i]; j++) {
            int x; cin >> x;
            s[i].push_back(x);
        }
        edges.push_back(i);
    }
    sort(all(edges), [&](int a, int b) {
        return c[a] < c[b];
    });

    dsu uf = dsu(n);

    int ans = 0;

    for (auto i : edges) {
        set<int> reps;
        for (int j : s[i]) {
            reps.insert(uf.rep(j));
        }
        ans += c[i]*((int)reps.size()-1ll);
        int s = (*reps.begin());
        reps.erase(reps.begin());
        for (int j : reps) uf.merge(j, s);
    }
    int g = uf.rep(1);
    for (int i = 1; i <= n; i++) {
        if (uf.rep(i) != g) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << ans << "\n";

}
