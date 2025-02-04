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
    int x; cin >> x; return x;
}

int dp[305][305][35];
// post office placed here, last place post office was placed, no. of post offices placed

int32_t main() {
    int v = nxt(), p = nxt();
    vector<int> pos(v+1);
    generate(1+all(pos), nxt);
    vector<int> psa(v+1, 0);
    for (int i = 1; i <= v; i++) psa[i] = psa[i-1]+pos[i];
    dp[1][0][2] = 0;
    dp[1][0][1] = min(abs(pos[2]-pos[1]));
    for (int i = 2; i <= v; i++) {
        for (int j = 0; j < i; j++) {
            // placing at post office i, last is from post office j
            for (int k = 3; k <= p; k++) {
                for (int q = 0; q < j; q++) {
                    dp[i][j][k] = min(dp[i][j][k], dp[j][q][k-1]+(
                }
            }
        }
    }
}
