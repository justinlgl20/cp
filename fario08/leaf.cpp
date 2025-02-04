#include <bits/stdc++.h>
using namespace std;


void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif


#define int long long
#define pii pair<int, int>
#define f first
#define s second


pii points[2005];
int dist(int i, int j) {
    return abs(points[i].f-points[j].f)+abs(points[i].s-points[j].s);
}

struct dsu {
    vector<int> par;
    dsu(int n) {
        par.resize(n+1500);
        for (int i = 0;i <= 3*n+1; i++) par[i] = i;
    }
    int rep(int u) {
        if (par[u] == u) return u;
        return par[u] = rep(par[u]);
    }
    void merge(int a, int b) {
        a = rep(a); b = rep(b);
        par[a] = b;
    }
};

int total = 0;
void to(int _i, int _j) {
    auto i = points[_i];
    auto j = points[_j];
    int g1 = i.f;
    int g2 = j.f;
    while (g1 > g2) {
        cout << g1 << " " << i.s << " " << g1-1 << " " << i.s << "\n";
        g1 -= 1;
        total++;
    }
    while (g1 < g2) {
        cout << g1 << " " << i.s << " " << g1+1 << " " << i.s << "\n";
        total++;
        g1 += 1;
    }
    g1 = i.s;
    g2 = j.s;
    while (g1 > g2) {
        cout << j.f << " " << g1 << " " << j.f << " " << g1-1 << "\n";
        total++;
        g1 -= 1;
    }
    while (g1 < g2) {
        cout << j.f << " " << g1 << " " << j.f << " " << g1+1 << "\n";
        total++;
        g1 += 1;
    }
}
int cnt = 0;
void go(int _i, int _j) {
    auto i = points[_i];
    auto j = points[_j];
    int g1 = i.f;
    int g2 = j.f;
    while (g1 > g2) {
        g1 -= 1;
        cnt++;
    }
    while (g1 < g2) {
        cnt++;
        g1 += 1;
    }
    g1 = i.s;
    g2 = j.s;
    while (g1 > g2) {
        cnt++;
        g1 -= 1;
    }
    while (g1 < g2) {
        cnt++;
        g1 += 1;
    }
}


int randint(int l, int h) {
    return rand()%(h-l+1)+l;
}

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int32_t main() {
    srand(69);
    auto start = std::chrono::steady_clock::now();
    int n; cin >> n;
    int boundx = 0;
    int boundy = 0;
    int smallx = 1e9;
    int smally = 1e9;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        boundx = max(x, boundx);
        boundy = max(boundy, y);
        smallx = min(x, smallx);
        smally = min(y, smally);
        points[i+1] = {x, y};
    }
    vector<vector<int>> best_adj(n+300, vector<int>());
    vector<pair<int, pii>> best_edges = {};
    vector<pii> stoof;
    pii point;
    int best_cost = 1e18;
    for (int _ = 0; since(start).count() <= 120000; _++)
    {   
        int added = rand()%(n/2)+n/5;
        added = min(rand()%(int)(n/15+1), (boundx-smallx)*(boundy-smally)/2);
        if (_ == 0)
            added = 0;
        set<pii> idkidk;
        for (int i = 1; i <= n; i++) idkidk.insert(points[i]);
        for (int i = n+1; i <= n+added; i++) {
            points[i] = {randint(smallx, boundx), randint(smally, boundy)};
            while (idkidk.find(points[i]) != idkidk.end()) points[i] = {randint(smallx, boundx), randint(smally, boundy)};
            idkidk.insert(points[i]);
            dbg(points[i]);
        }
        vector<pair<int, pii>> edges;
        for (int i = 1; i <= n+added; i++) {
            for (int j = 1; j <= n+added; j++) {
                edges.push_back({dist(i, j), {i, j}}); 
            }
        }
        dsu uf = dsu(n);
        sort(edges.begin(), edges.end());
        vector<pair<int, pii>> use;
        
        int cost = 0;
        for (auto i : edges) {
            if (uf.rep(i.s.f) != uf.rep(i.s.s)) { uf.merge(i.s.f, i.s.s); use.push_back(i); cost += i.f; }//dbg(i, points[i.s.f], points[i.s.s]);}
        }
        for (int i = 1; i <= n+added; i++) assert(uf.rep(i) == uf.rep(1));
        vector<vector<int>> adj(n+300, vector<int>());
        for (auto i : use) {
            adj[i.s.f].push_back(i.s.s);
            adj[i.s.s].push_back(i.s.f);
        }
        dbg(cost, use);
        if (cost < best_cost) {best_edges= use; best_cost = cost;stoof.clear(); for (int i = n+1; i <= n+added; i++) stoof.push_back(points[i]);}
    }
    dbg(best_edges);
    for (int i = 1; i <= stoof.size(); i++) {
        points[n+i] = stoof[i-1];
    }
    for (int i = 0; i <= n+2; i++) best_adj[i].clear();
    for (auto i : best_edges) {
        best_adj[i.s.s].push_back(i.s.f);
        best_adj[i.s.f].push_back(i.s.s);
    }
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto i : best_adj[u]) {
            if (i != p) {                
                dfs(i, u);
            }
        }
        for (auto i : best_adj[u]) {
            if (i != p) {
                to(i, u);
            }
        }
    };
    dfs(1, 0);
    cerr << best_cost << " " << total  <<"\n";
}
