#include <bits/stdc++.h>
using namespace std;
 
 
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

/*
namespace FastIO {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p1 = buf, p2 = (p1 + fread(buf, 1, 1 << 21, stdin))) == p1 ? EOF : *p1++)
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar((x % 10) ^ '0'); }
	template <typename T> inline void print(T x) { if (x > 0) write<T>(x); else if (x < 0) putchar('-'), write<T>(-x); else putchar('0'); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; 
using namespace FastIO;
#undef getchar()*/

int cnt = 1;

const int qwe = (1ll<<23)+5;

int s[qwe], ch[qwe][2];
stack<int> use;
int new_node() {
    if (use.size()) {
        int g = use.top();
        s[g] = 0;
        ch[g][0] = 0;
        ch[g][1] = 0;
        use.pop();
        dbg(g);
        return g;
    }
    assert(cnt <= qwe);
    return cnt++;
}

void build(int& x, int l, int r, int v) {
    x = new_node(); 
    s[x]+=1;
    if (l==r) return;
    int m = (l+r)>>1ll;
    if (v <= m)
        build(ch[x][0], l, m, v);
    else
        build(ch[x][1], m+1, r, v);
}

void add(int &x, int l, int r, int v) {
    if (x == 0) x = new_node();
    s[x] += 1;
    if (l == r) return;
    int m = (l+r)>>1ll;
    if (v <= m)
        add(ch[x][0], l, m, v);
    else
        add(ch[x][1], m+1, r, v);

}

void split(int t1, int& t2, int k) {
    t2 = new_node();
    int ls = s[ch[t1][0]];
    if (k > ls) split(ch[t1][1], ch[t2][1], k-ls);
    else swap(ch[t1][1], ch[t2][1]);
    if (k < ls) split(ch[t1][0], ch[t2][0], k);
    s[t2] = s[t1]-k;
    s[t1] = k;
}

int merge(int t1, int t2) {
    if (t1 == 0 or t2 == 0) return t1^t2;
    ch[t1][0] = merge(ch[t1][0], ch[t2][0]);
    ch[t1][1] = merge(ch[t1][1], ch[t2][1]);
    s[t1] += s[t2]; // t2 is nothing now;
    use.push(t2);
    return t1;
}

int query(int x, int l, int r, int k) {
    if (l == r) return l;
    int ls = s[ch[x][0]];
    int m = (l+r)>>1ll;
    if (k > ls) return query(ch[x][1], m+1, r, k-ls);
    return query(ch[x][0], l, m, k);
}

void print(int x, int tl, int tr) {
    return;
    if (tl == tr) {
        dbg(x, ch[x][0], ch[x][1], s[x], tl, tr);
        return;
    }
    int tm = (tl+tr)>>1ll;
    if (ch[x][0]) print(ch[x][0], tl, tm);
    if (ch[x][1]) print(ch[x][1], tm+1, tr);
}

vector<int> roots;
const int MAX = 1ll<<21;
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q; cin >> n >> m >> q;
    roots.resize(m+4);
    vector<vector<int>> a(m+4, vector<int>(n+3, 0));
    multiset<pair<int, pii>> g;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            a[i][j+1] = x;
            g.insert(make_pair(x, make_pair(i, j+1)));
        }
    }
    int cnt = 1;
    vector<int> unmap(g.size()+4, 0);
    for (auto i : g) {
        a[i.s.f][i.s.s] = cnt;
        unmap[cnt] = i.f;
        cnt++;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int x = a[i][j+1];
            if (j == 0) {
                int g = 0;
                build(g, 0, MAX, x);

                roots[i] = g;
            }else {
                add(roots[i], 0, MAX, x);
                //dbg("A");
                ///print(g, 1, MAX);
                //dbg("B");
                //print(roots[i], 1, MAX);
                //roots[i] = merge(roots[i], g);
                //dbg("A+B");
                //print(roots[i], 1, MAX);

            }
        }
    }
    vector<int> had_op_1(m+4, 0);
    for (int i = 0; i < q; i++) {
        int x; cin >> x;
        if (x == 1) {
            int x, y; cin >> x >> y;
            x--, y--;
            had_op_1[x] = 1;
            had_op_1[y] = 1;
            roots[x] = merge(roots[x], roots[y]);
            split(roots[x], roots[y], n);
        }
        else {
            int i, j; cin >> i >> j; 
            i--;
            if (had_op_1[i]) {
                int ans = query(roots[i], 0, MAX, j);
                cout << unmap[ans] << "\n";
            } else {
                cout << unmap[a[i][j]] << "\n";
            }
        }
    }
}
