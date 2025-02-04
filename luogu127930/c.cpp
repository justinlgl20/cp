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

const int MAX = 200005; // Max size of array
int tree[4 * MAX] = { 0 }; // Segment tree
int lazy[4 * MAX] = { 0 }; // Lazy array

void updateRange(int node, int start, int end, int l, int r,
                int val)
{
    if (lazy[node] != 5) {
        tree[node] = (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 5;
    }
    if (start > end or start > r or end < l)
        return;
    if (start >= l and end <= r) {
        tree[node] = (end - start + 1) * val;
        if (start != end) {
            lazy[node * 2] = val;
            lazy[node * 2 + 1] = val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node * 2, start, mid, l, r, val);
    updateRange(node * 2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int queryRange(int node, int start, int end, int l, int r)
{
    if (start > end or start > r or end < l)
        return 0;
    if (lazy[node] != 5) {
        tree[node] = (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] = lazy[node];
            lazy[node * 2 + 1] = lazy[node];
        }
        lazy[node] = 5;
    }
    if (start >= l and end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node * 2, start, mid, l, r);
    int p2 = queryRange(node * 2 + 1, mid + 1, end, l, r);
    return (p1 + p2);
}

int32_t main() {
    int n, k; cin >> n >> k;
    set<int> a;
    unordered_map<int, vector<int>> gq;
    for (int i = 0; i < n; i++) {
        int q;
        cin >> q;
        a.insert(q);
        gq[q].push_back(i);
    }
    vector<int> g;
    for (auto i : a) g.push_back(i);
    if (a.size() == 1) {
        for (int i = 0; i < n; i++) {
            cout << 0 << " \n"[i==n-1];
        }
        return 0;
    }

    reverse(all(g));
    vector<int> ans(n+4, 0);
    for (int i = 1; i < n; i++) {

        if (g[i-1]-g[i] <= k) {
            // add a w1
            updateRange(1, 0, 200005, i, i, 1);
            dbg("UPD", i, i, 1);
        } else {
            int free = 0;
            function<bool(int)> works = [&](int x) {
                int q = g[i] + x*k;
                int y = g[i-1] + (((i-1)-(i-1-x+1)+1) - queryRange(1, 0, 200005, i-1-x+1, i-1))*k;
                //dbg(x, q, y);
                if (q < y-k) return 1;
                return 0;
            };
            for (int i = 1ll<<20; i > 0; i >>=1ll) {
                if (free + i <= 200005 and works(free+i)) {
                    free += i;
                }
            }
            free += 1;
            updateRange(1, 0, 200005, i-free+1, i, 0);
            dbg("UPD", free, i-free+1, i, 0);
        }
        ans[i] = queryRange(1, 0, 200005, 0, 200005);

    }
    vector<int> fans(n+4, 0);
    for (int i = 0; i < n; i++) {
        for (auto j : gq[g[i]]) {
            fans[j] = ans[i];
        }
    }
    for (int i = 0; i < n; i++) {
        cout << fans[i] << " \n"[i==n-1];
    }
}
