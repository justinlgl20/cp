#include <bits/stdc++.h>
#include "factories.h"
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

int n;

int par[500005];
int val[500005];

vector<pii> adj[500005];
int depth[500005];
int tin[500005]; // pos of thing
int tout[500005]; // exclude that
int hop[500005][25];
int cnt;
void dfs(int u, int p) {
    hop[u][0] = p;
    for (int i = 1; i <= 23; i++) hop[u][i] = hop[hop[u][i-1]][i-1];
    tin[u] = ++cnt;
    for (auto i : adj[u]) {
        if (i.f != p) {
            depth[i.f] = depth[u] + i.s;
            dfs(i.f, u);
        }
    }
    tout[u] = ++cnt;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    int g = u;
    for (int i = 22; i >= 0; i--) {
        if (!is_ancestor(hop[g][i], v)) g = hop[g][i];
    }
    return hop[g][0];
}

int distance(int u, int v) {
    return depth[u]+depth[v]-((int)2)*depth[lca(u, v)];
}

void Init(int32_t N, int32_t A[], int32_t B[], int32_t D[]) {
    n = N;
    for (int i = 0; i <= N-2; i++) {
        adj[A[i]+1].emplace_back(B[i]+1, D[i]);
        adj[B[i]+1].emplace_back(A[i]+1, D[i]);
    }
    depth[1] = 0;
    dfs(1, 0);
    tout[0] = 1e15;
}

bool cmp(int a, int b) {
    return tin[a] < tin[b];
}

struct aux_tree {
    vector<int> nodes;
    unordered_map<int, int> colour;
    unordered_map<int, vector<int>> cadj;
    unordered_map<int, pii> anses;
    unordered_map<int, int> seen;
    unordered_map<int, int> dist;
    int root;
    int ans;
    vector<int> white;
    vector<int> black;
    aux_tree(vector<int> black, vector<int> white) {
        this->white = white;
        this->black = black;
        dbg(white, black);
        ans = 1e15;
        for (auto i : black) {nodes.push_back(i); colour[i] = 1;}
        for (auto i : white) {
            nodes.push_back(i); 
            if (colour[i] == 1) ans = 0;
            colour[i] = 2;
            
        }
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.resize(unique(nodes.begin(), nodes.end())-nodes.begin());
        int k = nodes.size();
        for (int i= 0; i < k - 1; i++) {
            int new_vertex = lca(nodes[i], nodes[i+1]);
            if (colour.find(new_vertex) == colour.end())
                colour[new_vertex] = 0;
            nodes.push_back(new_vertex);
        }
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        vector<int> stck;
        stck.push_back(nodes[0]);
        dist[nodes[0]] = 1e18;
        for (int i = 1; i < nodes.size(); i++) {
            int v = nodes[i];
            dist[v] = 1e18;
            while (stck.size() >= 2 and !is_ancestor(stck.back(), v)) {
                cadj[stck[stck.size()-2]].emplace_back(stck.back());
                cadj[stck.back()].emplace_back(stck[stck.size()-2]);
                stck.pop_back();
            }
            stck.push_back(v);
        }
        while (stck.size() >= 2) {
            cadj[stck[stck.size()-2]].emplace_back(stck.back());
            cadj[stck.back()].emplace_back(stck[stck.size()-2]);
            stck.pop_back();
        }
        root = nodes[0];
    }    
    int solve() {
        if (ans == 0) return 0;
        dbg(nodes);
        for (auto i : nodes) {
            dbg(i, cadj[i]);
        }
        priority_queue<pair<int, int>> q;
        for (int i : white) {
            dist[i] = 0;
            q.push(make_pair(0, i));
        }
        while (q.size()) {
            int t = q.top().s;
            int d = -q.top().f;
            q.pop();
            dbg(t, d);
        
            if (colour[t] == 1) return min(ans, d);
            if (seen[t]) continue;
            //if (d > dist[t]) continue;
            assert(!seen[t]);
            dist[t] = d;
            seen[t] = true;
            for (auto i : cadj[t]) {
                if (dist[t]+distance(i, t) < dist[i]) {
                    dist[i] = dist[t]+distance(i, t);
                    q.push(make_pair(-dist[i], i));
                }
            }
        }
        return ans;
    }
};

long long Query(int32_t S, int32_t X[], int32_t T, int32_t Y[]) {
    vector<int> white;
    for (int i = 0; i < S; i++) white.push_back(X[i]+1);
    vector<int> black;
    for (int i = 0; i < T; i++) black.push_back(Y[i]+1);
    aux_tree g = aux_tree(black, white);
    return g.solve();
}
