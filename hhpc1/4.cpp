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
    int c; cin >> c;

    if (c == 1) {
        cout << "1\n";
        return;
    }
    vector<int> pf;
    int n = c;
    while (n%2 == 0) {
        pf.push_back(2);
        n/=2;
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            pf.push_back(i);
            n /= i;
        }
    }
    if (n > 1) pf.push_back(n);

    int last = pf[0];
    int cnt = 0;
    vector<pii> stuff;
    for (auto i : pf) {
        if (i == last) cnt++;
        else {
            stuff.emplace_back(cnt, last);
            dbg(cnt, last);
            cnt = 1;
            last = i;
        }
    }
    stuff.emplace_back(cnt, last);
    dbg(cnt, last);
    int total = 2*stuff[0].f+1;
    for (int i = 1; i < stuff.size(); i++) total *= (2*stuff[i].f+1ll);
    if (c == 1) total = 1;
    cout << total << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
