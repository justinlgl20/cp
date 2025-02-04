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


int32_t main() {
    int ans = 0;
    ptr root = new Node(5, Value{(int)1e9});
    function<void()> query = [&]() {
        int q = queryi(root, 0, sz(root)-1).mn;
        if (q > 0) {
            ans++;
            updi(root, 0, sz(root)-1, Lazy{-1ll});
        }
    };
    ptr n = new Node(0, Value{2});
    ins(root, n);
    query();
    n = new Node(1, Value{1});
    ins(root, n);
    query();
    n = new Node(2, Value{1});
    ins(root, n);
    n = new Node(3, Value{1});
    ins(root, n);
    ptr x = del(root, 0);
    x = del(root, 1);
    query();
    n = new Node(4, Value{1});
    ins(root, n);
    x=del(root, 2);
    x=del(root, 3);
    query();
    query();
    cout << ans << "\n";
}
