#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[200005];

struct seg {
    int tl, tr;
    int val;
    seg *l, *r;
    seg(int tl, int tr) : tl(tl), tr(tr) {
        if (tl == tr) {
            val = a[tl];
            return;
        }
        int tm = (tl+tr)/2;
        l = new seg(tl, tm);
        r = new seg(tm+1, tr);
        val = (l->val)&(r->val);
    }
    int get(int ql, int qr) {
        if (ql <= tl and tr <= qr) return val;
        else if (tl > qr or ql > tr) return (int)(1<<31)-1;
        else return (l->get(ql, qr))&(r->get(ql, qr));
    }
};

void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    seg x = seg(1, n);
    int q; cin >> q;
    while (q--) {
        int l, k; cin >> l >> k;
        int g = l;
        for (int val = 30; val >= 0; val -= 1) {
            //cerr << "DEBUG\n";
            //cerr << "Try add " << val << " " << x.get(l, g+(1<<val)) << "\n";
            if (g+(1<<val) <= n and x.get(l, g+(1<<val)) >= k) {
                g+=(1<<val);
                //cout << "ADDED " << val << "\n";
            }
        }
        if (g == l and a[g] < k) g = -1;
        cout << g << " ";
    }
    cout << "\n";
}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
