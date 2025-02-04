#include <bits/stdc++.h>
using namespace std;
 
#define int unsigned long long
 
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

int n, m;

int solve(int a, int b) {
    if (a > n or a <= 0ll) return (int)(696969696);
    if (b > m or b <= 0ll) return (int)(696969696);
    dbg(a, b);
    int hrow = n/(int)2;
    if (n%(int)2 == (int)1 and a%(int)2 == 0ll) {
        hrow += (int)1;
    }
    int ans = m*hrow;
    int drow = n-hrow;
    int cnt = m/(int)2;
    if (m%(int)2 == (int)1 and b%(int)2 == 0ll) {
        cnt += (int)1;
    }
    int l = drow*cnt;
    ans += l;
    dbg(ans);
    return ans;

}

int32_t main() {
    cin >> n >> m;
    int a, b, x; cin >> a >> b >> x;
    dbg((int)9223372030412324865+(int)4611686016279904256);
    if (x == 0) {
        cout << solve(a, b) << "\n";
    } else {
        vector<int> an = {solve(a+(int)1, b), solve(a-(int)1, b), solve(a, b+(int)1), solve(a, b-(int)1), solve(a-(int)1, b-(int)1), solve(a-(int)1, b+(int)1), solve(a+(int)1, b-(int)1), solve(a+(int)1, b+(int)1), solve(a, b)-1};
        int ans = 18446744073709551615;
        for (int i : an) {
            if (i != 696969696) ans = min(ans, i);
        }
        if (n == (int)1) {
            ans = m/(int)2 + (b%(int)2==(int)1);
        }
        if (m == (int)1) {
            ans = n/(int)2 + (a%(int)2==(int)1);
        }
        cout << ans << "\n";

    }
}
