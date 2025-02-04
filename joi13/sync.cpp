#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

vector<int> adj[100005];

int n, m, q;
pii edges[200005];
int dat[100005];

int cnt;
int tin[100005];
int tout[100005];
int hop[100001][20];

void dfs(int u, int p) {
    hop[u][0] = p;
    for (int i = 1; i < 20 and hop[u][i-1]; i++) {
        hop[u][i] = hop[hop[u][i-1]][i-1];
    }
    dat[u] = 1;
    tin[u] = ++cnt;
    for (int i : adj[u]) {
        if (i != p) dfs(i, u);
    }
    tout[u] = cnt+1;
}



int last[100005];

int bit[100005];

void upd(int pos, int val) { for (; pos <= n; pos += (pos & (-pos))) bit[pos] += val; }

int query(int p) {
    int ans = 0;
    for (; p; p -= (p & (-p))) ans += bit[p];
    return ans;
}
int anc(int u) {
    int g = u;
    for (int i = 19; ~i; i--) {
        if (hop[g][i] and query(tin[hop[g][i]]) == query(tin[u])) g = hop[g][i];
    }
    return g;
}

int alive[100005];

int main() {
    cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        cin >> edges[i].f >> edges[i].s;
        adj[edges[i].f].push_back(edges[i].s);
        adj[edges[i].s].push_back(edges[i].f);
    }
    dfs(1, 0);

    cerr << "DBG\n";
    for (int i = 1; i < n+1; i++) {
        upd(tin[i], -1);
        upd(tout[i], 1);
    }
    cerr << "SUCCESS\n";
    while (m--) {
        int x; cin >> x;
        int u = edges[x].f;
        int v = edges[x].s;
        if (hop[u][0] == v) swap(u, v);
        
        if (alive[x]) {
            dat[v] = last[v] = dat[anc(u)];
            cerr << anc(u) << " " << last[v] << "\n";
            upd(tin[v], -1);
            upd(tout[v], 1);
        }
        else {
            dat[anc(u)] += dat[v]-last[v];
            cerr << anc(u) << "\n";
            upd(tin[v], 1);
            upd(tout[v], -1);
        }
        alive[x] = not alive[x];
    }
    while (q--) {
        int x; cin >> x;
        cout << dat[anc(x)] << "\n";
    }
}
