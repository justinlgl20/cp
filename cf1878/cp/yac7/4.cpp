#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

set<pair<int, int>> nodes;
int degree[200005];
int par[200005];
set<int> adj[200005];

int memo[200005][60];
int N;
int depth[200005];
void dfs(int u, int p)
{
    memo[u][0] = p;
    for (int i = 1; i <= log2(N)+1; i++)
        memo[u][i] = memo[memo[u][i - 1]][i - 1];
    for (int v : adj[u])
    {
        if (v != p)
        {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int killed[200005];

int main() {
	int M; cin >> N >> M;
	for (int i = 0; i < N-1; i++) {
		int a, b; cin >> a >> b;
		degree[a]++;
		degree[b]++;
		adj[a].insert(b);
		adj[b].insert(a);
	}
	dfs(1, 0);
	for (int i = 1; i <= N; i++) nodes.insert(make_pair(degree[i], i));
	for (int i = 1; i <= M; i++) {
		int a; cin >> a;
		int e = a;
		if (killed[e]) {
			int prev = e;
			while (killed[e]) {
				for (int i = 1; i <= log2(N+1); i++) if (killed[memo[e][i]]) e = memo[e][i];
				if (e == prev) break;
			}
			killed[e] = false;
			nodes.insert(make_pair(1, e));
		
		}
		set<pair<int, int>>::iterator itr;
		auto x = nodes.lower_bound(make_pair(1, 0));
		vector<pair<int, int>> to_rm;
		for (itr = nodes.begin(); itr != nodes.end(); itr++) {
			if ((*itr).f > 1) break;
			to_rm.push_back(*itr);
			cerr << "TO_REMOVE: " << (*itr).f << " " << (*itr).s << "\n";
		}
		for (auto i : to_rm){
			if (i.s != a) {
				nodes.erase(i);
				killed[i.s] = true;
				cerr << "REMOVED: " << i.f <<" " << i.s << "\n";
				for (auto j : adj[i.s]) {
					adj[j].erase(i.s);
				}
				int u = i.s;
				for (auto v : adj[u])
				{
					nodes.erase(make_pair(degree[v], v));
					degree[v]--;
					cerr << "EDITED: " << v << "\n";
					nodes.insert(make_pair(degree[v], v));
				}
			}
		}
		cout << nodes.size() << "\n";
	}
}

