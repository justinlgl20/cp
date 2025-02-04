#include <bits/stdc++.h>
#include "rocks.h"
using namespace std;
 
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

int find_heavy_rock(int n, vector<int> t) {
    vector<int> psa(n+2,0);
    for (int i = 1; i <= n; i++) {
        psa[i] = psa[i-1]+t[i-1];
    }
    function<int(int, int)> sum = [&](int l, int r) {
        return psa[r+1]-psa[l];
    };
    int l=0, r=n-1;
    while (l != r) {
        int m = (l+r)>>1;
        vector<int> c;
        for (int i = l; i <= m; i++) c.push_back(i);
        int g = use_scales(c);
        if (g == sum(l, m)) {
            l = m+1;
        } else {
            r = m;
        }
    }
    return l;
}
