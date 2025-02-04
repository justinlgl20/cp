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

int composite[200005];

int32_t main() {
    // CAN DO QUERIES OFFLINE
    int t; cin >> t;
    int n = 200004;
    vector<int> primes;
    composite[1] = 1;
    composite[0] = 1;
    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size(); j++) {
            if (i * primes[j] > n) break;
            composite[i*primes[j]] = 1;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    dbg(primes.size());
    for (int i = 0; i < t; i++) {
        cin >> n;
        int ans = 0;
        dbg(n);
        for (auto i : primes) {
            if (!composite[n%i]) {ans++;}
        }
        cout << ans << "\n";
    }
}
