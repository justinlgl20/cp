#include "factories.h"
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define pii pair<int, int>
#define f first
#define s second

int N;
vector<pii> adj[500005];
int depth[500005];
int tin[500005]; // pos of thing
int tout[500005]; // exclude that
int hop[500005][25];
int cnt;
void dfs(int u, int p) {
    hop[u][0] = p;
    for (int i = 1; i <= 23; i++) hop[u][i] = hop[hop[u][i-1]][i-1];
    tin[u] = ++cnt;
    for (auto i : adj[u]) {
        if (i.f != p) {
            depth[i.f] = depth[u] + i.s;
            dfs(i.f, u);
        }
    }
    tout[u] = ++cnt;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    int g = u;
    for (int i = 22; i >= 0; i--) {
        if (!is_ancestor(hop[g][i], v)) g = hop[g][i];
    }
    return hop[g][0];
}

int dist(int u, int v) {
    return depth[u]+depth[v]-((int)2)*depth[lca(u, v)];
}

void Init(int32_t N, int32_t A[], int32_t B[], int32_t D[]) {
    ::N = N;
    for (int i = 0; i < N; i++) {
        adj[A[i]+1].emplace_back(B[i]+1, D[i]);
        adj[B[i]+1].emplace_back(A[i]+1, D[i]);
    }

    dfs(1, 0);
}

long long Query(int32_t S, int32_t X[], int32_t T, int32_t Y[]) {
    vector<int> seen(N+2, false);
    vector<int> dist(N+2, 1e18);
    vector<int> goal(N+2, false);
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < S; i++) {
        dist[X[i]+1] = 0;
        q.push(make_pair(0, X[i]+1));
    }
    for (int i = 0; i < T; i++) goal[Y[i]+1] = true;
    while (q.size()) {
        int t = q.top().s;
        int d = -q.top().f;
        q.pop();
     
        if (goal[t]) return d;
        if (seen[t]) continue;
        //if (d > dist[t]) continue;
        assert(!seen[t]);
        dist[t] = d;
        seen[t] = true;
        for (auto i : adj[t]) {
            if (dist[t]+i.s < dist[i.f]) {
                dist[i.f] = dist[t]+i.s;
                q.push(make_pair(-dist[i.f], i.f));
            }
        }
    }
    return -1e18;
}