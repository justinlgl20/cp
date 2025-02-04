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

int nxt() {
    int x; cin >> x; return x;
}

#define idk(a, b, c) ((height[a] <= height[b] <= height[c])or(height[a]>=height[b]>=height[c]))


int modul(int x) {return x < 0 ? -x : x;}

int32_t main() {
    int n = nxt();
    vector<int> height;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        dbg(c);
        while (height.size() >= 2 and ((height[height.size()-2] <= height[height.size()-1] and height[height.size()-1] <= c) or (height[height.size()-2] >= height[height.size()-1] and height[height.size()-1] >= c))) height.pop_back();
        height.push_back(c);
    }
    dbg(height);
    n = height.size();
    dbg(n);
    auto id = [&](int i, int j) {
        return i*n+j;
    };
    vector<vector<pii>> adj(n*n+30, vector<pii>());
    vector<int> dist(n*n+n, 1e18);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            dist[id(i, j)] = 1e18;
            //wtaf is this cursed transition
            // i hate dp
            // i hate dp
            // i hate dp
            if (i+1 < n and idk(j, i+1, j+1)) {
                adj[id(i, j)].emplace_back(id(i+1, j), modul(height[i]-height[i+1]));
            }
            if (i-1 >= 0 and idk(j, i-1, j+1)) {
                adj[id(i, j)].emplace_back(id(i-1, j), modul(height[i]-height[i-1]));
            }
            if (i +1 < n and idk(i, j, i+1)) {
                adj[id(i, j)].emplace_back(id(j, i), modul(height[i]-height[j]));
            }
            if (i -1 >= 0 and idk(i, j, i-1)) {
                adj[id(i, j)].emplace_back(id(j, i-1), modul(height[i]-height[j]));
            }
            if (i+1 < n and idk(i, j+1, i+1)) {
                adj[id(i, j)].emplace_back(id(j+1, i), modul(height[i]-height[j+1]));
            }
            if (i-1>=0 and idk(i, j+1, i-1)) {
                adj[id(i, j)].emplace_back(id(j+1, i-1), modul(height[i]-height[j+1]));
            }
        }
    }

    dist[id(0, n-2)] = 0;
    function<bool(pair<int, int>, pair<int, int>)> qw = [&](pair<int, int> a, pair<int, int> b) {
        if (a.f == b.f) {
            int ai = a.s/n;
            int aj = a.s%n;
            int bi = b.s/n;
            int bj = b.s%n;
            if (ai == bi) return aj < bj;
            return ai < bj;
        }
        return a.f < b.f;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, function<bool(pair<int, int>, pair<int, int>)>> pq(qw); 
    pq.push({0, id(0, n-2)});
    while (pq.size()) {
        int d = -pq.top().f;
        int u = pq.top().s;
        int i = u/n;
        int j = u%n;

        assert(id(i, j) == u);
        pq.pop();
        if (d > dist[u]) continue;
        dbg(u, i, j, d);
        if (i == j or i-1 == j) {cout << d << "\n"; return 0;}
        for (auto i : adj[u]) {
            dbg(i.f, i.s, d+i.s, dist[i.f]);
            if (d+i.s < dist[i.f]) {
                dist[i.f] = d+i.s;
                pq.push({-dist[i.f], i.f});
            }
        }
    }
    int ans = 1e18;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            if (i == j or i == j+1) ans = min(ans, dist[id(i, j)]);
        }
    }
    if (ans != 1e18) cout << ans << "\n";
    else cout << "No\n";

}
