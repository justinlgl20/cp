#include <bits/stdc++.h>
using namespace std;
 
#define int long long

#define ll int
 
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

void solve() {
    int n, k; cin >> n >> k;
    vector<int> x(n);
    multiset<int> g;
    for (int i = 0; i < n; i++) {cin >> x[i];}
    sort(all(x));
    int inx = 0;
    vector<pair<pii, int>> ranges(k);
    for (int i = 0; i < k; i++) {
        cin >> ranges[i].f.f >> ranges[i].f.s >> ranges[i].s;
    }
    for (int i = 0; i < k; i++) {
        int s = ranges[i].f.f;
        int e = ranges[i].f.s;
        //bsearch to find where e covers up to
        int q = 0;
        for (int qw = 20; qw >= 0; qw--) {
            if (q+(1ll<<qw) < n and x[q+(1ll<<qw)] <= e) {
                q += (1ll<<qw);
            }
        }
        int d = n-1;
        for (int qw = 20; qw >= 0; qw--) {
            if (d-(1ll<<qw) >= 0 and x[d-(1ll<<qw)] >= s) {
                d -= (1ll<<qw);
            }
        }
        dbg(ranges[i].f.f, ranges[i].f.s);
        if (ranges[i].f.s-ranges[i].f.f+1ll == 0) {
            ranges[i].s = -1;
        } else {
            ranges[i].s = (q-d+1ll) - ranges[i].s; // how many i can cut down
        }
        dbg(ranges[i].s);
    }
    ranges.emplace_back(make_pair(0, 1e9), 1e9);
    int ans = 0;
    for (int i : x) {
        int m = 1e9;
        for (auto x : ranges) {
            if (x.f.f <= i and i <= x.f.s) {
                m = min(m, x.s);
            }
        }
        if (m > 0) {
            ans++;
            dbg(i);
            for (auto &x : ranges) {
                if (x.f.f <= i and i <= x.f.s) {
                    x.s--;
                }
            }
        }

    }
       
    cout << ans << '\n';


}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
