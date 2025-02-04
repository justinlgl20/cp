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

int n, m; 
 
struct state {
    int dir, steps;
    int i, j;
    bool legal() {
        if (steps > 3) return false;
        if (i < 0 or i >= n or j < 0 or j >= m) return false;
        return true;
    }
};

int32_t main() {
   cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    int sr, sc, er, ec;;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                sr = i, sc = j;
                grid[i][j] = '.';
            }
            if (grid[i][j] == 'T') {
                er = i, ec = j;
                grid[i][j] = '.';
            }
        }
    }
    queue<state> q;
    q.push(state{0, 0, sr, sc});
    vector<vector<vector<vector<int>>>> dist(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(4, 1e9))));
    dist[sr][sc][0][0] = 0;
    vector<pii> g = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };
    while (q.size()) {
        state u = q.front();
        if (u.i == er and u.j == ec) {
            cout << dist[u.i][u.j][u.dir][u.steps] << "\n";
            return 0;
        }
        q.pop();
        for (int i = 0; i < 4; i++) {
            state ne = u;
            ne.i += g[i].f;
            ne.j += g[i].s;
            if (i == ne.dir) ne.steps++;
            else {
                ne.dir = i;
                ne.steps = 1;
            }
            if (ne.legal() and dist[ne.i][ne.j][ne.dir][ne.steps] == 1e9 and grid[ne.i][ne.j] == '.') {
                dist[ne.i][ne.j][ne.dir][ne.steps] = dist[u.i][u.j][u.dir][u.steps]+1;
                q.push(ne);
            }
        }
    }
    cout << "-1\n";
}
