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

const int MOD = 1000000007;

int32_t main() {
    int n; cin >> n;
    vector<char> s(n+4);
    for (int i = 1; i <= n; i++) cin >> s[i];
    vector<int> dp(n+5, 0);
    dp[0] = 1;
    s[0] = 'R';
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        dbg(i);
        bool seen = false;
        for (int j = i-1; j >= 1; j--) {
            seen = seen or (s[j] != 'X');
            if (s[i] == 'X' and !seen) {
                dp[i] += dp[j-1];
                dp[i] %= MOD;
            }
            if ((i-j+1)%2 == 0) {
                // j to (i+j)/2 inclusive
                bool works = 1;
                for (int k = j; k <= (i+j)/2; k++) {
                    if (s[k] == 'B') works = false;
                }
                for (int k = (i+j)/2 + 1ll; k <= i; k++) {
                    if (s[k] == 'R') works = false;
                }
                if (works) {
                    dp[i] += dp[j-1];
                    dp[i] %= MOD;
                    dbg(j, dp[j-1]);
                }
            }
        }
    }
    cout << dp[n] << "\n";
}
