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

const int MOD = 1000000007;
const int INVMOD = 500000004;
const int INV6 = 166666668;
const int INV3 = 333333336;

int power(int a, int b) {
    int result = 1;
    while (b) {
        if (b&1) {
            result = result*a;
            result %= MOD;
        }
        a *= a;
        a %= MOD;
        b>>=1;
    }
    return result;
}

int sq(int x) {
    return ((x%MOD)*((x+1ll)%MOD)*INVMOD)%MOD;
}

int sum(int l, int r) {
    return (sq(r) - sq(l-1ll) + MOD) % MOD;
}

int32_t main() {
    int n, q; cin >> n >> q;
    /*
    vector<int> ans(n+3, 0);
    vector<int> pos(n+3, 0);
    ans[1] = (power(2, n)-1ll+MOD)%MOD;
    pos[1] = power(2, n);
    dbg(pos[1]);
    for (int x = 2; x <= n; x++) {
        pos[x] = pos[x-1]*2;
        pos[x] %= MOD;
        pos[x] += power(2, n-x+1ll);
        pos[x] %= MOD;
        dbg(pos[x]);
        int neg = ((power(2, x)+4ll)%MOD)*((power(2ll, x)-1ll+MOD)%MOD);
        neg %= MOD;
        neg *= INV6;
        neg %= MOD;
        ans[x] = (pos[x] - neg + MOD + MOD)%MOD;
    }*/
    while (q--) {
        int k; cin >> k;
        string s; cin >> s;
        int x = n-k+1ll;
        int neg = ((power(2, x)+4ll)%MOD)*((power(2ll, x)-1ll+MOD)%MOD);
        neg %= MOD;
        neg *= INV6;
        neg %= MOD;
        int y = x-1;
        int pose = power(2, y)*power(2, n);
        pose %= MOD;
        pose += ((((power(4, y)-1+MOD)%MOD)*INV3)%MOD)*power(2, n-x+1);
        pose %= MOD;
        int a = pose-neg+MOD+MOD;
        a %= MOD;
        cout << a << "\n";
    }
}
