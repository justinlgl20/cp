#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define f first
#define s second

#define int long long

void solve() {
    int n, m; cin >> n >> m;
    int best_pos = 0;
    int overlap = 0;
    vector<pii> things;
    vector<pii> events;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        things.emplace_back(a, b);
        events.emplace_back(a, 1);
        events.emplace_back(b, -1);
    }
    events.push_back({m, 0});
    events.push_back({1, 0});
    sort(events.begin(), events.end(), [&](pii a, pii b) {
        if (a.f != b.f) return a.f < b.f;
        return a.s > b.s;
    });
    int cost = 0;
    int last = 1;
    int worst = 1000000000000;
    for (auto i : events) {
        if (cost > overlap) {
            best_pos = i.f;
            overlap = cost;
        }
        last = i.f;
        cost += i.s;
    }
    events.clear();
    for (int i = 0; i < n; i++) {
        if (things[i].f <= best_pos and best_pos <= things[i].s) {
            events.emplace_back(things[i].f, 1);
            events.emplace_back(things[i].s+1, -1);
        } else {
            events.emplace_back(things[i].f, 0);
            events.emplace_back(things[i].s+1, 0);
        }
    }
    cost = 0;
    last = 1;
    worst = 10000000000000;
    events.push_back({m+1, 0});
    events.push_back({1, 0});
    sort(events.begin(), events.end(), [&](pii a, pii b) {
        if (a.f != b.f) return a.f < b.f;
        return a.s > b.s;
    });
    for (auto i : events) {
        if (last != i.f and cost < worst) worst = cost;
        last = i.f;
        cost += i.s;
    }
    cout << overlap - worst << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
