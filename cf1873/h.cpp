#include <bits/stdc++.h>
using namespace std;

bool is_in_cycle[20005];

vector<int> find_cycle(int start, vector<vector<int>> &adj, int N) {
        vector<int> cycle;
        stack<pair<int, int>> q;
        vector<int> seen(N+5); // 0 is not explored, 1 is being explored, 2 is fully explored
        vector<int> par(N+5);
        for (int i = 0; i <= N; i++) seen[i] = 0,par[i] = 0;
        vector<int> last(N+5);
        q.push(make_pair(start, 0));
        bool kill = false;
        while (!q.empty()) {
                int cur = q.top().first;
                int prev = q.top().second;
                q.pop();
 
                if (seen[cur]) continue;
                seen[cur] = true;
                last[cur] = prev;
                for (auto i : adj[cur]) {
                        q.push({i, cur});
                        if (i != last[cur] and seen[i])
                        {
                                last[i] = cur;
                                int cur2 = cur;
                                cycle.push_back(i);
                                is_in_cycle[i] = true;
                                while (cur2 != i) {
                                        cycle.push_back(cur2);
                                        is_in_cycle[cur2] = true;
                                        cur2 = last[cur2];
                                        if (is_in_cycle[cur2]) break;
                                }
 
                                if (!is_in_cycle[cur2]) {
                                        cycle.push_back(cur2);
                                        is_in_cycle[cur2] = true;
                                }
                                kill = true;
                                break;
                        }
                }
                if (kill == true) break;
        }
        return cycle;
}

int hop[20005][30];
void solve() {
    int n, a, b;
    vector<vector<int>> adj(n+1, vector<int>());
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto c = find_cycle(1);
    for (int i : c) {
        for 
    }
}
