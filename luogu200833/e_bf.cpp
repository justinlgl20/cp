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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    multiset<int> s;
    while (q--) {
        int opt; cin >> opt;
        if (opt == 1) {
            int a; cin >> a;
            s.insert(a);
        } else if (opt == 4) {
            int a; cin >> a;
            int m = 0;
            for (int i : s) {
                int g;
                if ((a^i) == 0ll) {
                    g = 1ll<<32;
                } else {
                    g = a^i;
                }
                dbg(i, a^i, g);
                if (__builtin_ctz(g) > m) {
                    m = __builtin_ctz(g);
                }
            }
            cout << (1ll<<m) << "\n";
        } else if (opt == 2) {
            int a; cin >> a;
            s.erase(s.find(a));
        } else if (opt == 3) {
            int x, k, v; cin >> x >> k >> v;
            vector<int> todo;
            for (int i : s) {
                
                int g = ((x^i)==0)?(1ll<<32):(x^i);
                if (__builtin_ctz(g) >= k) {
                    todo.push_back(i);
                }
            }
            for (auto i : todo) {
                s.erase(s.find(i));
                s.insert(i+v);
            }
        }
    }
}
