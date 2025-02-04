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
    int q, b; cin >> q >> b;
    vector<int> a = {b, b};
    int s = 1000 * q - b - b;
    //if (q < b) { // we want to make it lower
        dbg(499, b);
        for (int i = 0; i < 499; i++) {
            a.push_back(b);
            s -= b;
        }
        dbg(s);
        dbg(abs(s)%499, (s/499)+1);
        for (int i = 0; i < abs(s) % 499; i++) {
            a.push_back((s/499) + 1ll*(s > 0) - 1ll*(s<0));
        }
        dbg(499 - (abs(s)%499), s/499);
        for (int i = 0; i < 499 - (abs(s)%499); i++) {
            a.push_back(s / 499);
        }
    //}
    cout << "1000\n";
    for (int i : a) cout << i << " ";
    cout << "\n";
}
