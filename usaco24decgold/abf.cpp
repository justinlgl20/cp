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

int find(vector<int> &v, int x) {
    if (v.size() == 0) return 0;
    int start = v[0];
    int ans = 1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] - start <= x) continue;
        start = v[i];
        ans++;
    }
    return ans;
}

int32_t main() {
    int n; cin >> n;
    vector<vector<int>> g(n+2, vector<int>());
    for (int i = 1; i <= n; i++) {
        int id; cin >> id;
        g[id].push_back(i);
    }
    int init_ans = 0;
    vector<int> add(n+3, 0);
    dbg(g[1]);
    dbg(find(g[1], 1));
    for (int i = 1; i <= n; i++) {
        int ans = 0;
        for (int j = 1; j <= n; j++) ans += find(g[j], i);
        cout << ans << '\n';
    }
}
