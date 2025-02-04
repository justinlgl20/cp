#include "highway.h"
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define f first
#define s second


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


void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    int M = U.size();
    vector<vector<pii>> adj(N+1);
    for (int i = 0; i < M; i++) {
        adj[U[i]].push_back({V[i], i});
        adj[V[i]].push_back({U[i], i});
    }
    if (B < A) swap(A, B);
    int dist = 0;
    vector<int> W(M);
    for (int i = 0; i < M; i++) W[i] = 0;
    dist = ask(W)/A;
    vector<int> edge_depth(M);
    vector<int> depth(N);
    vector<int> edge_above(N);
    depth[0] = 0;
    int max_depth = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto i : adj[u]) {
            if (i.f != p) {
                edge_depth[i.s] = depth[u];
                depth[i.f] = depth[u]+1;
                edge_above[i.f] = i.s;
                max_depth = max(max_depth, depth[i.f]);
                dfs(i.f, u);
            }
        }
    };
    dfs(0, -1);
    int lo = 0; // if mark all edges under as B, then there is at least 1 B edge in the path
    int hi = max_depth+1; // if mark all edges under as B, then there are no B edges, meaning the depth is lower than lower of S and T
    int calls = 1;
    while (lo != hi-1) {
        int mid = (lo+hi)/2;
        for (int i = 0; i < M; i++) {
            W[i] = 0;
            if (edge_depth[i] >= mid) W[i] = 1;
        }
        int x = ask(W);
        calls += 1;
        if (x == dist*A) hi = mid;
        else lo = mid;
    }
    dbg(calls);
    //hi is ans
    int depth_lower_node = hi;
    vector<int> considering;
    for (int i = 0; i < N; i++) {
        if (depth[i] == depth_lower_node) {considering.push_back(i);}
    }
    lo = 0;
    hi = considering.size();
    while (hi-lo >= 1) {
        int mid  = (lo+hi)/2;
        for (int i = 0; i < M; i++) {
            W[i] = 0;
        }
        for (int i = lo; i <= mid; i++) {
            W[edge_above[considering[i]]] = 1;
        }
        int x = ask(W);
        calls += 1;
        if (x == dist*A) lo = mid+1;
        else hi = mid;
    }
    dbg(calls);
    int node_1 = considering[lo];
    depth[node_1] = 0;
    dfs(node_1, -1);
    //dist edges away
    considering.clear();
    for (int i = 0; i < N; i++) {
        if (depth[i] == dist) considering.push_back(i);
    }
    lo = 0;
    hi = considering.size();
    while (hi-lo >= 1) {
        int mid  = (lo+hi)/2;
        for (int i = 0; i < M; i++) {
            W[i] = 0;
        }
        for (int i = max(lo, 0); i <= mid; i++) {
            W[edge_above[considering[i]]] = 1;
        }
        int x = ask(W);
        calls+=1;
        if (x == dist*A) lo = mid+1;
        else hi = mid;
    }
    dbg(calls);
    int node_2 = considering[lo];
    answer(node_1, node_2);
}
