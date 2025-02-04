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

void solve() {
    int n, k; cin >> n >> k;
    if (n <= 50 and k > (1ll<<(n-1ll))) {
        cout << "-1\n";
    } else {
        vector<int> f, b;
        k--;
        for (int i = n-1; i >= 1; i--) {
            if (n-1ll-i <= 50 and k&(1ll<<(n-1ll-i))) {
                b.push_back(i);
            } else {
                f.push_back(i);
            }
        }
        reverse(all(f));
        for (auto i : f) cout << i << " ";
        cout << n << " ";
        for (auto i : b) cout << i << " ";
        cout << "\n";
    }
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
