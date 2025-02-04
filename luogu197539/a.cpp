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

struct node {
    int val;
    int l; int r; // l is 0 r is 1
    node () {
        val = 0, l = 0, r = 0;
    }
};

node trie[3000005];
int cnt = 1;

void build(int n) {
    if (trie[n].l == 0) {
        trie[n].l = cnt;
        cnt++;
    }
    if (trie[n].r == 0) {
        trie[n].r = cnt;
        cnt++;
    }
}

void add(int a, int b, int inx, int n=0) {
    if (inx == 0) return;
    build(n);
    if (b&(1ll<<inx)) {
        // if a&(1ll<<inx), the inx'th position in k can be 1 then anything after is fine
        // the inx'th position in k can be 0 then pass on
        if (a&(1ll<<inx)) {
            trie[trie[n].r].val += 1;
            add(a, b, inx-1, trie[n].l);
        }
        // if !(a&(1ll<<inx)), the inx'th position in k can be 0 then anything after is fine
        // the inx'th position in k can be 1 then pass on
        if (!(a&(1ll<<inx))) {
            trie[trie[n].l].val += 1;
            add(a, b, inx-1, trie[n].r);
        }
    }
    else {
        // b[inx] is 0
        // a[inx] xor k[inx] must be 0
        if (a&(1ll<<inx)) {
            add(a, b, inx-1, trie[n].r);
        } else {
            add(a, b, inx-1, trie[n].l);
        }
    }
}

int query(int x, int inx, int n = 0) {
    build(n);
    if (inx == -1) return trie[n].val;
    if (x&(1ll<<inx)) {
        return trie[n].val + query(x, inx-1, trie[n].r);
    } else {
        return trie[n].val + query(x, inx-1, trie[n].l);
    }
}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t, n, m; cin >> t >> n >> m;
    vector<int> a(n), b(n);
    int mx = 0;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) {
        add(a[i], b[i], 31);
    }
    int l = 0;
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        k = k^(l*t);
        int ans = query(k, 31)+1;
        cout << ans << "\n";
        l = ans;
    }
    
}
