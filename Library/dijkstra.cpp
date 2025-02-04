struct graph {
    vector<vector<pii>> adj;
    int n;
    graph(int n) {
        this->n = n;
        adj.resize(n+4);
        for(int i=0;i<n+3;i++)adj[i].clear();
    }
    void ae(int u, int v, int w) {
        adj[u].emplace_back(v,w);
    }
    vector<int> dikstra(int s) {
        vector<int> dist(n+4,1e18);
        dist[s]=0;
        priority_queue<pii> q;
        q.push(make_pair(0,s));
        while (q.size()) {
            int u=q.top().s;
            int w=-q.top().f;
            q.pop();
            if(w>dist[u])continue;
            for(auto i:adj[u]){
                if(i.s+dist[u] < dist[i.f]){
                    dist[i.f]=i.s+dist[u];
                    q.push(make_pair(-dist[i.f], i.f));
                }
            }
        }
        return dist;
    }
};