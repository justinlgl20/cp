namespace Treap {

    struct Lazy {
        int kval;
    
        void operator+=(const Lazy& oth) {
            kval += oth.kval;
        }
    };
    
    const Lazy lid = {0};
    
    // mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    mt19937 mt(1);
    using ptr = struct Node*;
    
    struct Node {
        Lazy lazy;
    
        int key;
        int pri;
        ptr l, r;
    
        Node() {
            pri = mt();
            lazy = lid;
            l = r = nullptr;
        }
    
        Node(int key) : key(key) {
            pri = mt();
            lazy = lid;
            l = r = nullptr;
        }
    };
    
    void push(ptr n) {
        if (!n) return;
        n->key += n->lazy.kval;
        if (n->l) n->l->lazy += n->lazy;
        if (n->r) n->r->lazy += n->lazy;
        n->lazy = lid;
    }
    
    ptr pull(ptr n) {
        if (!n) return nullptr;
        push(n->l), push(n->r);
        return n;
    }

        // [-inf, k) and [k, inf]
    pair<ptr, ptr> split(ptr n, int k) {
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
    
    ptr merge(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        if (l->pri > r->pri) return l->r = merge(l->r, r), pull(l);
        else return r->l = merge(l, r->l), pull(r);
    }
    
    ptr mn(ptr n) {
        if (!n) return nullptr;
        push(n);
        return n->l ? mn(n->l) : n;
    }

    // returns root of new treap
    ptr del(ptr n, int k) {
        if (!n) return nullptr;
        push(n);
        if (n->key == k) return merge(n->l, n->r);
        if (k <= n->key) n->l = del(n->l, k);
        else n->r = del(n->r, k);
        return pull(n);
    }

    // proof of complexity: https://codeforces.com/blog/entry/108601
    ptr unite(ptr l, ptr r) {
        if (!l || !r) return l ? l : r;
        push(l), push(r);
        if (mn(l)->key > mn(r)->key) swap(l, r);
        ptr res = 0;
        while (r) {
            auto [lt, rt] = split(l, mn(r)->key + 1);
            res = merge(res, lt);
            tie(l, r) = make_pair(r, rt);
        }
        return merge(res, l);
    }
}

// generated at caterpillow.github.io/byot

namespace Treap2 {

    struct Lazy {
        int val1, val2;
    
        void operator+=(const Lazy& oth) {
            val1 += oth.val1;
            val2 += oth.val2;
        }
    };
    
    const Lazy lid = {0, 0};
    
    // You can implement your own monoid here for custom operations.
    struct Value {
        pi mn; // min node, index
    
        void upd(Lazy lazy, int sz) {
            mn.f += lazy.val1;
            mn.s += lazy.val2;
        }
    
        Value operator+(const Value& oth) const {
            Value res {};
            res.mn = min(mn, oth.mn);
            return res;
        }
    };
    
    const Value vid = {{inf, inf}};
    
    // mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    mt19937 mt(1);
    using ptr = struct Node*;
    
    struct Node {
        Value val;
        Value agg;
        Lazy lazy;

        Treap::ptr treap;
    
        int sz;
        int pri;
        ptr l, r;
    
        Node(Treap::ptr treap, int i) : treap(treap) {
            int kval = Treap::mn(treap)->key;
            val = {{kval, i}};
            agg = val;
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

    template <typename Op>
    void tour(ptr n, Op op) {
        if (!n) return;
        tour(n->l, op);
        op(n);
        tour(n->r, op);
    }
}