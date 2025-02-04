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

struct line {
    int m, c;
    int get(int x) {
        return m * x + c;
    }
};

line lid = {-1, 0};

struct lichao {
    line val;
    int tl, tr;
    lichao *l, *r;
    lichao (int tl, int tr) {
        this->tl = tl; this->tr = tr;
        val = lid;
        l = r = NULL;
    }
    void add(line li) {
        int tm = (tl+tr)>>1ll;
        if (li.get(tm) > val.get(tm)) {
            swap(li, val);
        }
        if (li.m == lid.m and li.c == lid.c) return;
        if (tl == tr) return;
        if (li.get(tl) > val.get(tl)) {
            if (l == NULL) {
                l = new lichao(tl, tm);
            }
            l->add(li);
        } else if (li.get(tr) > val.get(tr)) {
            if (r == NULL) {
                r = new lichao(tm+1ll, tr);
            }
            r->add(li);
        }
        dbg("HI");
    }
    int query(int x) {
        int ans = val.get(x);
        if (l and x <= (tl+tr)/2) {
            ans = max(ans, l->query(x));
        }
        if (r and x <= (tl+tr)/2) {
            ans = max(ans, r->query(x));
        }
        return ans;
    }
};

int32_t main() {
    int n, k; cin >> n >> k;
    vector<pair<pii, int>> places;
    for (int i = 0; i < k; i++) {
        int a, b, c; cin >> a >> b >> c;
        places.emplace_back(make_pair(a, b), c);
    }
    lichao left = lichao(0, 1e9+10);
    lichao right = lichao(0, 1e9+10);
    places.emplace_back(make_pair(0, 0), 0);
    sort(all(places));
    vector<pair<pii, int>> values;
    places[0] = make_pair(make_pair(0, 0), 0);
    sort(all(places));
    vector<int> val(k+3, 0);
    for (int i = 0; i <= k; i++) val[i] = places[i].s;
    vector<int> dp(k+3, -1e9);
    dp[0] = 0;
    vector<pair<pii, int>> past;
    past.emplace_back(make_pair(0ll, 0ll), 0ll);
    for (int i = 1; i <= k; i++) {
        int row = places[i].f.f, block = places[i].f.s;
        int x = block, y = row-block;
        for (auto q : past) {
            if (q.f.f <= x and q.f.s <= y) {
                dp[i] = max(dp[i], q.s);
            }
        }
        dp[i] += val[i];
        past.emplace_back(make_pair(x, y), dp[i]);
        values.emplace_back(make_pair(row, block), dp[i]);
    }


    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        int ans = -min(l, r)*(n-1);
        for (auto i : values) {
            int a = i.s -(i.f.s-1ll)*r - l*(i.f.f-i.f.s) - min(l, r) * (n-i.f.f);
            dbg(i.f.f, i.f.s, a, i.s);
            ans = max(ans, a); 
        }
        cout << ans << "\n";
    }
}
