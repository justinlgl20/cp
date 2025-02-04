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


#define f first
#define s second


struct dsu {
    vector<int> par;
    vector<int> smoll;
    vector<double> sz;
    vector<double> idk;
    struct comp {
        bool operator() (pair<double, int> a, pair<double, int> b)  const {
            return a.f > b.f;
        }
    };
    set<pair<double, int>, comp> comps;
    dsu(int n, vector<double> &a) {
        par.resize(n+2);
        sz.resize(n+2);
        idk.resize(n+2);
        for (int i = 1; i <= n; i++) { par[i] = i; comps.insert({a[i]/i, i}); sz[i] = a[i]; idk[i] = a[i]; }
    }
    void merge(int u, int v) {
        u = rep(u); v = rep(v);
        if (u > v) swap(u, v);
        comps.erase({sz[v]/v, v});
        comps.erase({sz[u]/u, u});
        par[v] = u; //rep is always smaller
        sz[u] += sz[v];
        idk[u] += idk[v];
        comps.insert({sz[u]/u, u});
    }
    int rep(int a) {
        if (par[a] == a) return a;
        return par[a] = rep(par[a]);
    }
};

void solve() {
    int n;double c; cin >> n >> c;
    vector<double> a(n+2, 0);
    for (int i =1 ; i <= n; i++) {cin >> a[i]; a[i] = a[i]/c; }
    dsu x = dsu(n, a);
    while (x.comps.size() > 1) {
        int fir = (*(x.comps.begin())).s;
        int sec = ((*(++x.comps.begin()))).s;
        dbg(fir, sec);
        dbg(x.sz[fir], x.sz[sec]);
        if (fir*sec <= x.sz[fir]+x.sz[sec]) x.merge(fir, sec);
        else {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";

}

int main() {
    int t; cin >> t;
    while (t--) solve();
}
