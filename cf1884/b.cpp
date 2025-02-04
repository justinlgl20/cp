#include <bits/stdc++.h>
using namespace std;


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


#define int long long

void solve() {
    int n; cin >> n;
    vector<int> a(2*n+1, 0);
    int biggest_bit = -1;
    for (int i = n-1; i >= 0; i--) { char g; cin >> g; a[i] = g=='1';}
    int ones = 0;
    for (int i = 0; i < n; i++) ones += a[i];
    int block_sz = 0;
    int inx = 0;
    while (inx < n and a[inx]) {block_sz ++; inx++;}
    int cost = 0;
    dbg(ones);
    for (int i = 1; i <= n-ones; i++) {
        //need to move things in block_sz over 1
        //a[i-1+block_sz] should be 0
        //dbg(i, block_sz);
        assert(i-1+block_sz < n);
        assert(a[i-1+block_sz] == 0);
        cost += block_sz;
        int inx = i+block_sz;
        while (a[inx]) {block_sz++; inx++;}
        cout << cost << " \n"[i==n];
    }
    for (int i = n-ones+1; i <= n; i++) cout << -1 << " \n"[i==n];

}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
