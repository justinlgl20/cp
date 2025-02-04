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

int f(int x) {
    return x*(x+1ll)/2;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(all(a));
    // IF WE HAVE DUPLICATES WE CAN TAKE SOME OFF THEM OR NOT
    int dup = 0;
    set<int> g;
    multiset<int> q;
    a.insert(a.begin(), 0);
    for (int i = 1; i <= n; i++) {
        g.insert(a[i]);
        q.insert(a[i]);
        if (a[i] == a[i-1]) {
            dup += (a[i]-1);
        }
    }
    int ans = g.size()+1;
    int k = 0; // how much we take off them
    for (int i = 1; i < ans; i++) {
        int w = (*q.lower_bound(i));
        assert(w >= i);
        k+= (w-i);
        q.erase(q.find(w));
    }
    dbg(ans, k);
    auto w = q;
    for (auto i : w) {
        if (i >= ans) {
            k += i-ans;
            ans++;
            q.erase(q.find(i));
        }
    }
    dbg(q, k);
    dup = 0;
    for (auto i : q) dup += i-1ll;
    if (k <= ans) {
        // we could increase ans by 1 more if we have extra duplicates 
        if (dup >= ans-k) ans++;
    }
    cout << ans << "\n";

}

int32_t main() {
    int t; cin >> t;
    while(t--) solve();
}
