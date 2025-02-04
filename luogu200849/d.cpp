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

struct node {
    vector<int> l;
};

vector<pii> values[200005];

node tree[800004];
void build(int n = 1, int tl=0, int tr=200005) {
    if (tl == tr) {
        for (auto i : values[tl]) {
            dbg(tl, i.s);
            tree[n].l.push_back(i.s);
        }
        return;
    }
    int tm = (tl+tr)>>1;
    build(n*2, tl, tm);
    build(n*2+1, tm+1, tr);
    // now i need to merge stuff :(((((
    tree[n].l = tree[n*2].l;
    for (auto i : tree[n*2+1].l) {
        tree[n].l.push_back(i);    
    }
    sort(all(tree[n].l));
}

int query(int l, int r, int x, int n = 1, int tl = 0, int tr = 200005) {
    if (l > tr) return 0;
    if (r < tl) return 0;
    if (l <= tl and tr <= r) {
        // find number of things in t[n].l bigger or equal to x
        // bserach on tree[n].l
        int q = tree[n].l.size();
        for (int i = 20; i >= 0; i--) {
            if (q-(1ll<<i) >= 0 and tree[n].l[q-(1ll<<i)] >= x) {
                q -= (1ll<<i);
            }
        }
        int ans = tree[n].l.size() - (q);
        dbg(tl, tr, q, tree[n].l, ans, x);
        // q+1 is first index of thing that works
        return tree[n].l.size() - (q);

    }
    int tm = (tl+tr)>>1;
    return query(l, r, x, n*2, tl, tm) + query(l, r, x, n*2+1, tm+1, tr);
}

vector<int> adj[200005];
vector<int> push[200005];
int n, m, k, q; 

vector<int> topsort() {
    vector<int> ans;
    vector<int> visited(n+4, 0);    
    function<void(int)> dfs = [&](int u) {
        visited[u] = 1;
        for (auto i : adj[u]) {
            if (!visited[i]) dfs(i);
        }
        ans.push_back(u);
    };
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
    }
    reverse(all(ans));
    return ans;
}

const int SQRT = 450;

bool can_go[200005];
vector<int> stuff[200005];

int32_t main() {
    int c; cin >> c;
    cin >> n >> m >> k >> q;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        if (v == 1) {
            can_go[u] = 1;
        }
    }
    vector<int> order = topsort();
    dbg(order);
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    vector<int> special(n+4, 0);
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() >= SQRT) {
            special[i] = true;
            for (auto j : adj[i]) {
                push[j].push_back(i);
            }
        }
    }
    vector<int> range(k, -1); // range[i] to i is minimum range for i to go
    // FOR ALL THE SQRT M  NODES WHICH HAVE MORE THAN SQRT M OUTGOING, EVERY TIME DO THEM
    // WORKS FOR C AND D WITHOUT THOSE, JUST LIKE SAVE THE ANSWERS FOR THOSE CONSTANTLY
    vector<int> last(n+3, -1);
    vector<int> ans(n+3, -1);
    for (int i = 0; i < k; i++) {
        last[1] = i;
        // if a[i] can go straight to 1 its range is i, i
        if (can_go[a[i]]) {
            range[i] = i;
        }
        if (special[a[i]]) {
            range[i] = max(range[i], ans[a[i]]);
        } else {
            for (auto u : adj[a[i]]) {
                range[i] = max(range[i], last[u]);
            }
        }
        last[a[i]] = range[i];
        for (auto u : push[a[i]]) {
            ans[u] = max(ans[u], range[i]);
        }
        dbg(i, a[i], range[i]);
    }
    for (int i = 0; i < k; i++) {
        if (range[i] > -1) {
            int l= range[i], r=i;
            values[r].push_back({a[i], l});
            stuff[l].push_back(a[i]);
        }
    }

    if (1 <= c and c <= 8) {
        for (int i = 0; i < q; i++) {
            int l, r; cin >> l >> r; l--, r--;
            set<int> ans;
            for (int i = 0; i < k; i++) {
                if (l <= range[i] and i <= r) {
                    ans.insert(a[i]);
                }
            }
            cout << n-1-ans.size() << "\n";
        }
    }

    // at most sqrt k have more than sqrt k ranges

    if (c == 12 or c == 13 or c == 14 or c == 15) { // all elements of a are unique could've just gone throuhg all adj instead of sqrt.
        build();

        for (int i = 0; i < q; i++) {
            int l, r; cin >> l >> r;
            l--, r--;
            cout << n-1-query(0, r, l)<<"\n";
        }
    }
    if (c == 16 or c == 17 or c == 20 or c == 21 or c == 22) {
        vector<int> ans(k+10);
        set<int> things;
        for (int i = k-1; i >= 0; i--) {
            for (auto j : stuff[i]) things.insert(j);
            ans[i] = things.size();
        }
        for (int i = 0; i < q; i++) {
            int l, r; cin >> l >> r;
            l--, r--;
            // r is always end
            cout << n-1-ans[l] << "\n";;
        }
    }
}
