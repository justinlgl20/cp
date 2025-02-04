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

const int MOD = 998244353;

int trie[40005];
int children[40005][10];

int active[90];

vector<int> vals; // substring sums ending on u
int cnt = 1;
void dfs(int u) {
    for (int i = 0; i <= 9; i++) {
        // check if adding i to front of sequence makes it bad or not
        bool good = true;
        for (int j = 0; j < vals.size(); j++) {
            vals[j] += i;
            if (active[vals[j]]) {good = false;}
            active[vals[j]] += 1;
        }
        if (good) {
            vals.push_back(i);
            cnt++;
            children[u][i] = cnt;
            dfs(cnt);
            vals.pop_back();
        }
        for (int j = 0; j < vals.size(); j++) {
            active[vals[j]] -= 1;
            vals[j] -= i;
        }
    }
}

int dp[15000005];

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string s; cin >> s;
    int n = s.size();

    int k = 9;
    dfs(1);

    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        int node = 1;
        int c = s[i-1]-'0';
        node = children[node][c];
        int from = i-1;
        while (from >= 0 and node != 0) {
            dp[i] += dp[from];
            dp[i] %= MOD;
            node = children[node][s[from-1]-'0'];
            from--;
        }
    }
    cout << dp[n] << "\n";
}
