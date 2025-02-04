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

int comp[200005];
vector<pii> from[200005];
vector<pii> go[200005];
int dp[200005][105];

const int MOD = 998244353;

int32_t main() {
    int n, m, k; cin >> n >> m >> k;
    vector<pii> edges;
    set<int> relevant;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        edges.emplace_back(a, b);
        if (b == (a)%n+1) continue;
        relevant.insert(a);
        relevant.insert(b);
    }
    relevant.insert(1);
    relevant.insert(n);
    int cnt = 1;
    dbg(relevant);
    for (int i : relevant) {
        comp[i] = cnt;
        cnt++;
    }
    for (auto i : edges) {
        int a = comp[i.f], b = comp[i.s];
        int g = abs(i.f-i.s);
        go[a].push_back({b, 1});
        from[b].push_back({a, 1});
        dbg(a, b);
    }
    int last = *relevant.rbegin();
    for (int i : relevant) {
        //last ->i
        int a = comp[last];
        int b = comp[i];
        int l = min(abs(last-i), abs(n-(last-i)));
        go[a].push_back({b, l});
        from[b].push_back({a, l});
        last = i;
        dbg(a, b, l);
    }
    dp[0][1] = 1;
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < cnt; j++) {
            for (auto q : from[j]) {
                if (q.s <= i) {
                    dp[i][j] += dp[i-q.s][q.f];
                    dp[i][j] %= MOD;
                }
            }
            dbg(i, j, dp[i][j]);
            for (auto q : go[j]) {
                if (i < k and q.s > k-i) {ans += dp[i][j];
                    ans %= MOD;
                }
            }
        }
    }
    for (int i = 1; i < cnt; i++) {
        ans += dp[k][i];
        ans %= MOD;
    }
    cout << ans << "\n";

}
