#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
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

#define pii pair<int, int>
#define f first
#define s second

#define map tree<int, int, less<int>, rb_tree_tag, tree_order_statistics_node_update>

int add[200005];
int pos[200005];
map in;

int32_t main() {
    int n = nxt();
    vector<int> a(n);
    generate(all(a), nxt);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        auto thingy = in.upper_bound(a[i]);
        if (thingy != in.end()) {
            dbg("IN");
            if (((*thingy).s > (*prev(thingy)).s) or (thingy == in.begin())) {dbg("ADD"); add[a[i]]++;}
        }
        if (pos[a[i]-1] > pos[a[i]]) add[a[i]]--;
        dbg(a);
        in[a[i]] = i;
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        dbg(i, add[i]);
        ans += add[i];
        cout << ans << "\n";
    }
}
