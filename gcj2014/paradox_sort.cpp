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

int nxt() {int g; cin >> g; return g;}

vector<vector<int>> adj;

vector<int> seen;

void dfs(int u) {
    dbg(u);
    for (auto i : adj[u]) {
        if (seen[i] == 0) {seen[i] = true; dfs(i);}
    }
}

vector<int> ans;

int n, A;

bool check() {
    for (int i = 0; i <= n; i++) seen[i] = false;
    for (auto i : ans) seen[i] = true;
    seen[A] = true;
    dfs(A);
    bool ans = 1;
    for (int i = 0; i <= n-1; i++) ans = (ans&&seen[i]);
    return ans;
}

int no = 1;
int pref[105][105];
void solve() {
    n = nxt();
    A = nxt();
    adj.resize(n);
    for (int i = 0; i < n; i++) adj[i] = {};
    seen.resize(n);
    ans = {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            pref[i][j] = 0;
            if (c == 'Y') {
                adj[i].push_back(j);
                pref[i][j] = 1;
            }
        }
    }
    dbg(adj);
    bool a = check();
    if (a == false) {
        cout << "Case #" << (no++) << ": IMPOSSIBLE\n";
        return;
    }
    int inx = 0;
    vector<int> put_in(n);
    int cnt = 0;
    while ((cnt++) < 50 and ans.size() < n-1) {
        while (put_in[inx]) {inx++;inx%=n;}
        ans.push_back(inx);
        if (inx == A) {
            // A must be preferred over everything left
            bool can = true;
            for (int i = 0; i < n; i++) {
                if (!put_in[i] and i != A) can = can&&(pref[A][i]);
            }
            
            if (can) {put_in[A] = true; continue;}
        }
        //dbg(ans);
        a = check();
        dbg(ans, a);
        if (a == false) {
            ans.pop_back();
            inx++;
        } else {
            put_in[inx] = true;
        }
    }
    cout << "Case #" << (no++) << ": ";
    for (auto i : ans) cout << i << " ";
    cout << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
