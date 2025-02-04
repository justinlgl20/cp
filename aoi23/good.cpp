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
struct maxtree {
    vector<int> big;    
    maxtree(int tl, int tr) {
        big.resize(2*(tr+7));        
        //for (int i = n; i > 0; i--) big[i] = -1e9, small[i] = 1e9;
    }
    void idk(int i, int v) {
        big[n+1+i] = v;    
    }
    void init() {
        for (int i = n; i > 0; i--) big[i] = max(big[i<<1], big[i<<1|1]);
    }
    void set(int p, int v) {
        p += n+1;
        for (big[p] = v; p > 1; p >>= 1) {big[p>>1] = max(big[p], big[p^1]);}
    }
    int query(int l, int r) {
        r += 1;
        int high = -1e9;
        for (l+=n+1, r+=n+1; l < r; l>>=1, r>>=1) {
            if (l&1) {high=max(high, big[l++]);}
            if (r&1) {high=max(high, big[--r]);}
        }
        return high;
    }
};
 
maxtree *tree[8];
// a is 000, b is 001 etc
 
 
int r[500005];
int g[500005];
int b[500005];
int get_tree_val(int i, int no) {
    int ans = 0;
    ans += ((no&(1 << 0))==0?-1:1)*r[i];
    ans += ((no&(1 << 1))==0?-1:1)*g[i];
    ans += ((no&(1 << 2))==0?-1:1)*b[i];
    return ans;
}
int works(int l, int r, int d) {
    int big = -1e9;
    for (int i = 0; i < 8; i++) {
        auto q = tree[i]->query(l, r); 
        int g = get_tree_val(0, i);
        //looking for first position on wlog right where q.first/second - g > D
        //then take min pos then thats the answer
        big = max(big, q-g);
    }
    return big;
}
 
int32_t main() {
#ifndef DEBUG
    freopen("colourin.txt", "r", stdin);
    freopen("colourout.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < 8; i++) tree[i] = new maxtree(1, n);
    for (int i = 1; i <= n; i++) {
        cin >> r[i] >> g[i] >> b[i];
        for (int j = 0; j < 8; j++) {
            tree[j]->idk(i, get_tree_val(i, j));
            //dbg(r[i], g[i], b[i], j, get_tree_val(i, j));
            //dbg(j, get_tree_val(i, j), tree[j]->query(i, i));
        }
    }
    for (int j = 0; j < 8; j++) tree[j]->init();
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
                int right = p;
                for (int add = 1<<20; add > 0; add>>=1) {
                    //cerr << "CURRENTLY R IS AT " << right << " TRYING TO ADD " << add << "\n";
                    //dbg(p, right+add, n);
                    //cerr << "BIG VALUE = " << val<< "\n"; 
                    if (right+add <= n and works(p, right+add, d) <= d) right += add;//dbg("ADDED ", add);}
                }
                int left = p;
                for (int add = 1<<20; add > 0; add >>=1) {
                    //cerr << "CURRENTLY L IS AT " << left << " TRYING TO take " << add << "\n";
                    if (left-add > 0 and works(left-add, p, d) <= d) left -= add;
                }
                dbg(left, right);
                cout << right-left+1 << "\n";
 
            } else cout << ans << "\n";
        }
    }
}
