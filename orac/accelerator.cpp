#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
vector<int> go;
vector<vector<int>> adj;

vector<int> find_cycle(int start, vector<vector<int>>adj, int N) {
        vector<int> cycle;
        stack<pair<int, int>> q;
        vector<int> seen(N+5); // 0 is not explored, 1 is being explored, 2 is fully explored
        vector<int> par(N+5);
        for (int i = 0; i <= N; i++) seen[i] = 0,par[i] = 0;
        vector<int> last(N+5);
        q.push(make_pair(start, 0));
        vector<bool> is_in_cycle(N+5, 0);
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

struct pseudotree {
    int N;
    vector<vector<int>> adj;
    vector<int> is_in;
    struct tree {
        int root;
        unordered_map<int, unordered_map<int, int>> hop;
        unordered_map<int, int> depth;
        void dfs(int u, pair<int, int> p) {
            is_in[u]= root;
            depth[u] = depth[p.first]+1;
            hop[u][0] = p.first;
            for (int i = 1; i < 20; i++) {
                hop[u][i] = hop[hop[u][i-1]][i-1];
            }
            for (int i : adj[u]) {
                if (i != p.first and i != p.second) dfs(i, {u, u});
            }
        }
        tree(int root, pair<int, int> ignore) {
            this->root = root;
            dfs(root, ignore);
        }
        tree() {}
    };
    vector<tree> trees;
    pseudotree(vector<vector<int>> &adj, int N, vector<int> directed) {
        this->adj = adj;
        is_in.resize(N+2);
        vector<int> g = find_cycle(1, adj, N);
        for (int i = 0; i <= g.size(); i++) {
            trees.push_back(tree(g[i], {g[(i-1+N)%N], g[(i+1)%N]}));
        }
        if (directed.empty()) return;
        if (directed[g[0]] == g[1]) return;
        reverse(directed.front(), directed.back());
    }
}

int main() {
    cin >> N >> M >> Q;
    adj.resize(N+2);
    radj.resize(N+2);
    go.resize(N);
}
