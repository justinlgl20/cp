#include <bits/stdc++.h>
using namespace std;

#define int long long

#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> t) {
    int g = t.size(); os << "{"; for (auto i : t) os << i << ((--g)?", ":""); os << "}";
    return os;
}

void _print() {
    cerr << "]\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " " << "[" << #x << "]" << " = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int nxt() {
    int g; cin >> g; return g;
}

const int MOD = 1000000007;

int32_t main() {
    int r, c, k; cin >> r >> c >> k;
    vector<vector<int>> val(r, vector<int>(c, 0));
    for (auto &i : val) {
        generate(all(i), nxt);
    }
    vector<vector<int>> dp(r, vector<int>(c, 0));
    dp[0][0] = 1;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            for(int k = i+1; k < r; k++) {
                for(int l = j+1; l < c; l++) {
                    if(val[i][j] != val[k][l]) {
                        dp[k][l] += dp[i][j];
                        dp[k][l] %= MOD;
                    }
                }
            }
        }
    }
    cout << dp[r-1][c-1] << "\n";
}
