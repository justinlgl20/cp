#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

ostream& operator<<(ostream& os, pair<int, int> x) {
    os << "(" << x.first << " " << x.second << ")";
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

#define pii pair<int, int>
#define f first
#define s second

int dp[200005];
const int MOD = 1000000007;
const int INVERSE2 = 500000004;

int solve(vector<pii> ranges) {
    int ans = 0;
    unordered_set<int> ends;
    for (auto i : ranges) {
        if (ends.size() and (*ends.begin()) < i.f) {
            ends.clear();
            ans++;
        }
        ends.insert(i.s);
    }
    if (ends.size()) ans++;
    return ans;
}

// needs range multiply, point set, range query
struct node {
    int tl, tr, val, lazy;
};
node tree[800004];

void push(int n) {
    if (tree[n].lazy == 1) return;
    tree[n].val *= tree[n].lazy;
    tree[n].val %= MOD;
    if (tree[n].tl == tree[n].tr) {tree[n].lazy = 1; return;}
    tree[2*n].lazy *= tree[n].lazy;
    tree[2*n].lazy %= MOD;
    tree[2*n+1].lazy *= tree[n].lazy;
    tree[2*n+1].lazy %= MOD;
    tree[n].lazy = 1;
}

void build(int tl=0, int tr=200000, int n = 1) {
    tree[n].tl = tl;
    tree[n].tr = tr;
    tree[n].val = 0;
    tree[n].lazy = 1;
    if (tl == tr) return;
    int tm = (tl+tr)/2;
    build(tl, tm, n*2);
    build(tm+1, tr, n*2+1);
}
void upd(int ql, int qr, int v, int n = 1, int tl = 0, int tr = 200000) {
    push(n);
    if (ql <= tl and tr <= qr) {
        tree[n].lazy = v;
        push(n);
        return;
    }
    if (ql > tr or tl > qr) return;
    int tm = (tl+tr)/2;
    upd(ql, qr, v, n*2, tl, tm);
    upd(ql, qr, v, n*2+1, tm+1, tr);
    push(n*2); push(n*2+1);
    tree[n].val = tree[n*2].val + tree[n*2+1].val;
    tree[n].val %= MOD;
}
int query(int ql, int qr, int n = 1, int tl = 0, int tr = 200000) {
    push(n);
    if (ql <= tl and tr <= qr) return tree[n].val;
    if (ql > tr or tl > qr) return 0;
    int tm = (tl+tr)/2;
    return (query(ql, qr, n*2, tl, tm) + query(ql, qr, n*2+1, tm+1, tr))%MOD;
}
void upd_point(int p, int v, int n = 1, int tl = 0, int tr = 200000) {
    push(n);
    if (tl == tr) {
        tree[n].val = v;
        tree[n].val %= MOD;
        return;
    }
    int tm = (tl+tr)/2;
    if (p <= tm) upd_point(p, v, n*2, tl, tm);
    else upd_point(p, v, n*2+1, tm+1, tr);
    push(n*2); push(n*2+1);
    tree[n].val = tree[n*2].val + tree[n*2+1].val;
    tree[n].val %= MOD;
}

struct seg {
    vector<int> t;
    int n;
    seg(int x) {
        n = 1;
        while (n <= x) n *= 2;
        t.resize(n*3+2);
        for (int i = 0; i < n*3+2; i++) t[i] = 0;
        for (int i = 0; i < n; i++) upd(i, 1);
    }
    void upd(int p, int v) {
        for (t[p+=n] = v; p > 1; p>>=1) t[p>>1] = t[p] + t[p^1];
    }
    int query(int l, int r) {
        int ans = 0;
        for(l += n, r+= n+1; l < r; l>>=1, r>>=1) {
            if (l&1) ans += t[l++];
            if (r&1) ans += t[--r];
        }
        return ans;
    }
};

int32_t main() {
    int n; cin >> n;
    seg note = seg(n+3);
    build();
    vector<pii> ranges(n);
    for (int i = 0; i < n; i++) cin >> ranges[i].f >> ranges[i].s;
    sort(all(ranges), [&](auto i, auto j) {
        return i.s < j.s;
    });
    vector<int> powers(n+4, 0), INVPOWERS(n+4, 0);
    powers[0] = 1;
    INVPOWERS[0] = 1;
    for (int i = 1; i <= n; i++) {
        powers[i] = 2*powers[i-1];
        powers[i] %= MOD;
        INVPOWERS[i] = INVERSE2*INVPOWERS[i-1];
        INVPOWERS[i] %= MOD;
    }
    priority_queue<pii> q;
    for (int i = n-1; i >= 0; i--) {
        int s = ranges[i].f, e = ranges[i].s;
        int k = 0;
        while (q.size() and q.top().f > e) {
            int i = q.top().s;
            note.upd(i, 0);
            dbg(i, note.query(0, i-1));
            q.pop();
            // ADD i into segtree with pos of ranges[i].s and value of dp[i] * 2**(note.query(0, i-1));
            int v = dp[i]*powers[note.query(0, i-1)];
            v %= MOD;
            dbg("UPD", i, v);
            dbg(tree[1].val);
            upd_point(i, v);
            // divide everything above i by 2
            dbg(tree[1].val);
            upd(i+1, n, INVERSE2);
            dbg("DIVIDE EVERYTHING ABOVE i BY 2");
        }
        int cursum = 0;
        
        /*for (int j = i+1; j < n; j++) {
            if (ranges[j].f <= e) {
                k++;
            } else {
                cursum += dp[j]*powers[k];
                cursum %= MOD;
            }
        }*/
        // cursum = segtree query (all) sum / (2**i)
        push(1); // CURSUM IS TOO BIG IS THE ISSUE
        int cursum2 = tree[1].val * INVPOWERS[i+1];
        cursum2 %= MOD;
        dbg(cursum2, tree[1].val, tree[1].val / pow(2, i+1), INVPOWERS[i+1], i+1);
        
        dp[i] = cursum2 + powers[n-1-i];
        dp[i] %= MOD;

        q.push(make_pair(s, i));
        // n-i
        dbg(s, e, dp[i], cursum, cursum2);
    }
    int ans = 0;
    for (int i = 0; i < n; i++) ans += dp[i];
    ans %= MOD;
    cout << ans << "\n";
}
