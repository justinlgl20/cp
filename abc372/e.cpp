#include <bits/extc++.h>
using namespace std;
 
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

using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

struct dsu {
    vector<int> p;
    vector<int> sz;
    vector<ordered_set> s;
    dsu(int n) {
        p.resize(n+3);
        sz.resize(n+3);
        s.resize(n+3);
        for (int i = 0; i < n+2; i++) {
            p[i] = i;
            sz[i] = 1;
            s[i].insert(i);
        }
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b = rep(b);
        if (a == b) return;
        if (sz[a] > sz[b]) swap(a, b); // b is bigger

        p[a] = b;
        sz[b] += sz[a];
        for (auto i : s[a]) s[b].insert(i);
    }
};

int32_t main() {
    int n, q; cin >> n >> q;
    dsu x = dsu(n);
    while (q--) {
        int c;
        int a, b;
        cin >> c >> a >> b;
        if (c == 1) {
            x.merge(a, b);
        } else {
            int q = x.s[x.rep(a)].size();
            if (q < b) cout << "-1\n";
            else {
                int ans = *x.s[x.rep(a)].find_by_order(q-b);
                cout << ans << "\n";
            }
        }
    }
}
