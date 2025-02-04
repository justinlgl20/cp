#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int n;

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
        // cerr << nodes.size() << ": " << tl << " " << tr << "\n";
        if (tl == tr)
        {
            nodes.push_back(node{0, (int)nodes.size(), tl, tr, -1, -1});
            return (int)nodes.size() - 1;
        }
        int mid = (tl + tr) / 2;
        nodes.push_back(node{0, (int)(int)nodes.size(), tl, tr, _build(sz, tl, mid), _build(sz, mid + 1, tr)});
        // cerr << "node " << nodes.back().inx << " has children " << nodes.back().l << " and " << nodes.back().r << endl;
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

int x[500005];
int y[500005];

int32_t main() {
    int q; cin >> n >> q;
    vector<pii> points;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        points.emplace_back(x[i], y[i]);
    }
    int last = 0;
    for (int i = 0; i < q; i++) {
        char q; cin >> q;
        if (q == 'Q') {
            int l, r; cin >> l >> r;
            l^=last;
            r^=last;
            int ans = 1e9;
            for (int i = 0; i < n; i++) {
                if (l <= x[i] and x[i] <= r and l <= y[i] and y[i] <= r) {
                    ans = min(ans, x[i]-y[i]);
                }
            }
            if (ans == 1e9) ans = 0;
            cout << ans << "\n";
            last = ans;
        } else {
            int i, x, y; cin >> i >> x >> y;
            i^=last;
            x^=last;
            y^=last;
            i--;
            ::x[i] = x;
            ::y[i] = y;
        }
    }
}
