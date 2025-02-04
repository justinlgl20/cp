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

#define gcd __gcd

// generated at caterpillow.github.io/byot

struct Lazy {

    void operator+=(const Lazy& oth) {
    }
};

const Lazy lid = {};

struct Value {
    int sum;

    void upd(Lazy lazy, int sz) {
    }

    Value operator+(const Value& oth) const {
        Value res {};
        res.sum = gcd(sum, oth.sum);
        return res;
    }
};


const Value vid = {0};

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
using ptr = struct Node*;

struct Node {
    Value val;
    Value agg;
    Lazy lazy;

    int sz;
    int pri;
    ptr l, r;

    Node() {
        pri = rand();
        val = vid;
        agg = vid;
        lazy = lid;
        sz = 1;
        l = r = nullptr;
    }

    Node(Value val) : val(val), agg(val) {
        pri = mt();
        lazy = lid;
        sz = 1;
        l = r = nullptr;
    }
};

int sz(ptr n) { return n ? n->sz : 0; };
Value agg(ptr n) { return n ? n->agg : vid; }

void push(ptr n) {
    if (!n) return;
    n->val.upd(n->lazy, 1);
    n->agg.upd(n->lazy, sz(n));
    if (n->l) n->l->lazy += n->lazy;
    if (n->r) n->r->lazy += n->lazy;
    n->lazy = lid;
}

ptr pull(ptr n) {
    if (!n) return nullptr;
    push(n->l), push(n->r);
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

// [-inf, i) and [i, inf]
pair<ptr, ptr> spliti(ptr n, int i) {
    if (!n) return {nullptr, nullptr};
    push(n);
    if (i <= sz(n->l)) {
        auto [l, r] = spliti(n->l, i);
        n->l = r;
        return {l, pull(n)};
    } else {
        auto [l, r] = spliti(n->r, i - 1 - sz(n->l));
        n->r = l;
        return {pull(n), r};
    }
}

// inserts node such that it will be at index i. only insert single nodes
ptr insi(ptr n, ptr it, int i) {
    if (!n) return it;
    push(n);
    if (n->pri < it->pri) {
        auto [l, r] = spliti(n, i);
        it->l = l, it->r = r;
        return pull(it);
    }
    if (i <= sz(n->l)) n->l = insi(n->l, it, i);
    else n->r = insi(n->r, it, i - 1 - sz(n->l));
    return pull(n);
}

ptr deli(ptr n, int i) {
    if (!n) return nullptr;
    push(n);
    if (i == sz(n->l)) return merge(n->l, n->r);
    if (i <= sz(n->l)) n->l = deli(n->l, i);
    else n->r = deli(n->r, i - 1 - sz(n->l));
    return pull(n);
}

Value queryi(ptr n, int lo, int hi) {
    if (!n || lo >= sz(n) || hi < 0) return vid;
    push(n);
    if (lo <= 0 && sz(n) - 1 <= hi) return n->agg;
    return queryi(n->l, lo, hi) + (lo <= sz(n->l) && sz(n->l) <= hi ? n->val : vid) + queryi(n->r, lo - 1 - sz(n->l), hi - 1 - sz(n->l));
}

ptr findi(ptr n, int i) {
    if (!n) return 0;
    push(n);
    if (sz(n->l) == i) return n;
    if (i < sz(n->l)) return findi(n->l, i);
    else return findi(n->r, i - sz(n->l) - 1);
}

int32_t main() {
    int n, q; cin >> n >> q;
    ptr root = NULL;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        ptr z = new Node(Value{a[i]-a[i-1]});
        root = insi(root, z, i);
    }
    
    while (q--) {
        char c; cin >> c;
        if (c == 'I') {
            int x, v; cin >> x >> v;
            // GET X FROM NORMAL ARRAY
            // GET X-1 FROM NORMAL ARRAY
            int f, s;
            if (x > 0)
                f = a[x-1];
            s = a[x];

            vector<int> idk = {v};

            a.insert(a.begin()+x, idk.begin(), idk.end());
            ptr i;
            if (x > 0) {
                root = deli(root, x-1);
                i = new Node(Value{v-f});
                root = insi(root, i, x-1);
            }
            i = new Node(Value{s-v});
            root = insi(root, i, x);
        }
        else if (c == 'D') {
            int x; cin >> x;
            x--;
            a.erase(a.begin()+x);
            int y = a[x];
            if (x-1 >= 0)
                y = a[x] - a[x-1];

            root = deli(root, x);
            if (x-1 >= 0)
                root = deli(root, x-1);
            ptr i = new Node(Value{y});
            root = insi(root, i, x-1);
        } else if (c == 'A') {
            int l, r, v; cin >> l >> r >> v;
            l--, r--;

            for (int i = l; i <= r; i++) {
                a[i] += v;
            }
            int nval;
            ptr i;
            if (l-1 >= 0) {
                nval = findi(root, l-1)->val.sum + v;
                root = deli(root, l-1);
                i = new Node(Value{nval});
                root = insi(root, i, l-1);
            }
            if (r + 1 < sz(root)) {
                nval = findi(root, r)->val.sum - v;
                root = deli(root, r);
                i = new Node(Value{nval});
                root = insi(root, i, r);
            }

            
        } else if (c == 'Q') {
            int l, r, v; cin >> l >> r >> v;
            l--, r--;
            int g = 0;
            if (r > l) {
                g = queryi(root, l, r-1).sum;
            }
            g = gcd(a[l], g);
            if (v % g == 0) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
        dbg(a);
        for (int i = 0; i < a.size()-1; i++) {
            dbg(i, findi(root, i)->val.sum);
        }
    }

}
