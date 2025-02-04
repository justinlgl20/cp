#include <bits/stdc++.h>
using namespace std;

#define int long long

struct dsu {
    int n;
    vector<int> par;
    dsu(int n) {
        this->n = n;
        par.resize(n+1);
        for (int i = 0; i <= n; i++) par[i] = i;
    }
    void merge(int a, int b) {
        par[rep(a)] = rep(b);
    }
    int rep(int a) {
        return par[a] == a? a: par[a] = rep(par[a]);
    }
};

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    vector<int> g;
    vector<tuple<int, int , int>> edges;
    for (int i = 0; i < m; i++) {
        g.push_back(i);
        int a, b, c; cin >> a >> b >> c;
        edges.push_back(make_tuple(a, b, c));
    }
    // 0 to m, pick n-1 of them
    int ans = 1e18;
    vector<int> bitmask;
    for (int i = 0; i < n-1; i++) bitmask.push_back(1);
    while (bitmask.size() != m) bitmask.push_back(0);
    do {
        dsu x = dsu(n);
        int cost = 0;
        bool works = true;        
        for (int i = 0; i < m and works; i++) {
            if (bitmask[i]) {
                cost += get<2>(edges[i]);
                cost %= k;
                if (x.rep(get<0>(edges[i])) == x.rep(get<1>(edges[i]))) works = false;
                x.merge(get<0>(edges[i]), get<1>(edges[i]));
            }
        }
        if (works) {
            ans = min(ans, cost%k);
        }
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    cout << ans << "\n";
}
