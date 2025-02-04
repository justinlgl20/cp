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

int32_t main() {
    int n, k; cin >> n >> k;
    vector<pii> stuff;
    stuff.emplace_back(0, 0);
    for (int i = 0; i < n; i++) {
        int c, v; cin >> c >> v;
        stuff.emplace_back(c, v);
    }
    vector<vector<int>> dp(n+3, vector<int>(k+3, 0));
    vector<pii> top(n+k+50, make_pair(0, 0));
    vector<pii> second(n+k+50, make_pair(0, 0));
    function<int(int, int)> diagonal = [&](int i, int j) {
        return (i-j+k+1);
    };

    int removed = 0;
    int l = 0;
    int last = stuff[1].f;
    for (int i = 1; i <= n; i++) {
        if (stuff[i].f == last) {
            l++;
        } else {
            dbg(i);
            removed += (l-1);
            l = 1;
            last = stuff[i].f;
        }
    }
    removed += l-1;


    dbg(removed);

    if (removed > k) {
        cout << "-1\n";
        return 0;
    }


    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            if (j >= i) {
                dp[i][j] = -1e18;
                continue;
            }
            int row = diagonal(i, j) - 1;
            pii best;
            if (top[row].s == stuff[i].f) {
                best = second[row];
            } else {
                best = top[row];
            }
            dbg(best.f, best.s);
            dp[i][j] = best.f + stuff[i].s;
            row++;
            pii option = make_pair(dp[i][j], stuff[i].f);
            if (stuff[i].f == top[row].s) {
                top[row] = max(top[row], option);
            } else {
                if (option > top[row]) {
                    second[row] = top[row];
                    top[row] = option;
                } else {
                    second[row] = max(second[row], option);
                }
            }
            dbg(i, j, dp[i][j]);
            if (j == k) {
                ans = max(ans, dp[i][j]);
            }
        }
    }
    cout << ans << "\n";

}
