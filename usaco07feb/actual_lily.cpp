#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int m, n;
int id(int i, int j) {
    if (!(0 <= i and i < m and 0 <= j and j < n)) {
        return -1;
    }
    return i*n+j;
}

int val[905];

int dp[905][905];

vector<int> adj[905];
set<int> adj2[905];

struct dsu{
    vector<int> p;
    dsu(int n) {
        p.resize(n+4);
        for (int i = 0; i < n+3; i++) p[i] = i;
    }
    int rep(int u) {
        if (p[u] == u) return u;
        return p[u] = rep(p[u]);
    }
    void merge(int a, int b) {
        a = rep(a), b = rep(b);
        if (a == b) return;
        p[a] = b;
    }
};

bool check[1010];
int dis[1010];
int sum[1010];
void spfa(int st){
	memset(dis,1e18,sizeof dis);
	memset(check,false ,sizeof check);
	queue<int >q;
	q.push(st);
	check[st]=true;
	dis[st]=0;
	sum[st]=1;
	while(!q.empty()){
		int u=q.front();
		for(int i=head[u];i;i=e[i].next ){
			int v=e[i].v ;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				sum[v]=sum[u];
				if(!check[v]){
					check[v]=true;
					q.push(v);
				}
			}
			else if(dis[v]==dis[u]+1)sum[v]+=sum[u];
		}
		check[u]=false;
		q.pop();
	}
}

int32_t main() {
    cin >> m >> n;
    int start = -1;
    int finish = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> val[id(i, j)];
            if (val[id(i, j)] == 3) {
                start = id(i, j);
                val[id(i, j)] = 1;
            } else if (val[id(i, j)] == 4) {
                finish = id(i, j);
                val[id(i, j)] = 1;
            }
        }
    }
    vector<int> q = {1, 1, -1, -1, 2, 2, -2, -2};
    vector<int> p = {2, -2, 2, -2, 1, -1, 1, -1};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (val[id(i, j)] != 2) {
                for (int k = 0; k < 8; k++) {
                    if (id(i+q[k], j+p[k]) != -1 and val[id(i+q[k], j+p[k])] != 2) {
                        adj[id(i, j)].emplace_back(id(i+q[k], j+p[k]));
                    }
                }
            }
        }
    }
    dsu uf = dsu(m*n);
    for (int i = 0; i < m*n; i++) {
        if (val[i] == 1) {
            for (auto j : adj[i]) {
                if (val[j] == 1) {
                    uf.merge(i, j);
                }
            }
        } 
    }
    vector<int> best(m*n, 1e9), seen(m*n, 0), ways(m*n, 0);
    stack<int> todo;
    todo.push(uf.rep(start));
    ways[uf.rep(start)] = 1;
    best[uf.rep(start)] = 0;
    while (todo.size()) {
        int u = todo.front();
        todo.pop();
        if (seen[u]) continue;
        dbg(u, best[u]);
        seen[u] = true;
        unordered_map<int, int> f;
        for (int i : adj[u]) {
            i = uf.rep(i.f);
            if (f[i]) continue;
            f[i] = 1;
            if (val[u] == 0) {
                if (best[u]+1 == best[i]) {
                    ways[i] += ways[u];
                } else if (best[u]+1 < best[i]) {
                    best[i] = best[u]+1;
                    ways[i] = ways[u];
                    todo.push(i);
                }
            } else if (val[i] == 0 and val[u] == 1) {
                // edge weight of 0
                if (best[u] == best[i]) {

                }
            }
        }
    }
    cout << best[uf.rep(finish)]-1 << "\n";
    cout << ways[uf.rep(finish)] << "\n";
}
