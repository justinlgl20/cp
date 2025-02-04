#include <bits/stdc++.h>
using namespace std;

int par[105];
vector<int> adj[106];
int depth[105];
int edge[105];
int m;

void dfs(int u, int p) {
	depth[u] = depth[p]+1;
	m = max(m, depth[u]);
	for (int i : adj[u]) {
		if (i != p) {
			dfs(i, u);
		}
	}
}

map<int, int> encode;
map<int, int> decode;

int main() {
	cout << std::flush;
	int n; cin >> n;
	for (int i = 2; i <= n; i++) {
		cin >> par[i];
		adj[i].push_back(par[i]);
		adj[par[i]].push_back(i);
	}
	depth[1] = 0;
	m = 0;
	par[1] = 0;
	depth[0] = -1;
	dfs(1, 0);
    bool bipartite = true;
    for (int i = 2; i <= n; i++) {
        if (adj[i].size() == 2) {
            for (int j : adj[i]) edge[j] = (j == i);
        }
        else edge[i] = max(edge[i], -1);
    }
    vector<int> seen(n+1, false);
    function<void(int, int)> d = [&](int u, int p) {
        if (u == 1) return;
    }
    if (m == 1) {
        cout << 1 << "\n";
        for (int i = 1; i <= n; i++) cout << 1 << " \n"[i==n];
        while (true) {
            int x; cin >> x;
            if (x != 0) return 0;
            cin >> x;
            cout << 1 << "\n";
        }
    }
}
