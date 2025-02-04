struct SCC {
    int n; 
    vector<vector<int>> adj, radj;
    vector<int> todo, seen, comp, comps; // comps is topologically sorted
    void init(int _n) { 
        n = _n; 
        adj = radj = vector<vector<int>>(n);
        comp.resize(n, -1);
        seen.resize(n); 
    }
    void ae(int u, int v) { adj[u].push_back(v), radj[v].push_back(u); }
    void dfs(int u) {
        if (seen[u]++) return;
        for (int v : adj[u]) dfs(v); 
        todo.push_back(u);
    }
    void rdfs(int u, int w) {
        comp[u] = w;
        for (int v : radj[u]) if (comp[v] == -1) rdfs(v, w); 
    }
    void gen() {
        for(int i=0;i<n;i++) dfs(i);
        reverse(all(todo));
        for (int u : todo) if (comp[u] == -1) rdfs(u, u), comps.push_back(u);
    }
};
