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


int nxt() {
    int g; cin >> g; return g;
}

const int MOD = 1e9+7;
#define pii pair<int, int>
#define f first
#define s second

int no = 1;

void solve() {
    int s= nxt();
    vector<int> p(s);
    generate(all(p), nxt);
    
    int ans = 0;
    vector<pair<int, int>> idk;
    for (int i = 0; i < s; i++) {
        while (idk.size() and idk.back().s <= p[i]) {
            pair<int, int> g = idk.back();
            idk.pop_back();
            if (idk.size() == 0) continue;
            int r = s-i;
            int l = idk.back().f+1;
            l %= MOD;
            r %= MOD;
            dbg(l, r);
            ans %= MOD;
            dbg("ANS: ", ans);
            int add = ((min(idk.back().s, p[i])-g.s)%MOD)*(((int)-idk.back().f+i-1ll)%MOD)*r;
            add %= MOD;
            add *= l;
            add %= MOD;
            ans += add;
            ans %= MOD;
            dbg(min(idk.back().s, p[i])-g.s);
            dbg("NEW ANS: ", ans);
        }
        idk.emplace_back(i, p[i]);
    }
    cout << "Case #" << (no++) << ": " << ans << "\n";
}

int32_t main() {
    int t = nxt();
    while (t--) solve();
}
