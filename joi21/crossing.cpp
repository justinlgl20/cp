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
    int x; cin >> x; return x;
}

int n;

vector<int> do_the_thing(vector<int> a, vector<int> b) {
    vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = ((a[i]+b[i])*2)%3;
    return ans;
}

unordered_map<char, int> to;
unordered_map<int, char> from;

vector<vector<int>> goot;

void stuff() {
    goot.push_back(do_the_thing(goot[0], goot[1]));
    goot.push_back(do_the_thing(goot[1], goot[2]));
    goot.push_back(do_the_thing(goot[0], goot[2]));
    goot.push_back(do_the_thing(goot[0], do_the_thing(goot[1], goot[2])));
    goot.push_back(do_the_thing(goot[1], do_the_thing(goot[0], goot[2])));
    goot.push_back(do_the_thing(goot[2], do_the_thing(goot[0], goot[1])));
}

vector<int> query;

struct seg {
    int tl, tr;
    vector<int> works;
    vector<int> colour;
    int lazy_set;
    int val;
    seg *l, *r;
    void push() {
        if (lazy_set == -1) return;
        if (tl == tr) {
            val = lazy_set;
            for (int i = 0; i < goot.size(); i++) {
                works[i] = val == goot[i][tl];
            }
        } else {
            for (int i = 0; i < goot.size(); i++) {
                works[i] = colour[i] == lazy_set;
            }
            l->lazy_set = lazy_set;
            r->lazy_set = lazy_set;
        }
        lazy_set = -1;
    }
    seg (int tl, int tr) {
        this->tl = tl;
        this->tr = tr;
        lazy_set = -1;
        works.resize(goot.size());
        colour.resize(goot.size());
        if (tl == tr) {
            val = query[tl]; 
            for (int i = 0; i < goot.size(); i++) {
                works[i] = val == goot[i][tl];
                colour[i] = goot[i][tl];
            }
            return;
        }
        int tm = (tl+tr)/2;
        l = new seg(tl, tm);
        r = new seg(tm+1, tr);
        for (int i = 0; i < goot.size(); i++) {
            works[i] = l->works[i] and r->works[i];
            if (l->colour[i] != r->colour[i]) colour[i] = -1;
            else colour[i] = l->colour[i];
        }
    }
    /*void update(int p, int val) {
        if (tl == tr) {
            this->val = val;
            for (int i = 0; i < goot.size(); i++) {
                works[i] = val == goot[i][tl];
            }
            return;
        }
        int tm = (tl+tr)/2;
        if (p <= tm) l->update(p, val);
        else r ->update(p, val);
        for (int i = 0; i < goot.size(); i++) {
            works[i] = l->works[i] and r->works[i];
        }
    }*/
    void update(int ql, int qr, int val) {
        if (tl > qr or tr < ql) return;
        if (ql <= tl and tr <= qr) {
            push();
            lazy_set = val;
            push();
            if (tl == tr) return;
            l->push();
            r->push();
            for (int i = 0; i < goot.size(); i++) {
                works[i] = l->works[i] and r->works[i];
            }
            return;
        }
        else {
            push();
            l->update(ql, qr, val);
            r->update(ql, qr, val);
        }
        l->push();
        r->push();
        for (int i = 0; i < goot.size(); i++) {
            works[i] = l->works[i] and r->works[i];
        }
    }
#ifdef DEBUG
    void print() {
        dbg(tl, tr, val, works, lazy_set);
        if (tl == tr) return;
        l->print();
        r->print();
    }
#else 
    void print(){}
#endif
};

int32_t main() {
    cin >> n;
    to['J'] = 0;
    to['O'] = 1;
    to['I'] = 2;
    from[0] = 'J';
    from[1] = 'O';
    from[2] = 'I';
    for (int i = 0; i < 3; i++) {
        vector<int> things;
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            things.push_back(to[c]);
        }
        goot.push_back(things);
    }
    stuff();
    dbg(goot);
    int q; cin >> q;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        query.push_back(to[c]);
    }
    dbg("HI");
    seg tree = seg(0, n-1);
    dbg("HI");
    auto check = [&]() {
        for (int i = 0; i < goot.size(); i++) {
            if (tree.works[i]) return true;
        }
        return false;
    };
    tree.print();
    if (check()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    while (q--) {
        int l, r; char c; cin >> l >> r >> c;l--,r--;
        tree.update(l, r, to[c]);
        tree.print();
        if (check()) cout << "Yes\n";
        else cout << "No\n";
    }
}
