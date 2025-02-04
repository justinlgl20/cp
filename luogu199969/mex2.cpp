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

int find(int c, int i) {
    // return highest 2^something - 1 that divides it
    for (int i = log2(c)+1; i >= 0; i--) {
        if (c%((1ll<<i) - 1ll) == 0 and c/((1ll<<i)-1ll) >= (i+1)) {
            return i;
        }
    }
    return 0;
}

void solve() {
    int c; cin >> c;
    vector<int> cnt(41, 0);
    int extras = __builtin_ctz(c);
    dbg(extras);
    c /= (1ll<<extras);
    dbg(c);
    for (int i = 0; i <= 40; i++) {
        int g = find(c, i);
        dbg(i, g);
        cnt[i] = g;
        c /= (1ll<<g)-1ll;
        c -= i+1;
        if (c == 0) break;
    }
    for (int i = 0; i <= 40; i++) {
        for (int j = 0; j < cnt[i]; j++) cout << i << " ";
    }
    for (int i = 0; i < extras; i++) cout << 1e9 << " ";
    cout << "\n";

}

int32_t main() {
    int t; cin >> t;
    while(t--) solve();
}
