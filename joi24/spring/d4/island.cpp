#include <bits/stdc++.h>
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

#include "island.h"

void solve(int32_t n, int32_t L) {
    vector<int> thingy(n+1), a(n+3), b(n+4);
    for (int i = 1; i <= n-1; i++) {
        int x = query(1, i);
        thingy[i-1] = x;
        a[x] = i;
    }
    for (int j = 0; j < n-1; j++) {
        int i = thingy[j];
        if (b[i]) continue;
        for (int k = 1; k <= n-1; k++) {
            int z = query(i, k);
            answer(z, i);
            b[z] = 1;
            if (a[z] < a[i]) break;
        }
    }

}
