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
    int n, m, k; cin >> n >> m >> k;
    vector<char> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    vector<int> q;
    int l = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1'){
            l = 0;
        }
        else l++;
        if (l >= m) {
            // need to use one at this point
            ans+=1;
            for (int j = 0; j < k; j++) {
                i++;
            }
            l = 0;
            i--;
        }
    }
    cout << ans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while(t--)solve();
}
