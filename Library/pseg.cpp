struct persistent_segtree
{
    struct node
    {
        int val;
        int inx;
        int tl, tr;
        int l, r;
    };
    vector<node> nodes;
    vector<int> roots;
    int _build(int sz, int tl = 0, int tr = n)
    {
        if (tl == tr)
        {
            nodes.push_back(node{0, (int)nodes.size(), tl, tr, -1, -1});
            return (int)nodes.size() - 1;
        }
        int mid = (tl + tr) / 2;
        nodes.push_back(node{0, (int)(int)nodes.size(), tl, tr, _build(sz, tl, mid), _build(sz, mid + 1, tr)});
        return (int)nodes.size() - 1;
    }
    int copy_tree(int old)
    {
        nodes.push_back({nodes[old].val, (int)nodes.size(), nodes[old].tl, nodes[old].tr, nodes[old].l, nodes[old].r});
        return (int)nodes.size() - 1;
    }
 
    void __upd(int cur, int pos, int val, int tl = 0, int tr = n)
    {
        if (tl == tr)
        {
            nodes[cur].val = val;
            return;
        }
        int mid = (tl + tr) / 2;
        if (pos <= mid)
        {
            nodes[cur].l = copy_tree(nodes[cur].l);
            __upd(nodes[cur].l, pos, val, tl, mid);
        }
        else
        {
            nodes[cur].r = copy_tree(nodes[cur].r);
            __upd(nodes[cur].r, pos, val, mid + 1, tr);
        }
        nodes[cur].val = nodes[nodes[cur].l].val + nodes[nodes[cur].r].val;
    }
 
    int _upd(int old, int pos, int val, int tl = 0, int tr = n)
    {
        int cur = copy_tree(old);
        if (tl == tr)
        {
            nodes[cur].val = val;
            return cur;
        }
        // int mid = (tl + tr) / 2;
        __upd(cur, pos, val, tl, tr);
        nodes[cur].val = nodes[nodes[cur].l].val + nodes[nodes[cur].r].val;
 
        return cur;
    }
    int _qry(int cur, int l, int r, int tl = 0, int tr = n)
    {
        if (l > r)
        {
            return 0;
        }
        if (l == tl && r == tr)
        {
            return nodes[cur].val;
        }
        int mid = (tl + tr) / 2;
        int leftq = _qry(nodes[cur].l, l, min(r, mid), tl, mid);
        int rightq = _qry(nodes[cur].r, max(l, mid + 1), r, mid + 1, tr);
        return leftq + rightq;
    }
    void init(int sz)
    {
        nodes.clear();
        roots.clear();
        n = sz;
        roots.push_back(_build(sz));
        // cerr << "root is " << roots[0] << endl;
        // cerr << nodes.size() << endl;
    }
    void update(int pos, int val, int t)
    {
        roots.push_back(_upd(roots[t], pos, val));
    }
    int query(int l, int r, int t)
    {
        return _qry(roots[t], l, r);
    }
};
