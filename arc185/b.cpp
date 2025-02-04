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

struct segtree {
    vector<int> t;
    int n;
    segtree(int n) {
        this->n = 1;
        while (this->n <= n) this->n *= 2;
        t.resize(n*2+4);
        for (int i = 0; i < n*2+3; i++) t[i] = 0;
    }
    void upd(int p, int v) {
        for (t[p+=n] += v; p > 1; p>>=1) {
            t[p>>1] = t[p]+t[p^1];
        }
    }
    int query(int l, int r) {
        r++;
        int ans = 0;
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) ans += t[l++];
            if (r&1) ans += t[--r];
        }
        ans += 1;
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int owe = 0;
    int sum = a[0];
    for (int i = 1; i < n; i++) {
        int last = ceil((double)sum/i);
        if (a[i] > last) {
            int take = min(a[i]-last, owe);
            owe -= take;
            a[i] -= take;
            
            sum += a[i];
            int g = ceil((double)(sum)/(i+1)); // this is what we can make this one
            dbg(i, g);
        } else if (a[i] <= last){
            int add = last-a[i];
            owe += add; // gotta take owe off later
            int g = last; // this one becomes this
            sum += g;
            dbg(i, g);
        }
    }
    if (owe) cout << "No\n";
    else cout << "Yes\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
