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

int a[10005];

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, smol=4e9; cin >> n;
    for (int i = 1; i <= n; i++) {cin >> a[i];smol = min(smol, a[i]);}
    smol/=4;
    int ans = 0;
    dbg(n, smol);
    for (int i = 1; i <= smol; i++) {
        unordered_set<int> stuf;
        bool c= true;
        for (int j = 1; j <= n and c; j++) {
            stuf.insert(a[j]%i);
            if (stuf.size() > 3) c = false;
        }
        if (c) ans += i;
    }
    cout << ans << "\n";


}
