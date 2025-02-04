#include <bits/stdc++.h>
using namespace std;
 
#define int long long

#define ll int
 
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

// generated at caterpillow.github.io/byot

struct Lazy {
    int val;

    void operator+=(const Lazy& oth) {
        val += oth.val;
    }
};

const Lazy lid = {0};


// You can implement your own monoid here for custom operations.
struct Value {
    int mn;

    void upd(Lazy lazy, int sz) {
        mn += lazy.val;
    }

    Value operator+(const Value& oth) const {
        Value res {};
        res.mn = min(mn, oth.mn);
        return res;
    }
};

const Value vid = {1'000'000'000};

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
using ptr = struct Node*;

struct Node {
    Value val;
    Value agg;
    Lazy lazy;

    ll key;
    int sz;
    int pri;
    ptr l, r;

    Node() {
        pri = mt();
        val = vid;
        agg = vid;
        lazy = lid;
        sz = 0;
        l = r = nullptr;
    }

    Node(ll key, Value val) : key(key), val(val), agg(val) {
        pri = mt();
        lazy = lid;
        sz = 1;
        l = r = nullptr;
    }

    ~Node() {
        delete l;
        delete r;
    }
};

int sz(ptr n) { return n ? n->sz : 0; };
Value agg(ptr n) { return n ? n->agg : vid; }

void push(ptr n) {
    n->val.upd(n->lazy, 1);
    n->agg.upd(n->lazy, sz(n));
    if (n->l) n->l->lazy += n->lazy;
    if (n->r) n->r->lazy += n->lazy;
    n->lazy = lid;
}

ptr pull(ptr n) {
    if (!n) return nullptr;
    if (n->l) push(n->l);
    if (n->r) push(n->r);
    n->sz = sz(n->l) + 1 + sz(n->r);
    n->agg = agg(n->l) + n->val + agg(n->r);
    return n;
}

ptr merge(ptr l, ptr r) {
    if (!l || !r) return l ? l : r;
    push(l), push(r);
    if (l->pri > r->pri) return l->r = merge(l->r, r), pull(l);
    else return r->l = merge(l, r->l), pull(r);
}

// [-inf, k) and [k, inf]
pair<ptr, ptr> split(ptr n, ll k) {
    if (!n) return {nullptr, nullptr};
    push(n);
    if (k <= n->key) {
        auto [l, r] = split(n->l, k);
        n->l = r;
        return {l, pull(n)};
    } else {
        auto [l, r] = split(n->r, k);
        n->r = l;
        return {pull(n), r};
    }
}

// only insert single nodes
void ins(ptr& n, ptr it) {
    if (!n) { n = it; return; }
    if (n->pri < it->pri) {
        auto [l, r] = split(n, it->key);
        it->l = l, it->r = r, n = it;
    } else if (it->key <= n->key) ins(n->l, it);
    else ins(n->r, it);
    pull(n);
}

// returns pointer to deleted node
ptr del(ptr& n, ll k) {
    if (!n) return nullptr;
    push(n);
    if (n->key == k) { ptr ret = n; n = merge(n->l, n->r); return ret; }
    ptr ret = k <= n->key ? del(n->l, k) : del(n->r, k);
    pull(n);
    return ret;
}

void updi(ptr n, int lo, int hi, Lazy lazy) {
    if (!n) return;
    push(n);
    if (lo >= n->sz || hi <= 0) return;
    if (lo <= 0 && n->sz <= hi) {
        n->lazy += lazy;
        push(n);
        return;
    }
    if (lo <= sz(n->l) && sz(n->l) < hi) n->val.upd(lazy, 1);
    updi(n->l, lo, hi, lazy);
    updi(n->r, lo - 1 - sz(n->l), hi - 1 - sz(n->l), lazy);
    pull(n);
}

Value queryi(ptr n, int lo, int hi) {
    if (!n || lo >= sz(n) || hi <= 0) return vid;
    push(n);
    if (lo <= 0 && sz(n) <= hi) return n->agg;
    return queryi(n->l, lo, hi) + (lo <= sz(n->l) && sz(n->l) < hi ? n->val : vid) + queryi(n->r, lo - 1 - sz(n->l), hi - 1 - sz(n->l));
}

struct node {
    int tl, tr, val, lazy;
    node *l, *r;
    node(int ql, int qr) {
        tl = ql; tr = qr;
        val = 1e9;
        lazy = 0;
        int tm = (tl+tr)/2;
        if (tl == tr) return;
        l = new node(tl, tm);
        r = new node(tm+1, tr);
    }
    void push() {
        if (lazy) {
            val += lazy;
            if (tl != tr) {
                l->lazy += lazy;
                r->lazy += lazy;
            }
            lazy = 0;
        }
    }
    int query(int ql, int qr) {
        if (tl > qr or ql > tr) {
            return 1e9;
        }
        push();
        if (ql <= tl and tr <= qr) {
            return val;
        }
        return min(l->query(ql, qr), r->query(ql, qr));
    }
    void upd(int ql, int qr, int v) {
        if (tl > qr or ql > tr) {
            return;
        }
        push();
        if (ql <= tl and tr <= qr) {
            lazy += v;
            return;
        }
        l->upd(ql, qr, v);
        r->upd(ql, qr, v);
        l->push();
        r->push();
        val = min(l->val, r->val);
    }
    void set(int p, int v) {
        if (tl == tr) {
            val = v;
            lazy = 0;
            return;
        }
        push();
        int tm = (tl+tr)/2;
        if (p <= tm) {
            l->set(p, v);
        } else {
            r->set(p, v);
        }
        l->push();
        r->push();
        val = min(l->val, r->val);
    }
};

void solve() {
    int n, k; cin >> n >> k;
    vector<int> x(n);
    multiset<int> g;
    for (int i = 0; i < n; i++) {cin >> x[i];}
    sort(all(x));
    int inx = 0;
    vector<pair<pii, int>> ranges(k);
    for (int i = 0; i < k; i++) {
        cin >> ranges[i].f.f >> ranges[i].f.s >> ranges[i].s;
    }
    for (int i = 0; i < k; i++) {
        int s = ranges[i].f.f;
        int e = ranges[i].f.s;
        //bsearch to find where e covers up to
        int q = -1;
        for (int qw = 20; qw >= 0; qw--) {
            if (q+(1ll<<qw) < n and x[q+(1ll<<qw)] <= e) {
                q += (1ll<<qw);
            }
        }
        int d = n;
        for (int qw = 20; qw >= 0; qw--) {
            if (d-(1ll<<qw) >= 0 and x[d-(1ll<<qw)] >= s) {
                d -= (1ll<<qw);
            }
        }
        dbg(ranges[i].f.f, ranges[i].f.s, d, q);
        if (ranges[i].f.s-ranges[i].f.f+1ll == 0 or d== n or q == -1) {
            ranges[i].s = -1;
        } else {
            ranges[i].s = (q-d+1ll) - ranges[i].s; // how many i can cut down
        }
        dbg(ranges[i].s);
    }
    ranges.emplace_back(make_pair(-1e9, 1e9), 1e9);
    sort(all(ranges));
    vector<pair<pii, pii>> segnar;
    int cnt = 0;
    for (auto x : ranges) {
        segnar.emplace_back(x.f, make_pair(x.s, cnt));
        cnt++;
    }
    sort(all(segnar), [&](pair<pii, pii> a, pair<pii, pii> b) {
        return a.f.s < b.f.s;
    });
    unordered_map<int, int> qe;
    for (int i = 0; i < segnar.size(); i++) {
        qe[segnar[i].s.s] = i;
    }
    int subtract = 0;
    inx = 0;
    int inx2 = 0;
    int ans = 0;
    ptr root = nullptr;
    // GETTING UB
    node tree = node(0, k+4);
    for (int i : x) {
        while (inx < ranges.size() and ranges[inx].f.f <= i) {
            if (ranges[inx].s == -1) {
                inx++;
                continue;
            }
            int e = qe[inx]; // ENDS HERE
            int t = ranges[inx].s; // CAN TAKE THIS MUCH AWAY IN THIS RANGE
            dbg("INSERT", e, t);
            tree.set(e, t);
            inx++;
        } 
        while (inx2 < segnar.size() and segnar[inx2].f.s < i) {
            if (segnar[inx2].s.f == -1) {
                inx2++;
                continue;
            }
            int e = inx2;
            int t = segnar[inx2].s.f;
            dbg("DELETE", e, t);
            tree.set(e, 1e9);
            inx2++;
        }
        int q = tree.query(0, k+2);
        dbg(i, q);
        if (q > 0ll) {
            ans++;
            //dbg(i);
            tree.upd(0, k+2, -1);
            dbg("-1 on all");
        }

    }
       
    cout << ans << '\n';


}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
