#include "september.h"
#include <bits/stdc++.h>
using namespace std;
 
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

int n, m;
vector<int> p;
vector<vector<int>> s;
vector<int> adj[100005];

int subtree_latest[100005];
int pos_in_perm[100005][6];

void dfs(int u, int pa) {
    subtree_latest[u] = pos_in_perm[u][pa];
    for (auto i : adj[u]) {
        dfs(i, pa);
        subtree_latest[u] = max(subtree_latest[u], subtree_latest[i]);
    }
}

vector<pii> ranges[7];

int ans = 0;

void one_dude() {
    for (int i = 0; i < s.size(); i++) {
        for (int j = 0; j < n-1; j++) {
            pos_in_perm[s[i][j]][i] = j;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        dfs(0, i);
    }
    for (int j = 0; j < s.size(); j++) {
        int length = 0;
        int start = 0;
        int i = 0, eor = 0;
        while (i < n-1) {
            eor = max(eor, subtree_latest[s[j][i]]);
            dbg(i, subtree_latest[s[j][i]], s[j][i]);
            length++; 
            if (eor == i) {
                dbg(start, i);
                ranges[j].emplace_back(start, i);
                start = i+1;
                eor = i+1;
                length = 0;
            }
            i++;
        }
    }
}

void overlap_find() {
    int x = s.size();
    set<int> stuff;
    int start = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < s.size(); j++) {
            stuff.insert(s[j][i]);
        }
        if (stuff.size() == (i-start+1)) {
            ranges[x].emplace_back(start, i);
            dbg(start, i);
            start = i+1;
            stuff.clear();
        }
    }
}

void find_ranges_overlap() {
    //ranges[0] to ranges[s.size()]
    vector<int> g(n+4, 0);
    for (int i = 0; i <= s.size(); i++) {
        for (int j = 0; j < ranges[i].size(); j++) 
            g[ranges[i][j].second]++;
    }
    int start = 0;
    for (int i = 0; i < n-1; i++) {
        if (g[i] == s.size()+1) {
            ans++;
            start = i+1;
        }
    }
}

int solve(int n, int m, std::vector<int> par, std::vector<std::vector<int>> S) {
    ::n = n;
    ::m = m;
    ::p = par;
    ::s = S;
    ans = 0;
    for (int i = 0; i <= n; i++) adj[i].clear();
    for (int i = 0; i < 7; i++) ranges[i].clear();
    for (int i = 1; i < n; i++) adj[p[i]].push_back(i);
    one_dude();
    overlap_find();
    find_ranges_overlap();
    return ans;
}
