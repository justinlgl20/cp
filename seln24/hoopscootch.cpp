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


struct node {
    int val;
    int tl, tr;
    node *l, *r;
    node(int tl, int tr) : tl(tl), tr(tr){
        val = -1e18;
        l = r = nullptr;
    }
    void make() {
        int tm = (tl+tr)/2;
        if (!l) {
            l = new node(tl, tm);
        }
        if (!r) {
            r = new node(tm+1, tr);
        }
    }
    void upd(int i, int v) {
        val = max(val, v);
        if (tl == tr) return;
        make();
        int tm = (tl+tr)/2;
        if (i <= tm) {
            l->upd(i, v);
        } else {
            r->upd(i, v);
        }
    }
    int query(int x1, int x2) {
        if (x1 > tr or x2 < tl) return -1e18;
        if (x1 <= tl and tr <= x2) {
            return val;
        }
        make();
        return max(l->query(x1, x2), r->query(x1, x2)); 
    }
};

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
    }
    int query(int x) {
        int ans = val.get(x);
        if (l and x <= (tl+tr)/2) {
            ans = max(ans, l->query(x));
        }
        if (r and x > (tl+tr)/2) {
            ans = max(ans, r->query(x));
        }
        return ans;
    }
};

struct maxtree {
    vector<int> t;
    int n;
    maxtree(int x) {
        n = 1;
        while (n <= x) n *= 2;
        t.resize(n*3+2);
        for (int i = 0; i < n*3+1; i++) t[i] = -1e18;
    }
    void upd(int p, int v) {
        p+=n;
        for (t[p] = max(t[p], v); p > 1; p>>=1) t[p>>1] = max(t[p], t[p^1]);
    }
    int query(int l, int r) {
        r++;
        int ans = -1e18;
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) ans = max(ans, t[l++]);
            if (r&1) ans = max(ans, t[--r]);
        }
        return ans;
    }
};

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
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
    for (int _ = 0; _ < 2; _++) {
        dbg(_);
        if (_ == 1) {
            for (auto &i : places) {
                i.f.s = i.f.f - i.f.s + 1ll;
            }
        }
        places[0] = make_pair(make_pair(0, 0), 0);
        sort(all(places), [&](pair<pii, int> a, pair<pii, int> b) {
            int x = a.f.s;
            int y = a.f.f-x;
            if (x == b.f.s) {
                return y < b.f.f-b.f.s;
            }
            return x < b.f.s;
        });;
        vector<int> val(k+3, 0);
        for (int i = 0; i <= k; i++) val[i] = places[i].s;
        vector<pair<pii, int>> past;
        //node tree = node(0, 1e9+3);
        vector<pair<pii, int>> values;
        //tree.insert(0, 0, 0);
        node t = node(0, 1e9+3);
        t.upd(0, 0);
        for (int i = 1; i <= k; i++) {
            int row = places[i].f.f, block = places[i].f.s;
            int x = block, y = row-block;
            int vale = -1e18;
            /*for (auto q : past) {
                if (q.f.f <= x and q.f.s <= y) {
                    dp[i] = max(dp[i], q.s);
                }
            }*/
            dbg(x, y);
           // vale = tree.query(0, x, 0, y);
            vale = t.query(0, y);
            vale += val[i];
            //tree.insert(x, y, vale);
            t.upd(y, vale);
            values.emplace_back(make_pair(row, block), vale);
        }
        if (_ == 0) {
            left.add(line{-1, 0});
            for (auto i : values) {
                left.add(line{-i.f.s, i.s});
            }
        } else {
            right.add(line{-1, 0});
            for (auto i : values) {
                right.add(line{-i.f.s, i.s});
            }
        }
    }
    dbg("BUILT");


    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        if (l < r) {
            int ans = left.query(r-l) - n*l + r;
            cout << ans << "\n";
        } else {
            int ans = right.query(l-r);
            ans += - n*r + l;
            cout << ans << "\n";
        }
    }
}
