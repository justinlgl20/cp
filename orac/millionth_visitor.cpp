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
    vector<pii> peeps;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        peeps.emplace_back(a, b);
    }
    //binary search for day
    int lo = 0;
    int hi = 1e18;
    while (lo != hi-1) {
        int mid = (lo+hi)>>1;
        int num_before = 0;
        for (auto i : peeps) {
            if (i.f <= mid) {
                num_before += (mid-i.f)/i.s+1;
            }
        }
        if (num_before >= k) hi = mid;
        else lo = mid;
    }
    // on day of hi;
    vector<int> valid;
    for (int _ = 0; _ < peeps.size(); _++) {
        auto i = peeps[_];
        if (hi >= i.f and (hi-i.f)%i.s==0) {
            valid.push_back(_+1);
        }
    }
    assert(valid.size()>0);
    sort(all(valid));
    int num_before = 0;
    int mid = hi-1;
    for (auto i : peeps) {
        if (i.f <= mid) {
            num_before += (mid-i.f)/i.s+1;
        }
    }
    int ans = valid[k-num_before-1];
    cout << ans << "\n";
}
