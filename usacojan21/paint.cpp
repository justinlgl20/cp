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

int n, q;

int last[30];
int pre[100005], suf[100005];

int32_t main() {
    string s;
    cin >> n >> q >> s;

    vector<int> stuff(n+4);
    for (int i = 1; i <= n; i++) stuff[i] = s[i-1]-'A';

    for (int i = 0; i < 30; i++) last[i] = -1;
    for (int i = 1; i <= n; i++) {
        int c = stuff[i];
        pre[i] = pre[i-1];
        for (int j = 0; j < 26; j++) last[j] = min(c, last[j]);
        if (last[c] < c) pre[i]++;
        last[c] = c;
    }
    for (int i = 0; i < 30; i++) last[i] = -1;
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i+1];
        int c = stuff[i];
        for (int j = 0; j < 26; j++) last[j] = min(c, last[j]);
        if (last[c] < c) suf[i]++;
        last[c] = c;
    }
    while (q--) {
        int l, r; cin >> l >> r;
        cout << pre[l-1]+suf[r+1] << "\n";
    }

}
