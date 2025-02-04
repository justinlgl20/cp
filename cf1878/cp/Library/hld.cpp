
template<typename T>
struct segtree {
    int tl, tr;
    T data;
    segtree *l, *r
    segtree(int tl, int tr) {
        this->tl = tl;
        this->tr = tr;
        if (tl == tr) return;
        int tm = (tl+tr)/2;
        l = new segtree(tl, tm);
        r = new segtree(tm+1, tr);
        data = (l->data).merge(r->data);
    }
    void push() {
        (l->data).lazy(data);
        (r->data).lazy(data);
        data.wipe_lazy();
    }
    int range_query(int ql, int qr) {}
    template<typename V>
    int range_update(int ql, int qr, V val) {}
};

//vertice based hld
template<class T, int V>
class HLD {
    int parent[V], heavy[V], depth[V], root[V], pos[V];
    segtree<T> seg(0, V+2);
    
    template<class G> 
    int dfs(const G& adj, int v) {
        int sz = 1; int maxsub = 0;
        for (int u : adj[v]) {
            if (u != parent[v]) {
                parent[u] = v;
                depth[u] = depth[v]+1;
                int st = dfs(adj, u);
                if (st > maxsub) heavy[v]=u,maxsub=st;
                sz += st;
            }
        }
        return sz;
    }
    template <class Operation>
    void do_path(int u, int v, Operation op) {
        for (; root[u] != root[v]; v = parent[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(pos[root[v]], pos[v]+1);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v]+1);
    }
    
    template<class G>
    void init(int n, const G& adj, int root) {
        fill_n(heavy, n, -1);
        parent[root] = -1;
        depth[root] = 0;
        dfs(graph, root);
        for (int i = 0, inx = 0; i < n; i++) 
            if (parent[i] == -1 || heavy[parent[i]] != i) 
                for (int j = i; j != -1; j = heavy[j]) {
                    root[j] = i;
                    pos[j] = inx++;
                }
    }
    void modify(int u, int v, int val) {
        do_path(u, v, [this, &val](int l, int r) { seg.range_update(l, r, val) });
    }
    T query(int u, int v) {
        T res = T();
        do_path(u, v, [this, &res](int l, int r) { res = res.merge(tree.query(l, r)); });
        return res;
    }
}
