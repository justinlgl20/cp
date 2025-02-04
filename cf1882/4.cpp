#include <bits/stdc++.h>
using namespace std;

#define int long long

int root;
int subtree_sz[200005];
int a[200005];
int n;
vector<int> adj[200005];
int min_cost[200005];
int ans[200005];

void dfs(int u, int p) {
    subtree_sz[u] = 1;
    min_cost[u] = 0;
    for (auto i : adj[u]) {
        if (i != p) {
            dfs(i, u);
            subtree_sz[u] += subtree_sz[i];
            min_cost[u] += min_cost[i]+(int)(a[i]^a[u])*subtree_sz[i];
        }
    }
}

void shift_root(int from, int to) {
    /*subtree_sz[from] = 1;
    min_cost[from] = 0;
    for (auto i : adj[from]) {
        if (i != to) {
            subtree_sz[from] += subtree_sz[i];
            min_cost[from] += min_cost[i]+(int)(a[i]^a[from])*subtree_sz[i];
        }
    }*/
    subtree_sz[from] -= subtree_sz[to];
    min_cost[from] -= min_cost[to]+(int)(a[to]^a[from])*subtree_sz[to];
    /*subtree_sz[to] = 0;
    min_cost[to] = 0;
    for (auto i : adj[to]) {
        subtree_sz[to] += subtree_sz[i];
        min_cost[to] += min_cost[i]+(int)(a[i]^a[to])*subtree_sz[i];
    }*/
    subtree_sz[to] += subtree_sz[from];
    min_cost[to] += min_cost[from]+(int)(a[from]^a[to])*subtree_sz[from];
    ans[to] = min_cost[to];
    root = to;
    //cerr << root << ": \n";

    //for (int i = 1; i <= n; i++) cerr << min_cost[i] << "nbfds\n";
}

void solve() {
    root = 1;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        adj[i].clear();
        ans[i] = 0;
        subtree_sz[i] = 0;
        min_cost[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    ans[1] = min_cost[1];
    function<void(int, int)> d = [&](int u, int p) -> void {
        for (auto i : adj[u]) {
            if (i != p) {
                shift_root(u, i);
                d(i, u);
                shift_root(i, u);
            }
        }
    };
    d(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i==n];
}


int32_t main() {
    int t; cin >> t;
    while (t--)
        solve();
}

