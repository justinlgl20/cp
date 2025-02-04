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
    vector<int> cnt(n+2, 0);
    vector<int> done(n+2, 0);
    vector<int> done_by(n+2, 0);
    set<int> stuff;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        cnt[a]+=1;
        stuff.insert(a);
        done[i] = false;
    }
    int ans = 1ll*n*(n-1ll)/((long long)2);
    for (auto i : stuff) {
        //issue is if its been done by 2, then a pair is removed which is done by 2 and 3
        dbg(i);
        if (done[i]) { continue;}
        int no = 0;
        int done_stuff = 0;
        unordered_map<int, int> idk;
        for (int j = i; j <= n; j+=i) {
            no += cnt[j];
            if (!done[j]) {
                done_by[j] = i;
                done[j] = true;
            } else {
                done_stuff += cnt[j];
            }
        }
        dbg(idk);
        int g = 1ll*no*(no-1ll)/((long long)2);
        g -= 1ll*((done_stuff)*(done_stuff-1ll))/((long long)2);
        assert(g >= 0);
        dbg(i, no, g);
        ans -= g;
    }
    cout << ans << "\n";
}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
