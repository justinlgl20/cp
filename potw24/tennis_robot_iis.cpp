#include <bits/stdc++.h>
#include <climits>
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

int a[2000005], b[2000005];
const int MAXM = 200000;


int32_t main() {
#ifndef DEBUG
    freopen("tennisin.txt", "r", stdin);
    freopen("tennisout.txt", "w", stdout);
#endif
    int n, m; cin >> n >> m;
    vector<int> x(n+2, 0);
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
    vector<int> round(n+3, 0);
    vector<int> mins(n+3, 0);
    vector<vector<pii>> lows(n+3, vector<pii>(1, make_pair(0, 0)));
    for (int i = 1; i <= m; i++) {
        round[a[i]]--;
        if (round[a[i]] < mins[a[i]]) {
            mins[a[i]] = round[a[i]];
            lows[a[i]].emplace_back(i, round[a[i]]);
        }
        round[b[i]]++;
    }
    function<int(int, int)> solve = [&](int bin, int x) {
        if (lows[bin].size() == 1 or (round[bin] >= 0ll and x + mins[bin] >= 0ll)) return LLONG_MAX;
        int rounds;
        if (round[bin] >= 0ll) rounds = 0ll;
        else rounds = (x + mins[bin])/(-round[bin]);
        while (x + (rounds*round[bin]) >= -mins[bin]) {
            rounds++;
        }
        int ans = rounds*m;
        x += rounds*round[bin];
        dbg(rounds);
        // now we look for the first pos in lows where lows[i].s + x < 0
        int i = 0;
        for (int j = 20; j >= 0; j--) {
            if (i + (1ll<<j) < (int)(lows[bin].size()) and lows[bin][i+(1ll<<j)].s + x >= 0ll) {
                i += (1ll<<j);
            }
        }
        i++;
        dbg(lows[bin][i].f, lows[bin][i].s);
        ans += lows[bin][i].f;
        assert(ans != 0ll);
        ans--;
        return ans;
    };
    vector<int> anss(n+3, LLONG_MAX);
    vector<int> psm(n+3, LLONG_MAX);
    int ans = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        int g = solve(i, x[i]);
        ans = min(ans, g);
        dbg(i, x[i], g);
        anss[i] = g;
        psm[i] = min(psm[i-1], anss[i]);
    }
    vector<int> ssm(n+3, LLONG_MAX);
    for (int i = n; i >= 1; i--) {
        ssm[i] = min(ssm[i+1], anss[i]);
    }
    if (psm[n] == LLONG_MAX) {
        cout << "FOREVER\n";
    } else 
        cout << psm[n] << "\n";
    int q; cin >> q;
    while (q--) {
        int c, y; cin >> c >> y;
        int g = solve(c, y);
        int an = min(ans, g);
        if (an == LLONG_MAX) {
            cout << "FOREVER\n";
        } else {
            cout << an << "\n";
        }
    }

}
