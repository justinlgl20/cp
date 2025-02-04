#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
 
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int p[100005];
int loc[100005];

struct seg {
    seg *l, *r;
    int tl; int tr;
    ordered_set things;
    seg(int l, int r) {
        tl = l, tr = r;
        if (tl == tr) {
            if (p[tl] != 0)
                things.insert(p[tl]);
            return;
        }
        int tm = (tl+tr)>>1;
        this->l = new seg(tl, tm);
        this->r = new seg(tm+1, tr);
        this->things = this->l->things;
        for (auto i : this->r->things) things.insert(i);
    }
    void remove(int x) {
        things.erase(things.find(x));
        if (tl == tr) return;
        int tm = (tl+tr)>>1;
        if (loc[x] <= tm) l->remove(x);
        else r->remove(x);
    }

    int smaller_than(int ql, int qr, int x) {
        if (ql <= tl and tr <= qr) {
            return things.order_of_key(x);
        }
        if (tl > qr or tr < ql) return 0;
        return l->smaller_than(ql, qr, x) + r->smaller_than(ql, qr, x);
    }
    int bigger_than(int ql, int qr, int x) {
        if (ql <= tl and tr <= qr) {
            return things.size()-things.order_of_key(x);
        }
        if (tl > qr or tr < ql) return 0;
        return l->bigger_than(ql, qr, x) + r->bigger_than(ql, qr, x);
    }
};

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) {
        loc[p[i]] = i;
    }

    seg tree = seg(0, n+3);
    int fans = 1e9;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += tree.smaller_than(i+1, n, p[i]);
    }
    dbg(ans);
    fans = min(fans, ans);

    for (int i = 1; i <= n; i++) {
        ans -= tree.smaller_than(loc[i]+1, n, i);
        ans -= tree.bigger_than(0, loc[i]-1, i);
        tree.remove(i);
        ans += 1;
        fans = min(fans, ans);
    }
    cout << fans << "\n";
}
