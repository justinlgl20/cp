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

int nxt() {
    int q; cin >> q; return q;
}

int n, m, q;

struct Bridge {
    int u;
    int v;
    int w;
    int inx;
    Bridge(int u, int v, int w, int inx) {
        this->u = u;
        this->v = v;
        this->w = w;
        this->inx = inx;
    }
    bool operator < (Bridge &other) const {
        return inx < other.inx;
    }
};

struct Query {
    int type, a, b, inx;
    Query(int a, int b, int c, int d) {
        this->type = a;
        this->a = b;
        this->b = c;
        this->inx = d;
    }
    bool operator < (Query &other) const {
        return this->b < other.b;
    }
};

struct Dsu {
    vector<int> par;
    vector<int> sz;
    Dsu(int n) {
        par.resize(n+5);
        sz.resize(n+5);
        for (int i = 0; i <= n+4) {
            par[i] = i;
            sz[i] = 1;
        }
    }
    int rep(int a) {
        if (par[a] == a) return a;
        return par[a] = rep(par[a]);
    }
    void merge(int a, int b) {
        a = rep(a);
        b = rep(b);
        if (sz[a] > sz[b]) swap(b, a);
        par[a] = b;
        sz[b] += sz[a];
    }
    void rollback(int t) {

    }
};

const int sqrt = 350;

vector<Query> upd[100005];

int ans[100005];

int32_t main() {
    n = nxt(); m = nxt();
    vector<Bridge> bridges;
    for (int i = 1; i <= m; i++) {
        int a, b, d; cin >> a >> b >> d;
        bridges.push_back(Bridge(a, b, d, i));
    }
    int updates = 0;
    vector<int> reprocessing_spots;
    vector<vector<Query>> between = {{}};
    q = nxt();
    for (int i = 1; i <= q; i++) {
        ans[i] = -1;
        if (updates >= sqrt) {
            reprocessing_spots.push_back(i);
            updates = 0;
            between.push_back({});
        }
        int a, b, c; cin >> a >> b >> c;
        between[between.size()-1].push_back(Query(a, b, c, i));
        if (a == 1) upd[i] = Query(a, b, c, i);
        updates += 1;
    }
    vector<Query> update_buffer;
    for (int k = 0; k < between.size(); k++) {
        vector<Query> queries;
        for (auto q : update_buffer) {
            bridges[q.a-1].w = q.b;
        }
        vector<int> edges = bridges;
        sort(all(edges));

        for (int i = 0; i < between[k].size(); i++) {
            if (between[k][i].type == 2)
                upd[between[k][i].inx].push_back(between[k][i]);
            else if (between[k][i].type == 1)
                queries.push_back(between[k][i]);
            if (i > 0) {
                for (auto i : upd[between[k][i-1].inx]) upd[between[k][i].inx].push_back(i);
            }
        }

        sort(all(queries));
        int inx = 0;

        Dsu x = Dsu(n);

        for (auto i : edges) {
            if (inx == queries.size()) break;
            if (i.w > queries[inx].b) {
                int cnt = 0;
                for (auto j : upd[queries[inx].inx]) {
                    // need to merge all updates
                    // then rollback to what it was before
                    cnt++;
                }
                x.rollback(cnt);
                ans[queries[inx].inx] = x.sz[rep(queries[inx].a)]; //now we have to add the special cases in upd
                inx++;
            }
            x.merge(i.u, i.v);
        }
        while (inx < queries.size()) {
            ans[queries[inx].inx] = x.sz[rep(queries[inx].a)];
            inx++;
        }


        update_buffer = queries;
    }
}
