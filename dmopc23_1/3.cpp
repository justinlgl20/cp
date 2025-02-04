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

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int parent[5005];
int rep(int u) {
    if (parent[u] == u) return u;
    return parent[u] = rep(parent[u]);
}
void merge(int a, int b) {
    dbg("MERGING", a, b);
    parent[rep(b)] = rep(a);
}

int idk[5005];
bool on[5005][5005];
int queries[5005][5005];

int query(int l, int r) {
    if (queries[l][r] != 0) return queries[l][r];
    cout << "? " << l << " " << r << "\n" << flush;
    int x; cin >> x;
    queries[l][r] = x;
    return x;
}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    auto start = std::chrono::steady_clock::now();
    int N; cin >> N;
    for (int i = 1; i <= N; i++) parent[i] = i;
    int previous = 1;
    idk[0] = 1;
    on[0][1] = 1;
    int loops = 0;
    for (int i = 2; i <= N; i++) {
        assert(loops < 20000000);
        int x = query(1, i);
        if (x == idk[0])
        {
            int l = i;
            for (int j = log2(i); j >= 0; j--) {
                int r = i;
                int l_ = max((int)(l - pow((int)2, j)), 1ll);
                dbg(l_, 1<<j, l);
                loops+=1;
                if (query(l_, r) != idk[l_-1]) {
                    l -= 1<<j;
                    l = max(l, 1ll);
                }
            }
            merge(max(1ll, l-1), i);
        }
        previous = x;
        for (int j = 0; j < i; j++) {idk[j] += !on[j][rep(i)];on[j][rep(i)] = true; loops+=1;}
        loops += 1;
    }
    assert(loops < 20000000);
    unordered_map<int, int> vals;
    int cnt = 1;
    for (int i = 1; i <= N; i++) {
        if (rep(i) == i) vals[i] = cnt++;
    }
    cout << "! ";
    for (int i = 1; i <= N; i++) {
        cout << vals[rep(i)] << " \n"[i==N];
    }
    cout << flush;
    return 0;
}
