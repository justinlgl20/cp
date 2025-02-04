#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> g) {
    int a = g.size();
    os << "{";
    for (auto i : g) {
        os << i << (--a?", ":"}");
    }
    return os;
}

void _print() {
    cerr << "]\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t;
    if (sizeof...(v)) cerr <<", ";
    _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " " << "[" << #x << "] = ["; _print(x); cerr << "\e[39m";
#else
#define dbg(x...)
#endif

struct Update {
    ll v;
    bool inc;
    void prop(const Update &b, int l, int r, int nl, int nr) {
        // be careful around "empty" lazy tags that might overwrite one below
        if (b.inc) {
            v += b.v;
        } else {
            v = b.v;
            inc = false;
        }
    }
};
 
struct Node {
    ll mx;
    ll sum;
    Node operator+(const Node &b) {
        return {min(mx, b.mx), sum + b.sum};
    }
    void upd(const Update &u, int l, int r) {
        // careful about "empty" lazy tags
        if (u.inc) {
            mx += u.v;
            sum += u.v * (r - l);
        } else {
            mx = u.v;
            sum = u.v * (r - l);
        } 
    }
};
 
template<class T, class U, int SZ> struct LazySeg {
    vector<T> seg;
    vector<U> lazy;
    T NID;
    U UID;
    LazySeg(T INIT, T _NID, U _UID) { // initial value, identity value,
        NID = _NID;
        UID = _UID;
        seg.resize(2 * SZ, INIT);
        lazy.resize(2 * SZ, UID);
        build();
    }
    void pull(int i) {
        seg[i] = seg[2 * i] + seg[2 * i + 1];
    }
    void push(int i, int l, int r) {
        seg[i].upd(lazy[i], l, r);
        if (r - l > 1) {
            int m = (l + r) / 2;
            lazy[2 * i].prop(lazy[i], l, r, l, m);
            lazy[2 * i + 1].prop(lazy[i], l, r, m + 1, r);
        }
        lazy[i] = UID;
    }
    void build() {
        for (int i = SZ - 1; i > 0; i--) pull(i);
    }
    void upd(int lo, int hi, U val, int i = 1, int l = 0, int r = SZ- 1) {
        push(i, l, r);
        if (r < lo || l > hi) return;
        if (lo <= l && r <= hi) {
            lazy[i].prop(val, lo, hi, l, r);
            push(i, l, r);
            return;
        }
        int m = (l + r) / 2;
        upd(lo, hi, val, 2 * i, l, m);
        upd(lo, hi, val, 2 * i + 1, m + 1, r);
        pull(i);
    }
    T query(int lo = 0, int hi = SZ - 1, int i = 1, int l = 0, int r = SZ - 1) {
        push(i, l, r);
				if (r < lo || l > hi) return NID;
				if (lo <= l && r <= hi) return seg[i];
				int m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m + 1, r);
    }
};

LazySeg<Node, Update, 1 << 20> tree({INF, 0}, {-INF, 0}, {0, true});

// tree.update(0, 5, {1, true}); // increment [0, 5] by 1
// tree.query(2, 3).sum; // sum of range [2, 3]

int32_t main() {
	int d, t, w; cin >> d >> t >> w;
	vector<pair<int,pii>> guards(t);
	vector<pair<int,pii>> towers(w);
	for(int i=0;i<t;i++)cin>>guards[i].f>>guards[i].s.f>>guards[i].s.s;
	for(int i=0;i<w;i++)cin>>towers[i].f>>towers[i].s.f>>towers[i].s.s;
	int inx=0,inx2=0;
	for(int _=0;_<t+w;_++){
		if(inx==t){
			tower:
			int u=towers[inx2].s.f, c=towers[inx2].s.s;
			int best=tree.query(0,c);
			tree.upd
			inx2++;
		} else if(inx2==w){
			guard:
			guards[inx];
			inx++;
		} else if(guards[inx].f<towers[inx2].f){
			goto guard;
		} else {
			goto tower;
		}
	}

}
