#include <bits/stdc++.h>
using namespace std;

#define int long long

#define all(x) (x).begin(), (x).end()

template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> g) {
    os << "{" << g.first << ", " << g.second << "}";
    return os;
}

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> t) {
    int g = t.size(); os << "{"; for (auto i : t) os << i << ((--g)?", ":""); os << "}";
    return os;
}

void _print() {
    cerr << "]\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " " << "[" << #x << "]" << " = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int nxt() {
    int g; cin >> g; return g;
}

int32_t main() {
    int c, n; cin >> c >> n;
    vector<int> chickens(c);
    vector<pii> cows(n);
    
    generate(all(chickens), nxt);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        cows[i] = make_pair(a, b);
    }

    sort(all(chickens));
    sort(all(cows));
    multiset<int> ends;

    int ans = 0;
    int inx = 0;
    dbg(cows);
    for (int chicken : chickens) {
        while (inx < n and cows[inx].f <= chicken) {
            dbg("ADDING", cows[inx]);
            if (chicken <= cows[inx].s) {
                ends.insert(cows[inx].s);
            }
            inx++;
        }
        while (ends.size() and (*ends.begin()) < chicken) {
            ends.erase(ends.begin());
        }
        if (ends.size()) {
            dbg(ends);
            dbg(chicken, *(ends.begin()));
            ans += 1;
            ends.erase(ends.begin());
        }
    }
    cout << ans << "\n";
}
