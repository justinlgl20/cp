#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

int n;

int par[200005];
int val[200005];

vector<pii> adj[200005];
int depth[200005];
int tin[200005]; // pos of thing
int tout[200005]; // exclude that
int hop[200005][30];
int cnt;
void dfs(int u, int p) {
    hop[u][0] = p;
    for (int i = 1; i <= 30; i++) hop[u][i] = hop[hop[u][i-1]][i-1];
    tin[u] = ++cnt;
    for (auto i : adj[u]) {
        if (i.f != p) {
            depth[i.f] = depth[u] + i.s;
            dfs(i.f, u);
        }
    }
    tout[u] = cnt;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    int g = u;
    for (int i = 20; i >= 0; i--) {
        if (hop[g][i] != 0 and !is_ancestor(hop[g][i], v)) g = hop[g][i];
    }
    return hop[g][0];
}

int dist(int u, int v) {
    return depth[u]+depth[v]-2*depth[lca(u, v)];
}

void Init(int N, int A[], int B[], int D[]) {
    n = N;
    for (int i = 0; i <= N-2; i++) {
        adj[A[i]+1].emplace_back(B[i]+1, D[i]);
        adj[B[i]+1].emplace_back(A[i]+1, D[i]);
    }
    dfs(1, 0);
}

bool cmp(int a, int b) {
    return tin[a] < tin[b];
}

struct aux_tree {
    vector<int> nodes;
    unordered_map<int, bool> colour;
    unordered_map<int, vector<int>> cadj;
    int root;
    int ans;
    aux_tree(vector<int> black, vector<int> white) {
        ans = 1e18;
        for (auto i : black) {nodes.push_back(i); colour[i] = 1;}
        for (auto i : white) {nodes.push_back(i); colour[i] = 0;}
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.resize(unique(nodes.begin(), nodes.end())-nodes.begin());
        int k = nodes.size();
        for (int i= 0; i < k - 1; i++) {
            int new_vertex = lca(nodes[i], nodes[i+1]);
            nodes.push_back(new_vertex);
        }
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        vector<int> stck;
        stck.push_back(vert[0]);
        for (int i = 1; i < nodes.size(); i++) {
            int v = nodes[i];
            while (stck.size() >= 2 and !is_ancestor(stck.back(), v) {
                cadj[stck[stck.size()-2]].emplace_back(stack_of_vertices.back());
                stck.pop_back();
            }
            stck.push_back(v);
        }
        while (stck.size() >= 2) {
            cadj[stck[stck.size()-2]].emplace_back(stack_of_vertices.back());
            stck.pop_back();
        }
        root = nodes[0];
    }
    int dfs_white(int u, int p) { //returns highest black person
        int highest = 1e18;
        for (int i : cadj[u]) {
            if (i != p) {
                highest = min(highest, dist(i, u)+dfs_white(i, u));
            }
        }
        if (colour[u] == 0) { // we're white
            ans = min(ans, highest);
        } else { // we're black
            highest = 0;
        }
        return highest;
    }
    int dfs_black(int u, int p) {
        int highest = 1e18;
        for (int i : cadj[u]) {
            if (i != p) {
                highest = min(highest, dist(i, u)+dfs_black(i, u));
            }
        }
        if (colour[u] == 1) {
            ans = min(ans, highest);
        } else {
            highest = 0;
        }
        return highest;
    }
    int solve() {
        dfs_white(root, 0);
        dfs_black(root, 0);
        return ans;
    }
};

long long query(int S, int X[], int T, int D[]) {
    vector<int> white;
    for (int i = 0; i < S; i++) white.push_back(X[i]+1);
    vector<int> black;
    for (int i = 0; i < S; i++) black.push_back(D[i]+1);
    aux_tree g = aux_tree(black, white);
    return g.solve();
}


