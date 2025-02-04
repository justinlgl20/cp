#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

#define int long long

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> o) {
        os << "{"; int g = o.size(); for (auto i : o) os << i << ((--g)==0?"":", "); os << "}";
    return os;
}

void _print() {
        cout << "]\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
        cerr << t; if (sizeof...(v)) cerr << ", "; _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" <<__func__ << ":" <<__LINE__ << " [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int nxt() {
    int g; cin >> g; return g;
}

int n, q;
int l[25005], r[25005], a[25005];

// SEGTREE WORKS
struct seg {
    vector<int> t;
    vector<int> v;
    seg() {
        t.resize(4*n+3);
        v.resize(4*n+3);
        for (int i = 0; i < 4*n+2; i++) t[i] = 0;
        for (int i = 0; i < 4*n+2; i++) v[i] = 0;
    }
    void update(int ql, int qr, int i = 1, int tl = 1, int tr = n) {
        if (ql > tr or tl > qr) return;
        if (ql <= tl and tr <= qr) {
            t[i] = 1;
            v[i] = (tr-tl+1);
            return;
        }
        if (t[i] == 1) return;
        int tm = (tl+tr)>>1ll;
        update(ql, qr, i*2, tl, tm);
        update(ql, qr, i*2+1, tm+1, tr);
        v[i] = v[i*2]+v[i*2+1];
    }
    int query(int ql, int qr, int i = 1, int tl = 1, int tr = n) {
        if (ql <= tl and tr <= qr) {
            return v[i];
        }
        if (ql > tr or tl > qr) return 0;
        if (t[i] == 1) {
            return min(qr, tr) - max(ql, tl) + 1;
        }
        int tm = (tl+tr)>>1;
        return query(ql, qr, i*2, tl, tm) + query(ql, qr, i*2+1, tm+1, tr);
    }
};

pii qw[1000005];

bool works(int x) { // getting false negative
    vector<pair<int, pii>> ranges;
    set<int> s;
    for (int i = 0; i <= x; i++) {
        s.insert(a[i]);
        if (1e9 - a[i] < r[i]-l[i]) {
            return false;
        }
        ranges.push_back(make_pair(a[i], make_pair(l[i], r[i])));
    }
    sort(all(ranges));
    reverse(all(ranges));
    vector<pair<int, pii>> range;
    // all elements are also unique so ranges with same a[i] must overlap and can be condensed to that overlap
    int q = ranges[0].s.f, b = ranges[0].s.s;
    int w = ranges[0].s.f, e = ranges[0].s.s;
    for (int i = 1; i <= x; i++) {
        if (ranges[i].f == ranges[i-1].f) {
            q = max(q, ranges[i].s.f);
            w = min(w, ranges[i].s.f);
            b = min(b, ranges[i].s.s);
            e = max(e, ranges[i].s.s);
        } else {
            if (q > b) {
                return false;
            }
            qw[range.size()] = make_pair(w, e);
            range.push_back(make_pair(ranges[i-1].f, make_pair(q, b)));
            q = ranges[i].s.f;
            b = ranges[i].s.s;
            w = ranges[i].s.f;
            e = ranges[i].s.s;
        }
    }
    if (q > b) return false;
    qw[range.size()] = make_pair(w, e);
    range.push_back(make_pair(ranges[x].f, make_pair(q, b)));
    assert(range.size() == s.size());
    // EVERYTHING ABOVE HERE IS FINE

    sort(all(range));
    reverse(all(range));
    // put down ranges with largest int first
    // if a range overlaps with what has previously been placed down, those spots can't be the smaller range
    // must all be different
    // smaller range cannot be contained within bigger ranges
    // can use range set segtree for that
    seg tree = seg();

    for (int j = 0; j < range.size(); j++) {
        pair<int, pii> i = range[j];
        int g = tree.query(i.s.f, i.s.s);
        if (g == i.s.s-i.s.f+1) {
            return false;
        }
        tree.update(qw[j].f, qw[j].s);
    }
    return true;


}

int32_t main() { // OVERREPORTING ANSWER
    cin >> n >> q;
    for (int i = 0; i < q; i++) {
        cin >> l[i] >> r[i] >> a[i];
    }
    /*l[q] = 1;
    r[q] = n;
    a[q] = 1e9;*/
    int ans = 1;
    for (int i = 30; i >= 0; i--) {
        if (ans + (1ll<<i) <= q and works(ans+(1ll<<i) - 1ll)) {
            ans += (1ll<<i);
        }
    }
    if (ans == q) {
        cout << "0\n";
        return 0;
    }
    cout << ans+1 << "\n";
}
