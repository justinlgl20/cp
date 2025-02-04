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

//#define int long long

#define pii pair<int, int>
#define f first
#define s second

struct line
{
    int m, c;
    pii id;
    line(int am = 0, int ac = 0, pii g = {0, 0})
    {
        m = am;
        c = ac;
        id = g;
    }
    int get(int x)
    {
        return m * x + c;
    }
};
 
// max li chao tree
struct node
{
    int tl, tr;
    line li;
    node *left, *right;
    node(int atl, int atr, line lin = line(0, 0, {0, 0}))
    {
        tl = atl;
        tr = atr;
        left = right = nullptr;
        li = lin;
    }
    void add_line(line l)
    {
        int mid = (tl + tr) / 2;
        if (li.get(mid) < l.get(mid))
            swap(li, l);
        if (tl + 1 == tr or (li.get(tl) >= l.get(tl) and li.get(tr - 1) >= l.get(tr - 1))) // leaf or out
            return;
        if (li.get(tl) > l.get(tl))
        {
            if (!right)
            {
                right = new node(mid, tr, l);
            }
            else
            {
                right->add_line(l);
            }
        }
        else
        {
            if (!left)
            {
                left = new node(tl, mid, l);
            }
            else
            {
                left->add_line(l);
            }
        }
    }
    pair<int, pii> query(int x)
    {
        pair<int, pii> ans = {li.get(x), li.id};
        // cout << li.m << " " << li.c << "\n";
        if (left and x <= (tl + tr) / 2)
            ans = max(ans, left->query(x));
        if (right and x > (tl + tr) / 2)
            ans = max(ans, right->query(x));
        return ans;
    }
    void print() {
        dbg(li.m, li.c, li.id);
        if (left) left->print();
        if (right) right->print();
    }
};


int psa[100005];

int sum(int l, int r) {
    return psa[r] - psa[l-1];
}

int dp[100005][205];
pii from[100005][205];

line lines[100005][205];

int32_t main() {
#ifndef DEBUG
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> psa[i];
        psa[i] += psa[i-1];
    }
    for (int j = 1; j <= K+1; j++) {
        node *lichao = new node(0, 100005);
        for (int i = 1; i <= N; i++) {
            /*for (int k = 0; k < i; k++) {
                dp[i][j] = max(dp[i][j], lines[k][j-1].get(psa[N]-psa[i]));
                //if (dp[k][j-1]+(-psa[k])*(psa[N]-psa[i]) > dp[i][j])
            }*/
            dp[i][j] += psa[i]*(psa[N]-psa[i]);
            lines[i][j].m = -psa[i];
            lines[i][j].c = dp[i][j];
            lines[i][j].id = {i, j};
            lichao->add_line(lines[i][j]);
            auto g = lichao->query(psa[N]-psa[i+1]);
            //dbg(g);
            dp[i+1][j+1] = g.f;
            from[i+1][j+1] = g.s;
            dbg(i+1, j+1, from[i+1][j+1]);
            dbg(i, j, dp[i][j]);
        }
        //dbg(j);
        //lichao->print();
    }
    int ans = dp[N][K+1];
    cout << ans << "\n";
    pii curr = from[N][K+1];
    int last = K+1;
    for (int i = 0; i < K; i++) {
        if (curr.s != last)
            cout << curr.f << " ";
        curr = from[curr.f][curr.s];
    }
    cout << "\n";
}
