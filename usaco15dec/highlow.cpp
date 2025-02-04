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

int32_t main() {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    int n; cin >> n;
    vector<int> cards(n);
    generate(all(cards), nxt);
    set<int> mine;
    for (int i = 1; i <= 2*n; i++) mine.insert(i);

    for (auto i : cards) {
        mine.erase(mine.find(i));
    }

    vector<int> start(n+4, 0);
    vector<int> finish(n+4, 0);
    set<int> m = mine;
    int score = 0;
    for (int i = 1; i <= n; i++) { // if i have i
        auto use = mine.lower_bound(cards[i-1]);
        if (use != mine.end()) {
            score += 1;
            mine.erase(use);
        }
        start[i] = score;
    }
    score = 0;
    for (int i = n; i > 0; i--) {
        auto use = mine.lower_bound(cards[i-1]);
        if (use != mine.end()) {
            score += 1;
            mine.erase(use);
        }
        finish[i] = score;
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, start[i]+finish[i+1]);
    }
    cout << ans << "\n";
}
