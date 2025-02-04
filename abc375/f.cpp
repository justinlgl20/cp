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

vector<pii> adj[200005];
vector<pii> adj2[200005];

int visited[200005];
vector<int> ans;
int in_thing[200005];

void dfs(int v) {
    visited[v] = true;
    for (auto u : adj2[v]) {
        if (!visited[u.f])
            dfs(u.f);
    }
    ans.push_back(v);
}

void topsort() {
    for (int i = 1; i <= n; i++) {
        if (in_thing[i] and !visited[i]) {
            dfs(i);
        }
    }
    reverse(all(ans));
}

int good[200005];

int32_t main() {
    cin >> n >> m;
    unordered_map<int, unordered_map<int, int>> wq;
    vector<pair<int, pii>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
        wq[min(a, b)][max(a, b)] = i;
        edges.emplace_back(c, make_pair(a, b));
    }
    // bfs from 1
    priority_queue<pii> q;
    q.push({0ll, 1ll});
    vector<int> dist(n+2, 1e18);
    dist[1] = 0;
    while (q.size()) {
        int u = q.top().s;
        int d = -q.top().f;
        q.pop();
        if (dist[u] != d) {
            continue;
        }
        for (auto i : adj[u]) {
            if (d + i.s < dist[i.f]) {
                dist[i.f] = i.s+d;
                q.push({-dist[i.f], i.f});
            }
        }
    }

    q.push({0ll, n});
    vector<int> dist2(n+2, 1e18);
    dist2[n] = 0;
    while (q.size()) {
        int u = q.top().s;
        int d = -q.top().f;
        q.pop();
        if (dist2[u] != d) {
            continue;
        }
        for (auto i : adj[u]) {
            if (d + i.s < dist2[i.f]) {
                dist2[i.f] = i.s+d;
                q.push({-dist2[i.f], i.f});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dbg(i, dist[i], dist2[i]);
    }

    vector<pair<int, pii>> edges2;
    for (auto i : edges) {
        if (dist[i.s.f] + dist2[i.s.s] + i.f == dist[n]) {
            adj2[i.s.f].emplace_back(i.s.s, i.f);
            dbg(i.s.f, i.s.s);
            in_thing[i.s.f] = 1;
            in_thing[i.s.s] = 1;
        }
        if (dist[i.s.s] + dist2[i.s.f] + i.f == dist[n]) {
            adj2[i.s.s].emplace_back(i.s.f, i.f);
            dbg(i.s.s, i.s.f);
            in_thing[i.s.f] = 1;
            in_thing[i.s.s] = 1;
        }
    }
    // now we have dag
    topsort();
    dbg(ans);
    int jump_to = -1;

    vector<int> loc(n+3, 0);
    for (int i = 0; i < ans.size(); i++) {
        loc[ans[i]] = i;
    }

    vector<pii> answers;
    vector<int> answ;

    for (int i = 0; i < ans.size(); i++) {
        for (auto w : adj2[ans[i]]) {
            if (loc[w.f] != i+1)
                jump_to = max(jump_to, loc[w.f]);
        }
        if (i < ans.size()-1 and jump_to <= i) {
            answers.emplace_back(ans[i], ans[i+1]);
            int a = ans[i], b = ans[i+1];
            answ.push_back(wq[min(a, b)][max(a, b)]);
            good[answ.back()] = 1;
            dbg(ans[i], ans[i+1]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (good[i]) cout << "Yes\n";
        else cout << "No\n";
    }

}
