
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
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<pii> smallest(n);
    smallest[n-1] = make_pair(a[n-1], n-1);
    for (int i = n-2; i >= 0; i--) {
        smallest[i] = min(smallest[i+1], make_pair(a[i], i));
    }

    int start = 0;
    multiset<int> things;
    vector<int> ans;
    while (start < n) {
        int go;
        if (things.size() and smallest[start].f > 1 + (*things.begin())) {
            dbg("FINISH", things);
            go = n;
        } else {
            ans.push_back(smallest[start].f);
            go = smallest[start].s;
        }
        dbg(start, go);
        for (int i = start; i < go; i++) {
            things.insert(a[i]);
        }
        start = go + 1;
    }
    for (auto i : things) {
        ans.push_back(i+1);
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i==n-1];
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
