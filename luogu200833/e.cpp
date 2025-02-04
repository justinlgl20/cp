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

struct trie {
    trie *l, *r; // l is 0, r is 1
    int val, under;
    int lazy;
    void push() {
        if (lazy) {
            if (lazy&1) {
                swap(l, r);
            }
            if (!l) l = new trie();
            l->lazy += lazy>>1;
            if (!r) r = new trie();
            r->lazy += lazy>>1;
        }
    }
    trie() {
        this->l = NULL;
        this->r = NULL;
        val = 0;
        under = 0;
        lazy = 0;
    }
    void add(int i, int x) {
        push();
        if (x == 0) {
            val += 1;
            under += 1;
            return;
        }
        if (i&1) {
            if (r == NULL)
                r = new trie();
            r->add(i>>1, x-1);
        } else {
            if (l == NULL) 
                l = new trie();
            l->add(i>>1, x-1);
        }
        under = val;
        if (l != NULL) under += l->under;
        if (r != NULL) under += r->under;
    }
    void remove(int i, int x) {
        push();
        if (x == 0) {
            val -= 1;
            under -= 1;
            return;
        }
        if (i&1) {
            if (r == NULL)
                r = new trie();
            r->remove(i>>1, x-1);
        } else {
            if (l == NULL) 
                l = new trie();
            l->remove(i>>1, x-1);
        }
        under = val;
        if (l != NULL) under += l->under;
        if (r != NULL) under += r->under;
    }
    int query(int x) {
        push();
        if (l) l->push();
        if (r) r->push();
        if (x&1 and r!=NULL and r->under > 0) {
            return 1+r->query(x>>1);
        } else if ((!(x&1)) and l!=NULL and l->under > 0) {
            return 1+l->query(x>>1);
        } else if (x&1 and (r==NULL or r->under <= 0)){
            return 0ll;
        } else if ((!(x&1)) and (l==NULL or l->under <= 0)) {
            return (int)0ll;
        }
    }
    void print(int x) {
        dbg(val, under, x);
        if (l != NULL) {
        dbg("0");
        l->print(x+1);
        }
        if (r != NULL) {
        dbg("1");
        r->print(x+1);
        }
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    trie x = trie();
    int q; cin >> q;
    multiset<int> s;
    while (q--) {
        int opt; cin >> opt;
        if (opt == 1) {
            int a; cin >> a;
            x.add(a, 32);
            s.insert(a);
        } else if (opt == 4) {
            int a; cin >> a;
            /*if (s.find(a) != s.end()) {
                cout << (1ll<<32) << "\n";
                continue;
            }*/
            cout << (1ll<<(x.query(a))) << "\n";
        } else if (opt == 2) {
            int a; cin >> a;
            x.remove(a, 32);
            s.erase(s.find(a));
        } else if (opt == 3) {
            int w, k, v; cin >> w >> k >> v;
            // just add v thats it
            x.lazy += v;
        }
    }
}
