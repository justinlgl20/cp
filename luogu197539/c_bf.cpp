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

int x[500005];
int y[500005];

int32_t main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int last = 0;
    for (int i = 0; i < q; i++) {
        char q; cin >> q;
        if (q == 'Q') {
            int l, r; cin >> l >> r;
            l^=last;
            r^=last;
            int ans = 1e9;
            for (int i = 0; i < n; i++) {
                if (l <= x[i] and x[i] <= r and l <= y[i] and y[i] <= r) {
                    ans = min(ans, x[i]-y[i]);
                }
            }
            if (ans == 1e9) ans = 0;
            cout << ans << "\n";
            last = ans;
        } else {
            int i, x, y; cin >> i >> x >> y;
            i^=last;
            x^=last;
            y^=last;
            ::x[i] = x;
            ::y[i] = y;
        }
    }
}
