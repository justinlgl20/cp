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
 
int r, c;
 
int grid[1005][1005];
int no[1005][1005];
int dist[1000005];
bool seen[1000005];
 
vector<int> adj[1000005][2];
 
int32_t main() {
#ifndef DEBUG
    freopen("ogres.in", "r", stdin);
    freopen("ogres.out", "w", stdout);
#endif
    r = nxt();
    c = nxt();
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            char q; cin >> q;
            grid[i][j] = not(q=='#');
            dbg(i, j, grid[i][j]);
        }
    }
 
    int x = 1;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) no[i][j] = x++;
    function<int(int, int)> id = [&](int i, int j) {
        return no[i][j];
    };
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            dist[id(i, j)] = 1e18;
            if (j < c) {
                adj[id(i, j)][grid[i][j+1]].push_back(id(i, j+1));
                if (i > 1) {
                    adj[id(i, j)][grid[i-1][j+1]].push_back(id(i-1, j+1));
                    adj[id(i, j)][grid[i-1][j]].push_back(id(i-1, j));
                }
                if (i < r) {
                    adj[id(i, j)][grid[i+1][j+1]].push_back(id(i+1, j+1));
                    adj[id(i, j)][grid[i+1][j]].push_back(id(i+1, j));
                }
            }
            if (j > 1) {
                adj[id(i, j)][grid[i][j-1]].push_back(id(i, j-1));
                if (i > 1) {
                    adj[id(i, j)][grid[i-1][j-1]].push_back(id(i-1, j-1));
                }
                if (i < r) {
                    adj[id(i, j)][grid[i+1][j-1]].push_back(id(i+1, j-1));
                }

            }
        }
    }
    deque<int> todo;
    vector<int> order;
    for (int i = 1; i <= r; i++) {
        //dist[id(i, 1)] = grid[i][1];
        //todo.push_back(id(i, 1));
        adj[0][grid[i][1]].push_back(id(i, 1));
        dbg(grid[i][1], id(i, 1));
    }
    todo.push_back(0);
    seen[0] = false;
    while (todo.size()) {
        int u = todo.front();
        todo.pop_front();
        if (seen[u]) continue;
        seen[u] = 1;
        dbg(u, dist[u]);
        
        for (auto i : adj[u][1]) {
            if (dist[u]+1ll < dist[i]) {
                dbg(i);
                dist[i] = dist[u]+1ll;
                todo.push_back(i);
            }
        }
        for (auto i : adj[u][0]) {
            if (dist[u]+0ll < dist[i]) {
                dbg(i);
                dist[i] = dist[u];
                todo.push_front(i);
            }
        }
    }
    int ans = 1e18;
    for (int i = 1; i <= r; i++) {
        ans = min(ans, dist[id(i, c)]);
    }
    cout << ans << "\n";
}
