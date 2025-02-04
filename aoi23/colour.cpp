#include <bits/stdc++.h>
using namespace std;
 
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optmize("unroll-loops")
#pragma GCC target("avx2")
 
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif
 
int n;
int get_tree_val(int i, int no);
struct maxtree {
    int big[1048576];
    int no;
    maxtree(int no) {       
        //for (int i = n; i > 0; i--) big[i] = -1e9, small[i] = 1e9;
        this->no = no;
    }
    void build(int tl = 1, int tr = n, int u = 1) {
        if (tl == tr) {
            big[u] = get_tree_val(tl, no);
            return;
        }
        int mid = (tl+tr)/2;
        build(tl, mid, 2*u);
        build(mid+1, tr, 2*u+1);
        big[u] = max(big[2*u], big[2*u+1]);

    }
    void set(int p, int v, int tl = 1, int tr = n, int u = 1) {
        if (tl == tr) { big[u] = v; return; }
        int mid = (tl+tr)/2;
        if (p <= mid) set(p, v, tl, mid, 2*u);
        else set(p, v, mid+1, tr, 2*u+1);
        big[u] = max(big[2*u], big[2*u+1]);
    }
    int left(int l, int r, int val, int tl = 1, int tr = n, int v = 1) { // return first pos in l, r that is bigger than val
        if (l > tr or r < tl) return r;
        if (l <= tl and tr <= r) {
            if (big[v] <= val) return r;
            while (tl != tr) {
                int mid = tl+(tr-tl)/2;
                if (big[2*v] > val) {
                    v = 2*v;
                    tr = mid;
                } else {
                    v = 2*v+1;
                    tl = mid+1;
                }
            }
            return tl-1;
        }
        int mid = tl+(tr-tl)/2;
        int rs = left(l, r, val, tl, mid, 2*v);
        if (rs != r) return rs;
        return left(l, r, val, mid+1, tr, 2*v+1);
    }
 
    int right(int l, int r, int val, int tl = 1, int tr = n, int v = 1) { // return first pos in l, r that is bigger than val
        if (l > tr or r < tl) return l;
        if (l <= tl and tr <= r) {
            if (big[v] <= val) return l;
            while (tl != tr) {
                int mid = tl+(tr-tl)/2;
                if (big[2*v+1] > val) {
                    v = 2*v+1;
                    tl = mid+1;
                } else {
                    v = 2*v;
                    tr = mid;
                }
            }
            return tl+1;
        }
        int mid = tl+(tr-tl)/2;
        int rs = right(l, r, val, mid+1, tr, 2*v+1);
        if (rs != l) return rs;
        return right(l, r, val, tl, mid, 2*v);
    }
 
};
 
maxtree *tree[8];
// a is 000, b is 001 etc
 
 
int r[524288];
int g[524288];
int b[524288];
int get_tree_val(int i, int no) {
    int ans = 0;
    ans += ((no&(1 << 0))==0?-1:1)*r[i];
    ans += ((no&(1 << 1))==0?-1:1)*g[i];
    ans += ((no&(1 << 2))==0?-1:1)*b[i];
    return ans;
}
int get_right(int l, int r, int d) {
    int right = 1e9;
    for (int i = 0; i < 8; i++) {
        right = min(right, tree[i]->left(l, r, d+get_tree_val(0, i)));
    }
    return right;
}
 
int get_left(int l, int r, int d) {
    int left = -1e9;
    for (int i = 0; i < 8; i++) {
        left = max(left, tree[i]->right(l, r, d+get_tree_val(0, i)));
    }
    return left;
}
 
 
int32_t main() {
#ifndef DEBUG
    freopen("colourin.txt", "r", stdin);
    freopen("colourout.txt", "w", stdout);
#endif
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < 8; i++) tree[i] = new maxtree(i);
    for (int i = 1; i <= n; i++) {
        cin >> r[i] >> g[i] >> b[i];    
    }
    
    for (int i=  0; i < 8; i++) tree[i]->build();
    int q, u; cin >> q >> u;
    for (int i = 0; i < q+u; i++) {
        char v; cin >> v;
        if (v == 'u') {
            int pos;
            cin >> pos;
            cin >> r[pos] >> g[pos] >> b[pos];
            for (int j = 0; j < 8; j++) {
                tree[j]->set(pos, get_tree_val(pos, j));
            }
        }
        else if (v == 'q') {
            cin >> r[0] >> g[0] >> b[0];
            int p, d; cin >> p >> d;
            int ans = 0;
            if (abs(r[p]-r[0])+abs(b[p]-b[0])+abs(g[p]-g[0]) <= d) {
                //bsearch right;
                cout << get_right(p, n, d)-get_left(1, p, d)+1 << "\n";
 
            } else cout << ans << "\n";
        }
    }
}
