#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0ll; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
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

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int32_t main() {
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0ll;  i < n; i++) {cin >> p[i];p[i]--;}
    if (n < 10) {
        // BRUTE FORCE IT

    }
    multiset<int> gaps;
    int nopoints = 0ll, onepoints = 0ll;
    ordered_set poses;
    vector<int> gapl(n, -1);
    vector<int> gapr(n, -1);
    for (int i = 0ll; i < (int)n/2; i++) {
        poses.insert(p[i]);
    }
    int last = -1;
    for (auto i : poses) {
        dbg(i, last);
        if (last != -1)
            gapr[last] = i-last-1;
        gapl[i] = i-last-1;
        gaps.insert(i-last-1);
        last = i;
    }



    gaps.insert(n-last-1);
    gapr[last] = n-last-1;
    nopoints += (*gaps.rbegin()) >= (int)n/2;

    for (int i = 0; i < n; i++) {
        dbg(i, gapl[i], gapr[i]);
    }

    function<int(int)> calc = [&](int i) {
        if (gapl[i] == -1 or gapr[i] == -1) return 0ll;
        return max(0ll, (int)(min(gapl[i], n/2-1ll)+min(gapr[i], n/2-1ll)+1ll-(n/2-1ll)));
    };

    int cnt = 0ll;
    for (int i = 0ll; i < n; i++) {
        cnt += calc(i);
    }
    onepoints += cnt;

    for (int i = (int)n/2; i < n; i++) {
        // insert p[i] and remove p[i-n/2]
        dbg("REMOVING", p[i-n/2]);
        int g = p[i-n/2];
        cnt -= calc(g);
        int a = poses.order_of_key(g);
        int g1, g2;
        if (a == 0ll) {
            g1 = (g);
        } else {
            g1 = g-(*poses.find_by_order(a-1))-1;
        }
        if (a == n/2-1) {
            g2 = (n-g-1);
        } else {
            g2 = (*poses.find_by_order(a+1))-g-1;
        }
        int w = (*poses.find_by_order(a-1));
        int e = (*poses.find_by_order(a+1));
        if (a != 0ll) {
            cnt -= calc(w);
            gapr[w] = g1+g2+1;
            cnt += calc(w);
        }
        if (a != n/2-1) {
            cnt -= calc(e);
            gapl[e] = g1+g2+1;
            cnt += calc(e);
        }
        gapl[g] = -1;
        gapr[g] = -1;
        poses.erase(poses.find(g));
        gaps.erase(gaps.find(g1));
        gaps.erase(gaps.find(g2));
        gaps.insert(g1+g2+1);

        poses.insert(p[i]);
        dbg("INSERTING", p[i]);
        g = p[i];
        a = poses.order_of_key(g);
        if (a == 0ll) {
            g1 = (g);
        } else {
            g1 = g-(*poses.find_by_order(a-1))-1;
        }
        if (a == n/2-1) {
            g2 = (n-g-1);
        } else {
            g2 = (*poses.find_by_order(a+1))-g-1;
        }
        w = (*poses.find_by_order(a-1));
        e = (*poses.find_by_order(a+1));
        dbg(g1, g2);
        if (a != 0ll) {
            cnt -= calc(w);
            gapr[w] = g1;
            dbg(w, calc(w), gapl[w], gapr[w]);
            cnt += calc(w);
        }
        if (a != n/2-1) {
            cnt -= calc(e);
            gapl[e] = g2;
            dbg(e, calc(e), gapl[e], gapr[e]);
            cnt += calc(e);
        }
        gapl[g] = g1;
        gapr[g] = g2;
        cnt += calc(g);
        dbg(g, a, g1, g2);
        gaps.erase(gaps.find(g1+g2+1));
        gaps.insert(g1);
        gaps.insert(g2);
        dbg(gaps);

        nopoints += (*gaps.rbegin()) >= (int)n/2;
        onepoints += cnt;
        dbg(i, cnt);
    }
    dbg(nopoints, onepoints);
    int ans = nopoints* ((n/2)*(n/2-1));
    ans += onepoints;
    cout << ans << "\n";
}
