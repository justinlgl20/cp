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

map<int, int> *length[200005]; // [i][j] is min no. of paths needed to achieve j so top end is on i
int depth[200005];
int edepth[200005];
int sz[200005];
vector<pii> adj[200005];
void dfs(int u, int p) {
    //dbg(u, p);
    sz[u] = 1;
    if (u != 0)
        edepth[u] = edepth[p]+1;
    for (auto i : adj[u]) {
        if (i.f != p) {
            depth[i.f] = depth[u]+i.s;
            dfs(i.f, u);
            sz[u] += sz[i.f];
        }
    }
}

int K;
int ans;

void solve(int u, int p) {
    int big = -1, v = -1;
    for (auto a : adj[u]) {
        int i = a.f;
        if (i != p) {
            solve(i, u);
            if (sz[i] > big) {
                big = sz[i];
                v = i;
            }
        }
    }
    dbg(u);
    if (big != -1) length[u] = length[v];
    else length[u] = new map<int, int>();
    if ((*length[u]).count(depth[u]))
        (*length[u])[depth[u]] = min((*length[u])[depth[u]], edepth[u]);
    else 
        (*length[u])[depth[u]] = edepth[u];
    dbg(*length[u]);
    for (auto a : adj[u]) {
        int i = a.f;
        int l = a.s;
        if (i != p and i != v) {
            for  (auto x : *length[i]) {
                // x.f-depth[u] is length of path
                // x.s is no. of edges
                dbg(x,  K-(x.f-depth[u])+depth[u]);
                if ((*length[u]).count(K - (x.f - depth[u]) + depth[u])) {
                    ans = min(ans, ((*length[u])[K-(x.f-depth[u])+depth[u]]) + x.s - 2*edepth[u]);
                }
            }
            for (auto x : *length[i]) {
                if ((*length[u]).count(x.f)) {
                    (*length[u])[x.f] = min((*length[u])[x.f], x.s);
                } else {
                    (*length[u])[x.f] = x.s;
                }
            }
        }
    }
    if ((*length[u]).count(K - 0 + depth[u])) ans = min(ans, (*length[u])[K+depth[u]]-edepth[u]);
    dbg(*length[u]);
}

int best_path(int N, int K, int H[][2], int L[]) {
    ::K = K;
    for (int i = 0; i < N-1; i++) {
        adj[H[i][0]].push_back({H[i][1], L[i]});
        adj[H[i][1]].push_back({H[i][0], L[i]});
    }
    ans = 1e18;
    edepth[0] = 0;
    dfs(0, -1);
    solve(0, -1);
    if (ans == 1e18) ans = -1;
    return ans;
}

int H[200005][2];
int L[200005];
int32_t main() {
#ifndef DEBUG
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N-1; i++) cin >> H[i][0] >> H[i][1] >> L[i];
    cout << best_path(N, K, H, L) << "\n";
    dbg(edepth[0]);
}
