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

int scan() {
    int t; cin >> t; return t;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    // AABB -> ABAB -> BAAB -> BABA
    int first_a = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            first_a = i; break;
        }
    }
    if (first_a == -1) {
        cout << "0\n";
        return;
    }
    vector<bool> done(n+2, false);
    int start_a_chain = first_a;
    int length = 1;
    bool looking = false;
    int ans = 0;
    for (int i = first_a+1; i < n; i++) {
        if (s[i] == 'A') {
            if (looking) {start_a_chain = i;length = 0;}
            length += 1;
        } else {
            if (length) {
                ans += i-start_a_chain;
                length = 1;
                start_a_chain = i;
            }
        }
    }
    cout << ans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();

}
