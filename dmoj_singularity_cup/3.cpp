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



#define pii pair<int, int>
#define f first
#define s second

bool can[1000005];
vector<int> adj[1000005];
int dist[1000005];
int backdist[1000005];

int main() {
    int N, M, P;
    vector<int> dists;
    cin >> N >> M >> P;
    int start = 0;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        dist[i+1] = x;
        if (i == P-1) start = x;
        else dists.push_back(x);
    }
    vector<pii> right, left;
    for (int i = 0; i < N; i++) {
        can[i+1] = true;
        backdist[i+1] = start-dist[i+1];
        if (dists[i] < start) left.emplace_back(start-dists[i], i+1);
        else right.emplace_back(dists[i], i+1);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        can[a] = false;
        adj[b].push_back(a);
    }
    //sort(dists.begin(), dists.end());
    int lo = 0;
    int hi = 10;
    while (lo != hi-1) {
        int c = (lo+hi)/2;
        bool works = true;
        //going right
        vector<int> allow(N+2, 0);
        for (int i = 0; i <= N; i++) allow[i] = can[i];
        int l = start;
        int r = start;
        set<pii> allowed_right;
        set<pii> allowed_left;
        for (auto i : left) if (can[i.s]) allowed_left.insert(i);
        for (auto i : right) if (can[i.s]) allowed_right.insert(i);
        int furthest_right = start;
        int furthest_left = 0;
        vector<bool> seen(N+2, 0);
        seen[P] = true;
        for (auto i : adj[start]) can[i] = true;
        while (allowed_right.size() and allowed_left.size()) {
            if (allowed_right.size() and (*(right.begin())).s - furthest_right <= c) {
                auto q = *(right.begin());
                dbg("RIGHT: ", q);
                right.erase(right.begin());
                furthest_right = max(furthest_right, q.f);
                seen[q.s] = true;
                for (int i : adj[q.s]) {
                    assert(!seen[i]);
                    if (dist[i] < start) allowed_left.insert(make_pair(backdist[i], i));
                    else allowed_right.insert(make_pair(dist[i], i));
                }
            }
            else if (allowed_left.size() and (*(left.begin())).s - furthest_left <= c) {
                auto q = (*left.begin());
                dbg("LEFT: ", q);
                left.erase(left.begin());
                furthest_left = max(furthest_left, q.f);
                seen[q.s] = true;
                for (int i : adj[q.s]) {
                    assert(!seen[i]);
                    if (dist[i] < start) allowed_left.insert(make_pair(backdist[i], i));
                    else allowed_right.insert(make_pair(dist[i], i));
                }
            } else {
                works = false;
                break;
            }
            
        }
        dbg(c, works);
        dbg(furthest_left, furthest_right);
        for (int i = 1; i <= N; i++) works = works&seen[i];
        if (works) hi = c;
        else lo = c;
    }
    cout << hi << "\n";
}
