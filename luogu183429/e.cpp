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

void solve() {
    using milli = std::chrono::milliseconds;
    auto start = std::chrono::high_resolution_clock::now();
    int n, k; cin >> n >> k;
    vector<pii> ranges;
    int spec = -1;
    int qw = 1e9, wq = 0;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        ranges.emplace_back(l, r);
        qw = min(qw, r);
        wq = max(wq, l);
        if (l == r) spec = l;
    }
    vector<pii> q = ranges;
    sort(all(q), [&](pii a, pii b) {
            return a.s-a.f < b.s-b.f;
            });
    if (spec == -1) {
        int ans = -1;
        if (wq < qw) {
            ans = wq;
        } else {
        for (int g = k;g <= qw+1; g++) {
            if (g == qw+1) 1/0;
            auto finish = std::chrono::high_resolution_clock::now();
            int s = std::chrono::duration_cast<milli>(finish - start).count();
            //if (s > 450) break;
            bool works = 1;
            for (int i = 0; i < n; i++) {
                if (!(ceil((double)q[i].f/(double)g) <= floor((double)q[i].s/(double)g))) {works=0;break;}
            }
            if (works) {ans = g; break;}
        }
        }
        if (ans != -1) {
            cout << "Yes" << "\n";
            for (auto i : ranges) {
                cout << ans * (int)ceil((double)i.f/ans) << " ";
            }
            cout << "\n";
        } else {
            cout << "No\n";
        }
    } else {
        int ans = -1;
        // get all factors of spec
        int num = spec;
        int square_root = (int) sqrt(num) + 1;
        vector<int> factors;
        for (int i = 1; i < square_root; i++) {
            if (num % i == 0&&i*i!=num) {
                factors.push_back(i);
                factors.push_back(num/i);
            }
            if (num % i == 0&&i*i==num) {
                factors.push_back(i);
            }
        }
        for (int g : factors) {
            if (g < k) continue;
            auto finish = std::chrono::high_resolution_clock::now();
            int s = std::chrono::duration_cast<milli>(finish - start).count();
            if (s > 250) break;
            bool works = 1;
            for (int i = 0; i < n; i++) {
                if (!(ceil((double)q[i].f/(double)g) <= floor((double)q[i].s/(double)g))) {works=0;break;}
            }
            if (works) {ans = g; break;}
        }
        if (ans != -1) {
            cout << "Yes" << "\n";
            for (auto i : ranges) {
                cout << ans * (int)ceil((double)i.f/ans) << " ";
            }
            cout << "\n";
        } else {
            cout << "No\n";
        }

    }

}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    for (int _ = 0; _ < t; _++) {
        solve();
    }
}
