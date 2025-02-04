#include <bits/stdc++.h>
using namespace std;
 
#define pii pair<int, int>
#define f first
#define s second
 
#define dbg(x...)
 
 
int n;
vector<pii> adj[10005];
int st[10005];
int en[10005];
vector<pii> gadj[100005];
int par[10005];
int value[10005];
int depth[10005];
int hop[10005][30];
 
bool is_ancestor(int u, int v) {
    return st[u] <= st[v] and en[u] >= en[v];
}
 
struct dsu {
    vector<int> p;
    dsu() {
        p.resize(n+2);
        for (int i = 0; i <= n; i++) p[i] = i;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a); b = rep(b);
        p[a] = b;
    }
};
void kruskal() {
    dsu x = dsu();
    vector<pair<int, pii>> edges;
    for (int i = 1; i <= n; i++) {
        for (auto j : gadj[i]) {
            edges.push_back({j.s, {j.f, i}});
        }
    }
    sort(edges.begin(), edges.end());
    for (auto i : edges) {
        if (x.rep(i.s.f) != x.rep(i.s.s)) {
            x.merge(i.s.f, i.s.s);
            adj[i.s.f].emplace_back(i.s.s, i.f);
            adj[i.s.s].emplace_back(i.s.f, i.f);
            //cerr << "MST: " << i.s.f << " " << i.s.s << "\n";
        }
    }
}
void dfs(int u, int p) {
    hop[u][0] = p;
    for (int i = 1; i < 20; i++) {
        hop[u][i] = hop[hop[u][i-1]][i-1];
    }
    for (auto i : adj[u]) {
        if (i.f != p) {
            value[i.f] = i.s;
            par[i.f] = u;
            depth[i.f] = depth[u]+1;
            dfs(i.f, u);
        }
    }
}
 
int timer = 1;
vector<int> arr; // stores indices. when considering range, ignore double ups. Ans is value[i] where i is the indice
void euler(int u, int p) {
    st[u] = timer++;
    arr.push_back(u);
    for (auto i : adj[u]) {
        if (i.f != p) euler(i.f, u);
    }
    en[u] = timer++;
    arr.push_back(u);
}
bool cmp(int a, int b) {
    if (value[a] == value[b]) return a < b;
    return value[a] < value[b];
}
//set<int, decltype(cmp)*> slow(cmp);
struct fast_thingy {
    int block_sz;
    vector<int> map_to_val;
    vector<int> arr;
    vector<int> unmap;
    struct block {
        int tl, tr;
        int active;
    };
    vector<block> blockes;
    vector<int> block_no;
    int last;
    fast_thingy() {
        dbg("START INIT");
        //for (int i = 0; i <= n+2; i++) arr.push_back(0);
        vector<int> sorted = {0};
        map_to_val.resize(n+2);
        unmap.resize(n+2);
        arr.resize(n+2);
        block_no.resize(n+2);
        for (int i = 1; i <= n; i++) sorted.push_back(i);
        sort(sorted.begin(), sorted.end(), cmp);
        for (int i = 1; i <= n; i++) {
            arr[i] = 0;
            map_to_val[sorted[i]] = i;
            unmap[i] = sorted[i];
        }
        block_sz = pow(n, 0.5);
        for (int i = 1; i <= n; i++) block_no[i] = (i-1)/block_sz;
        last = block_no[n];
        int inx = 1;
        for (int i = 0; i <= last and inx <= n; i++) {
            block x;
            x.tl = inx;
            while (block_no[inx] == i) inx++;
            x.tr = inx-1;
            x.active = 0;
            dbg(i, x.tl, x.tr);
            blockes.push_back(x);
        }
        dbg(map_to_val);
        dbg(unmap);
        dbg("END INIT");
    }
    void _insert(int i) {
        if (arr[i] == 1) return;
        arr[i] = 1;
        blockes[block_no[i]].active += 1;
        dbg(arr);
    }
    void _erase(int i) {
        if (arr[i] == 0) return;
        arr[i] = 0;
        blockes[block_no[i]].active -= 1;
    }
    int _biggest() {
        dbg("QUERY FOR BIGGEST");
        dbg(arr);
        //dbg(slow);
        for (int i = last; i >= 0; i--) {
            if (blockes[i].active == 0) continue;
            else {
                for (int j = blockes[i].tr; j >= blockes[i].tl; j--) {
                    if (arr[j]){
                        dbg("ANS: ", j);
                        return j;
                    }
                }
            }
        }
    }
    void insert(int i) {
        dbg("INSERT", i);
        _insert(map_to_val[i]);
        //slow.insert(i);
 
    }
    void erase(int i) {
        dbg("ERASE", i);
        _erase(map_to_val[i]);
        //slow.erase(i);
    }
    int biggest() {
        return unmap[_biggest()];
    }
};
 
unordered_map<int, unordered_map<int, int>> anses; // maps the queries on arr to their solution
// can probably use a deque instead of a set
int cnt[100005];
 
fast_thingy considering;
int l;
int r;
 
void rl() {
    cnt[arr[r]]--;
    if (cnt[arr[r]] == 1) considering.insert(arr[r]);
    if (cnt[arr[r]] == 0) considering.erase(arr[r]);
    r--;
}
void rr() {
    r++;
    cnt[arr[r]]++;
    if (cnt[arr[r]] == 2) considering.erase(arr[r]);
    if (cnt[arr[r]] == 1) considering.insert(arr[r]);
}
void lr() {
    cnt[arr[l]]--;
    if (cnt[arr[l]] == 0) considering.erase(arr[l]);
    if (cnt[arr[l]] == 1) considering.insert(arr[l]);
    l++;
}
void ll() {
    l--;
    cnt[arr[l]]++;
    if (cnt[arr[l]] == 1) considering.insert(arr[l]);
    if (cnt[arr[l]] == 2) considering.erase(arr[l]);
}
 
int32_t main() {
#ifndef DEBUG
    freopen("yourin.txt", "r", stdin);
    freopen("yourout.txt", "w", stdout);
#endif
    int e, q;
    cin >> n >> e >> q;
    for (int i = 0; i < e; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        gadj[a].emplace_back(b, w);
    }
    kruskal();
    depth[1] = 1;
    dfs(1, 0);
    euler(1, 0);
    dbg(arr);
    //for (int i : arr) cerr << value[i] << " ";
    //cerr << "\n";
    vector<pii> actual;
    vector<pii> queries;
    while (q--) {
        int u, v; cin >> u >> v;
        int ans = 0;
        if (st[u] > st[v]) swap(u, v);
        if (is_ancestor(u, v)) {
            int up = depth[v] - depth[u] - 1;// to go up from v
            u = v;
            for (int i = 0; i < 20; i++) {
                if ((1 << i)&up)u = hop[u][i];
            }
            queries.emplace_back(st[u]-1, st[v]-1); 
        } else {
            queries.emplace_back(en[u]-1, st[v]-1); // works because calls on all except for the lca
        }
        actual.emplace_back(u, v);
    }
    considering = fast_thingy();
    l = 0; r = 0;
    considering.insert(arr[0]);
    cnt[arr[0]] = 1;
    int sz = 180;
    sort(queries.begin(), queries.end(), [&](pii a, pii b) {
            if ((int)a.f/sz == (int)b.f/sz) return a.s < b.s;
            return (int)a.f/sz < (int)b.f/sz;
            });
    dbg(queries);
    for (auto i : queries) {
        while (l > i.f) ll();
        while (r < i.s) rr();
        while (l < i.f) lr();
        while (r > i.s) rl();
        dbg(i);
        //dbg(considering);
        //for (int i = 1; i <= n; i++) cerr << i << ": " << cnt[i] << "\n";
        anses[i.f+1][i.s+1] = value[considering.biggest()];
        dbg(l);dbg(r)
    }
    for (auto i : actual) {
        int ans;
        int u = i.f, v = i.s;
        if (is_ancestor(u, v)) ans = anses[st[u]][st[v]];
        else ans = anses[en[u]][st[v]];
        cout << ans << "\n";
    }
}