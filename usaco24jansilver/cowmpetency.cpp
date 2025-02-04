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

int nxt() {
    int g; cin >> g; return g;
}

struct segtree {
    vector<int> t;
    int n;
    segtree(int n) {
        this->n = n;
        t.resize(4*n+3);
        for (int i = 0; i <= 4*n+1; i++) {
            t[i] = 1e18;
        }
        build();
    }

    void build() {
      for (int i = n-1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    int query(int p) {
        int ans = 0;
        for (p += n; p > 1; p >>= 1) ans += t[p];
        return ans;
    }

    void upd(int l, int r, int x) {
        r += 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) {t[l] = min(t[l], x); l++;}
            if (r&1) {r--; t[r] = min(t[r], x);}
        }
    }
};

int32_t main() {
    int n, q, c; cin >> n >> q >> c;
    vector<int> score(c);
    generate(all(score), nxt);
    segtree upper = segtree(n+5);
    vector<int> lower(n+5);
    vector<pii> things;
    for (int i = 1; i <= q; i++) {
        int a, h; cin >> a >> h;
        if (score[h-1] != 0)
            upper.upd(0, a-1, score[h-1]-1);
        else {
            things.emplace_back(a, h);
        }
    }

}
