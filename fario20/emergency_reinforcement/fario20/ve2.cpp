#include <bits/stdc++.h>
using namespace std;
 
struct bridge {
int u, v, comp, cost, id;
bridge(int a, int b, int c, int d, int e) : u(a), v(b), comp(c), cost(d), id(e) {}
bool operator < (const bridge other) const {
    return id < other.id;
}
bool operator == (const bridge other) const {
    return id == other.id;
}
};
 
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
void __print(bridge x) {cerr << x.id;}
 
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
 
 
 
 
struct dsu {
    vector<int> par;
    dsu(int n) {
        par.resize(n+2);
        for (int i = 0; i <= n; i++) par[i] = i;
    }
    int rep(int u) {
        if (par[u] == u) return u;
        return par[u] = rep(par[u]);
    }
    void merge(int a, int b) {
        a= rep(a); b = rep(b);
        par[a] = b;
    }
};
 
bool on[100005];
int company_costs[10005];
set<bridge> company_edges[10005];
set<bridge> company_off[10005];
 
template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}
 
double t;
long double a;
 
double P(int ol, int ne) {
    if (ne >= ol) return 1.0;
    return 0.0;
    return exp((double)(ne-ol)/(double)t);
}
 
int main() {
    t = 100000000;
    a = 0.99999;
    auto start = std::chrono::steady_clock::now();
    int n, e, k, x;
    cin >> n >> e >> k >> x;
    vector<bridge> bridges;
    for (int i = 1; i <= e; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        bridges.push_back(bridge(a, b, c, d, i));
    }
    dsu uf = dsu(n);
    sort(bridges.begin(), bridges.end());
    vector<bridge> use;
    vector<bridge> dont;
    for (auto i : bridges) {
        if (uf.rep(i.u) != uf.rep(i.v) and company_costs[i.comp]+i.cost <= x) {
            on[i.id] = true;
            company_costs[i.comp] += i.cost;
            uf.merge(i.u, i.v);
            //company_edges[i.comp].insert(i);
            use.push_back(i);
        } else {
            dont.push_back(i);
        }
    }
    //cerr << use.size() << " " << dont.size() << "\n";
    srand(69);
    vector<bridge> best = use;
    int iter = 0;
    /*for (int i = 0; i < 5; i ++) {
        dbg(i);
        dbg(use, dont);*/
    while (best.size() != n-1) {
        t = t*a;
        vector<int> company(k+2, 0);
        vector<bridge> use1 = use;
        set<bridge> dont1;
        for (auto i : dont) dont1.insert(i);
        vector<bridge> q;
        int hg = rand()%50+5;
        for (int i = 0; i < hg&&use1.size() >= 2; i++) { 
            int g = rand()%(use1.size());
            bridge er = use1[g];
            use1[g] = use1[use1.size()-1];
            q.push_back(er);
            use1.pop_back();
            dbg("POP");
        }
        dbg(use1);
        dbg(q);dbg(dont1);
        dsu g = dsu(n);
        for (auto i : use1) {
            company[i.comp] += i.cost;
            g.merge(i.u, i.v);
        }
        for (auto i : q) dont1.insert(i);
        vector<bridge> dont2;
        for (auto i : dont1) dont2.push_back(i);
        dbg(use1);
        dbg(dont1);
        random_shuffle(dont2.begin(), dont2.end());
        int add = 0;
        int to_add = rand()%50+5;
        for (auto i : dont2) {
            if (g.rep(i.u) != g.rep(i.v) and company[i.comp]+i.cost <= x) {
                company[i.comp] += i.cost;
                g.merge(i.u, i.v);
                //company_edges[i.comp].insert(i);
                use1.push_back(i);
                dont1.erase(i);
                add++;
                if (add == to_add) break;
            } 
        }
        if (use1.size() > best.size()) best = use1;
        
        if (P(use.size(), use1.size())*1e9 >= rand()%1000000000) {
            use = use1;
            dont = {};
            for (auto i : dont1) dont.push_back(i);
        }
        dbg(use);
        dbg(dont);
        dbg("REMOVED:", q);
        dbg(t, a);
        if (iter%100 == 0)
            cerr << t << ": " << n-best.size() << "\n";;
        iter++;
        //cerr << (use.size()+dont.size()) << "\n";
        //assert(use.size()+dont.size() == e);
    }
    cerr << n - best.size() << "\n";
    for (int i = 0; i < best.size(); i++) {
        cout << best[i].id << " \n"[i==best.size()-1];
    }
}
