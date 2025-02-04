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

const int SQRT = 400;

struct ds {
    vector<int> bucket_sums;
    vector<int> indiv;
    int bucket_in(int x) {
        return x/SQRT;
    }
    int n;
    ds(int n) {
        this->n = n;
        indiv.resize(n+4);
        bucket_sums.resize(n/SQRT+5);
        for (int i = 0; i <= n+2; i++) {
            indiv[i] = 0;
        }
        for (int i = 0; i <= n/SQRT+2; i++) {
            bucket_sums[i] = 0;
        }
    }
    void insert(int p, int add) {
        indiv[p] += add;
        bucket_sums[bucket_in(p)] += add;
        assert(indiv[p] >= 0);
        assert(bucket_sums[bucket_in(p)] >= 0);
    }
    int query(int k) {
        int sum_so_far = 0;
        for (int i = 0; i <= n/SQRT+1; i++) {
            assert(i <= bucket_sums.size()-1);
            if (sum_so_far + bucket_sums[i] < k) {
                sum_so_far += bucket_sums[i];
                continue;
            } else {
                for (int j = SQRT*i; j < min(SQRT*(i+1), n+2); j++) {
                    if (sum_so_far + indiv[j] < k) {
                        sum_so_far += indiv[j];
                    } else {
                        return j;
                    }
                }
            }
        }
    }
};

unordered_map<int, int> compress;
int decompress[100005];
int l = 1, r = 1;

ds *x;
int val[100005];
int original[100005];
int ans[100005];

void ll() {
    x->insert(val[l-1], 1);
    l-=1;
}
void rr() {
    x->insert(val[r+1], 1);
    r+=1;
}
void rl() {
    x->insert(val[r], -1);
    r -= 1;
}
void lr() {
    x->insert(val[l], -1);
    l+=1;
}

int32_t main() {
    int n, m; cin >> n >> m;
    set<int> stuff;
    for (int i = 1; i <= n; i++) {
        cin >> original[i];
        stuff.insert(original[i]);
    }
    int inx = 1;
    for (auto i : stuff) {
        compress[i] = inx;
        decompress[inx] = i;
        inx++;
    }
    for (int i = 1; i <= n; i++) {
        val[i] = compress[original[i]];
    }
    x = new ds(inx+10);
    x->insert(val[1], 1);
    vector<tuple<int, int, int, int>> queries;
    for (int i = 0; i < m; i++) {
        int l, r, k; cin >> l >> r >> k;
        queries.emplace_back(l, r, k, i);
    }
    sort(all(queries), [&](tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
        if (((int)(get<0>(a)))/SQRT != ((int)(get<0>(b)))/SQRT) return ((int)(get<0>(a)))/SQRT < ((int)(get<0>(b)))/SQRT;
        return (get<1>(a)) < (get<1>(b));
    });
    for (auto i : queries) {
        int tl = get<0>(i);
        int tr = get<1>(i);
        while (l > tl) ll();
        while (r < tr) rr();
        while (l < tl) lr();
        while (r > tr) rl();
        int k = get<2>(i);
        int a = x->query(k);
        ans[get<3>(i)] = a;
    }
    for (int i = 0; i < m; i++) cout << decompress[ans[i]] << "\n";
}
