#include "train.h"
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

struct train {
    int a, b;
    int u, v;
    int c;
    int id;
};

struct tree {
    int n;
    vector<vector<int>> t;
    tree(int n) {
        this->n = n;
        t.resize(4*n+5);
        for (int i = 0; i < 4*n+3; i++) t[i] = vector<int>();
    }
    void set(int p, int v) {
        t[p+=n].push_back(v);
        for (;p>1; p>>=1) {
            t[p>>1].push_back(v);
        }
    }
    int query(int l, int r, int k) { // number which are lower than k between l and r
        r++;
        int ans = 0;
        for (l += n, r+= n; l < r; l>>=1, r>>=1) {
            if (l&1) {
                //
                ans += (lower_bound(all(t[l]), k)-t[l].begin());
                l++;
            }
            if (r&1) {
                r--;
                //
                ans += (lower_bound(all(t[r]), k)-t[r].begin());
            }
        }
        return ans;
    }
    void process() {
        for (int i = 0; i < 4*n+3; i++) sort(all(t[i]));
    }
};


long long solve(int32_t N, int32_t M, int32_t W, std::vector<int32_t> T, std::vector<int32_t> X, std::vector<int32_t> Y,
                std::vector<int32_t> A, std::vector<int32_t> B, std::vector<int32_t> C, std::vector<int32_t> L,
                std::vector<int32_t> R) {
    set<int> times;
    for (int i = 0; i < M; i++) {
        times.insert(A[i]);
        times.insert(B[i]);
    }
    for (int i = 0; i < W; i++) {
        times.insert(L[i]);
        times.insert(R[i]);
    }
    map<int, int> compress;
    map<int, int> decompress;
    int inx = 1;
    for (int i : times) {
        compress[i] = inx++;
        decompress[inx-1] = i;
    }
    vector<vector<int>> leaving(N+5, vector<int>());

    vector<train> trains;
    for (int i = 0; i < M; i++) {
        train x = train{compress[A[i]], compress[B[i]], X[i], Y[i], C[i], i};
        dbg(x.a, x.b, x.u, x.v, x.c, x.id);
        leaving[x.u].push_back(i);
        trains.push_back(x);
    }
    vector<int> previous_train(M+4, -1);
    for (int i = 0; i < N; i++) {
        sort(all(leaving[i]), [&](int a, int b) {
                return trains[a].a < trains[b].a;
                });
        for (int j = 1; j < leaving[i].size(); j++) {
            previous_train[leaving[i][j]] = leaving[i][j-1];
        }
    }
    vector<train> train_origin = trains;

    vector<pii> ranges;
    for (int i = 0; i < W; i++) {
        ranges.emplace_back(compress[L[i]], compress[R[i]]);
    }
    tree seg = tree(1<<19);
    sort(all(ranges));
    for (auto i : ranges) {
        seg.set(i.first, i.second);
    }
    seg.process();

    sort(all(trains), [&](train a, train b) {
            return a.b < b.b;
            });
    vector<int> dp(M+5, 1e18);
    auto compare = [&](int a, int b) {
        return train_origin[a].b > train_origin[b].b;
    };
    vector<priority_queue<int, vector<int>, decltype(compare)>> waiting(N+5, priority_queue<int, vector<int>, decltype(compare)>(compare));

    function<int(int, int)> ranges_in = [&](int l, int r) {
        return seg.query(l, r, r);
    };
    trains.push_back(train{inx, inx+1, N-1, N, 0, M});
    for (auto i : trains) {
        // take all trains in waiting[i.a] which previous_train[i.id] can't take
        if (i.u == 0) {
            int q = ranges_in(0, i.a-1);
            dbg(q);
            dp[i.id] = min(dp[i.id], T[i.u]*q+i.c);
        }
        int g;
        if (previous_train[i.id] == -1) g = -1;
        else  g = train_origin[previous_train[i.id]].a; // previous time a train left here
        // THIS BIT NEEDS FIXING
        dbg(g);
        while (waiting[i.u].size() and waiting[i.u].top() > g) { // BUG OF THE CURRENT TRAIN COULD LEAVE BEFORE THE TRAIN ARRIVED AT I.U
            // we want trains which arrived at i.u after time g but before time i.a
            int last_train = waiting[i.u].top();
            waiting[i.u].pop();
            dp[i.id] = min(dp[i.id], dp[last_train]+T[i.u]*ranges_in(train_origin[last_train].b, i.a)+i.c);
        }
        dbg(i.id, dp[i.id]);
        waiting[i.v].push(i.id);

    }
    return dp[M];
    
    //tree.set(l[i], r[i]); // l[i] index is r[i]
    

}

