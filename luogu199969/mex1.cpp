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

vector<int> cnt;
vector<int> d;
int scnt = 0;
int c, n;
bool b = 0;
void dfs(int j) {
    if (b or j > 40 or scnt > n or c < 0) return;
    //dbg(cnt, c, scnt);
    
    for (int i = 40; i >= 1; i--) {
        if (scnt+i <= n and (c % ((1ll<<i)-1ll) == 0)) {
            cnt.push_back(i);
            scnt += i;
            c /= ((1ll<<i)-1ll);
            
            c -= (1ll<<(n-scnt));
            if (c == 0) {
                d = cnt;
                b = 1;
                return;
            }
            dfs(j+1ll);
            c += (1ll<<(n-scnt));
            c *= ((1ll<<i)-1ll);
            cnt.pop_back();
            scnt -= i;
        }
    }
}

void solve() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    int extras = __builtin_ctz(q);
    dbg(extras);
    for (int i = 0; i <= extras; i++) {
        c = q/(1ll<<extras);
        if (c == 0) {
            d = {0};
        }
        else {
            dbg(c);
            for (int i = 3; i <= 40-extras; i++) {
                n = i;
                d.clear();
                cnt.clear();
                scnt = 0;
                b = 0;
                dfs(0);
                if (d.size()) break;
            }
            if (d.size()) break;
        }
    }
    dbg(d);
    if (d.size() == 0) {
        cout << "-1\n";
        return;
    }
    int x = 0;
    for (int i = 0; i < d.size(); i++) x += d[i];
    cout << x+extras << "\n";
    for (int i = 0; i < d.size(); i++) {
        for (int j = 0; j < d[i]; j++) cout << i << " ";
    }
    for (int i = 0; i < extras; i++) {
        cout << "41 ";
    }
    cout << "\n";

}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
