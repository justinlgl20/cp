#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 #define pii pair<int, int>
#define f first
#define s second
ostream& operator<<(ostream& os, pii x) {
    os << "(" << x.f << " " << x.s << ")";
    return os;
}
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
struct segtree {
    vector<int> p;
    int n;
    segtree(int x) {
        n = 1; while (n <= x) n*=2;
        p.resize(n*3+4);
        for (int i = 0; i < n*3+3; i++) p[i] = 0;
    }
    void upd(int i, int v) {
        for (p[i+=n] += v; i > 0; i>>=1) p[i>>1] = p[i]+p[i^1];
    }
    int query(int l, int r) {
        r++;
        int ans = 0;
        for (l+=n, r+=n; l < r; l>>=1, r>>=1) {
            if (l&1) ans += p[l++];
            if (r&1) ans += p[--r];
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    vector<pii> g(n);
    unordered_map<int, int> xcompress;
    unordered_map<int, int> ycompress;
    set<int> xs, ys;
    for (int i = 0; i < n; i++) {
        cin >> g[i].f >> g[i].s;
        xs.insert(g[i].f);
        ys.insert(g[i].s);
    }
    vector<int> xdecompress(n+4, 0), ydecompress(n+4, 0);
    int cnt = 1;
    for (auto i : xs) {
        xcompress[i] = cnt++;
        xdecompress[cnt-1] = i;
    }
    int savevar = cnt;
    cnt = 1;
    for (auto i : ys) {
        ycompress[i] = cnt++;
        ydecompress[cnt-1] = i;
    }
    dbg(cnt);

    for (int i = 0; i < n; i++) {
        g[i].f = xcompress[g[i].f];
        g[i].s = ycompress[g[i].s];
    }
    vector<pii> city = g;
    int inx = 0;
    int left = 0, right = n;
    segtree seg = segtree(n+2);
    vector<int> ans(cnt+2, 0);
    sort(all(city), [&](pii a, pii b) {
        return a.s < b.s;
    });
    segtree seg2 = segtree(n+2);
    int inx2 = 0;
    for (auto i : city) seg2.upd(i.f, 1);
    int fans = 0;
    pii bcut = {0, 0};
    for (int y = 0; y < cnt; y++) { // gap is on the left of y
        while (inx2 < n and city[inx2].s == y) {
            seg2.upd(city[inx2].f, -1);
            right--;
            inx2++;
        }
        while (inx < n and city[inx].s == y) {
            seg.upd(city[inx].f, 1);
            left++;
            inx++;
        }

        dbg(y);
        for (int i = 0; i < 3; i++) {
            dbg(seg.query(i, i));
            dbg(seg2.query(i, i));
        }

        function<bool(int)> works = [&](int cut) {
            int g = seg.query(0, cut);
            int g2 = seg2.query(0, cut);
            if (g > left/2 and g2 > right/2) return false;
            if (g <= left/2 and g2 <= right/2) return true;
            if (g > left/2 and g2 <= right/2) {
                //left-g vs g2
                if (g2 < left-g) return true;
                if (left-g <= g2) return false;
            }
            if (g <= left/2 and g2 > right/2) {
                //g vs right-g2
                if (g < right-g2) return true;
                if (right-g2 <= g) return false;
            }
            return true;
        };

        int opt = 0;
        for (int i = 19; i >= 0; i--) {
            if (opt + (1ll<<i) <= n and works(opt + (1ll<<i))) {
                opt += (1ll<<i);
            }
        }
        ans[y] = 0;
        int best_op = 0;
        for (int i = -3; i < 4; i++) {
            if (0 <= opt+i and opt+i <= n) {
                int g = seg.query(0, opt+i);
                g = min(g, left-g);
                int h = seg2.query(0, opt+i);
                h = min(h, right-h);
                int pans = min(g, h);
                if (pans > ans[y]) {
                    ans[y] = pans;
                    best_op = opt+i;
                }
            }
        }
        if (ans[y] > fans) {
            fans = ans[y];
            bcut = make_pair(best_op, y);
        }
    }
    cout << fans << "\n";
    cout << xdecompress[bcut.f+1] << " " << ydecompress[bcut.s+1] << "\n";
   

}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
