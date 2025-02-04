#include <bits/stdc++.h>
using namespace std;

#define int long long

#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> stuff) {
    int g = stuff.size();
    os << "{";
    for (auto i : stuff) os << i << (--g?", ":"}");
    return os;
}

void _print() {cerr << "]\n";}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t;
    if (sizeof...(v)) cerr <<", ";
    _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

int nxt() {
    int x; cin >> x; return x;
}

int32_t main() {
    int n = nxt(), p = nxt(), Q = nxt();
    vector<int> pos(n);
    generate(all(pos), nxt);
    if (p+Q >= n) {
        cout << "1\n";
        return 0;
    }
    sort(all(pos));
    int ans = 1;
    for (int q = 1<<10; q > 0; q>>=1) {
        int pot = ans+q;
        bool works = false;
        vector<vector<int>> dp(n+2, vector<int>(p+2, -1e9)); // dp[pos][no. of small cameras used to cover up to this] = max no. of big cameras left
        for (int j = 1; j <= p; j++) dp[0][j] = Q;
        dp[0][0] = Q-1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= p; j++) {
                // place a small camera
                int from;
                if (j > 0) {
                    from = -1;
                    for (int a = 1<<10; a > 0; a>>=1) {
                        if (from+a < n and pos[from+a] <= pos[i]-pot) from += a;
                    }
                    if (from == -1) dp[i][j] = max(dp[i][j], Q);
                    else dp[i][j] = max(dp[i][j], dp[from][j-1]);
                }
                // place a big camera
                from = -1;
                for (int a = 1<<10; a > 0; a>>=1) {
                    if (from+a < n and pos[from+a] <= pos[i] - 2*pot) from += a;
                }
                if (from == -1) dp[i][j] = max(dp[i][j], Q-1);
                else dp[i][j] = max(dp[i][j], dp[from][j]-1);
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= p; j++) {
                dbg(i, j, dp[i][j]);
            }
        }
        for (int i = 0; i <= p; i++) {
            works = (works or (dp[n-1][i] >= 0));
        }
        dbg(pot, works);
        if (!works) ans += q;
    }
    cout << ans+1 << "\n";
}
