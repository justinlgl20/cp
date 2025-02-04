#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, q;
bool active[100001];
vector<int> graph[100001];
pair<int, int> edges[200001];

int info[100001], last_sync[100001];

// DFS order
int timer = 1, tin[100001], tout[100001];
// Binary lifting parents
int anc[100001][20];

void dfs(int node = 1, int parent = 0) {
    anc[node][0] = parent;
    for (int i = 1; i < 20 && anc[node][i - 1]; i++) {
        anc[node][i] = anc[anc[node][i - 1]][i - 1];
    }

    info[node] = 1;

    tin[node] = timer++;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
    tout[node] = timer;
}

// Fenwick tree
int bit[100001];

void update(int pos, int val) { for (; pos <= n; pos += (pos & (-pos))) bit[pos] += val; }

int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

// Binary lifting
int find_ancestor(int node) {
    int lca = node;
    for (int i = 19; ~i; i--) {
        if (anc[lca][i] && query(tin[anc[lca][i]]) == query(tin[node])) lca = anc[lca][i];
    }
    return lca;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m >> q;
    FOR(i, 1, n) {
        cin >> edges[i].first >> edges[i].second;
        graph[edges[i].first].push_back(edges[i].second);
        graph[edges[i].second].push_back(edges[i].first);
    }
    dfs();

    FOR(i, 1, n + 1) {
        update(tin[i], -1);
        update(tout[i], 1);
    }

    while (m--) {
        int x;
        cin >> x;
        int u = edges[x].first, v = edges[x].second;
        if (anc[u][0] == v) swap(u, v);

        if (active[x]) {
            info[v] = last_sync[v] = info[find_ancestor(u)];
            update(tin[v], -1);
            update(tout[v], 1);
        } else {
            info[find_ancestor(u)] += info[v] - last_sync[v];
            update(tin[v], 1);
            update(tout[v], -1);
        }
        active[x] = !active[x];
    }

    while (q--) {
        int x;
        cin >> x;
        cout << info[find_ancestor(x)] << '\n';
    }
    return 0;
}
