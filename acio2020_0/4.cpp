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


vector<int> adj[100005];

int32_t main() {
#ifndef DEBUG
    freopen("radin.txt", "r", stdin);
    freopen("radout.txt", "w", stdout);
#endif
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<int> band(n+2);
    vector<int> dist(n+2, 0);
    vector<bool> bad(n+2, 0);
    for (int i = 1; i <= n; i++) { cin >> band[i];}
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int lo = 0;
    int hi = 100000005;
    while (lo != hi-1) {
        int L = (lo+hi)/2;
        //L = 8;
        for (int i = 1; i <= n; i++) { bad[i] = band[i] < L; dist[i] = band[i] < L ? 100000005 : 0; }
        queue<int> q;
        q.push(1);
        bad[1] = true;
        while (q.size()) {
            int u = q.front();
            dbg(u, dist[u]);
            q.pop();
            for (int i : adj[u]) {
                if (!bad[i]) {
                    dist[i] = dist[u]+1;
                    bad[i] = true;
                    q.push(i);
                }
            }
        }
        int nodes = 0;
        for (int i = 1; i <= n; i++) if (bad[i]) nodes += dist[i] <= d;
        if (nodes >= k) lo = L;
        else hi = L;
    }
    cout << lo << "\n";
}
