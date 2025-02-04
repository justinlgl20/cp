#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
#ifdef DEBUG
/* 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}*/
 
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

int col[105];
int deg[105];
int depth[105], n, m;
vector<int> adj[105];

string get_string() {
    string s;
    for (int i = 0; i < n; i++) {
        s += to_string(col[i])+" ";
    }
    s+="\n";
    return s;
}

int32_t main() {
    srand(69);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        deg[a]++;
        deg[b]++;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (n == 2) {
        cout << "1\n0 0\n";
        return 0;
    }
    int root = 0;
    int d = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] > d) {
            d = deg[i];
            root = i;
        }
    }
    if (d == 2) {
        root = 0;
        for (int i = 0; i < n; i++) if (deg[i] == 1) root = i;
    }
    for (int i = 0; i < n; i++) {
        col[i] = i;
    }
    for (auto i : adj[root]) col[i] = root;
    string spec1=get_string();
    
    int mdepth = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        for (auto i : adj[u]) {
            if (i != p) {
                depth[i] = depth[u]+1;
                mdepth = max(mdepth, depth[i]);
                dfs(i, u);
            }
        }
    };
    dfs(root, -1);
    for (int i = 0; i < n; i++) {
        col[i] = (depth[i]/2)%2;
    }
    if (d != 2) col[root] = 2;
    string movement = get_string();
    for (int i = 0; i < n; i++) {
        col[i] = ((depth[i]+1)/2)%2;
    }
    if (d != 2) col[root] = 2;
    string movement2 = get_string();
    if (d == 2) {
        cout << 600 << "\n";
        for (int i = 0; i < 300; i++) {
            cout << movement << movement2;
        }
        return 0;
    }
    int k = (2000/(mdepth+3)-2)/2;
    k = 1;
    cout << (2*k+3)*(mdepth+3) << "\n";
    for (int i = 0; i < mdepth+3; i++) {
        for (int j = 0; j < k; j++) {
            int g = adj[root][rand()%((int)adj[root].size())];
            for (int i = 0; i < n; i++) {
                col[i] = i;
            }
            col[g] = root;
            string spec2=get_string();
            cout << spec1 << spec2;
        }
        cout << spec1;
        cout << movement2;
        cout << movement;
    }
}
