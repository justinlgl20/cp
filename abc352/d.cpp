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

vector<int> p;

int works(int length) {
    set<pii> ranges;
    int longest = 0;
    auto add = [&](int u) {
        if (ranges.size() == 0) {
            ranges.insert(make_pair(u, u));
            longest = max(longest, 1);
            return;
        }
        if (ranges.size() == 1) {

        }
        auto g = ranges.lower_bound(make_pair(u, 0));
        if (g == ranges().end()) {
            // nothing after
        }
        else if (g == ranges.begin()){
            // nothing before
        }
        else {
            pii after = *g;
            g--;
            pii before = *g;
            pii ans = make_pair(u, u);
            if (after.f == u+1) {ans.s = after.s;ranges.erase(ranges.find(after));}
            if (before.s == u-1) {ans.f = before.f; ranges.erase(ranges.find(before));}
            ranges.insert(ans);
            longest = max(longest, (ans.s-ans.f+1));
        }
    };
    for (int i = 0; i < length; i++) {
        add(p[i]);
    }
}

int32_t main() {
    int n, k; cin >> n >> k;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i];
    int ans = 0
}
