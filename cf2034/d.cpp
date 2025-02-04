#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
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

void solve() {
    int n; cin >> n;
    vector<int> a(n+5, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    set<int> ones, twos, zeros;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) ones.insert(i);
        if (a[i] == 2) twos.insert(i);
        if (a[i] == 0) zeros.insert(i);
    }
    int z = zeros.size();
    int t = twos.size();
    int o = ones.size();
    bool works = true;
    for (auto i : ones) {
        if (z < i and i <= z+o) continue;
        else works = false;
    }
    vector<pii> ans;
    if (works) {
        int i = *ones.begin();
        int j = 1;
        while (a[j] == 1) j++;
        if (j == n+1) {
            cout << "0\n";
            return;
        }
        if (a[j] == 0) {
            zeros.insert(i);
            zeros.erase(zeros.find(j));
        }
        if (a[j] == 2) {
            twos.insert(i);
            twos.erase(twos.find(j));
        }
        ones.insert(j);
        ones.erase(ones.find(i));
        swap(a[i], a[j]);
        ans.emplace_back(i, j);
    }
    // 1 to z inclusive
    while (zeros.size() and (*zeros.begin()) <= z) zeros.erase(zeros.begin());

    stack<int> qu;
    function<void(int)> zero = [&](int i) {
        int g = *(zeros.rbegin());
        ans.emplace_back(i, g);
        zeros.erase(zeros.find(g));
        a[g] = 1;
        a[i] = 0;
        if (g >= z+o+1ll) {
            qu.push(g);
        }
    };
    function<void(int)> two = [&](int i) {
        int g = (*twos.begin());
        ans.emplace_back(i, g);
        twos.erase(twos.begin());
        a[g] = 1;
        a[i] = 2;
        if (g <= z) {
            qu.push(g);
        }

    };
    for (int i = 1; i <= z; i++) {
        if (a[i] == 1) {
            // swap i and zeros.begin()
            zero(i);
            while (qu.size()) {
                int u = qu.top();
                qu.pop();
                if (u <= z) zero(u);
                else two(u);
            }
        }
    }
    for (int i = z+o+1ll; i <= n; i++) {
        if (a[i] == 1) {
            two(i);
            while (qu.size()) {
                int u = qu.top();
                qu.pop();
                if (u <= z) zero(u);
                else two(u);
            }
        }
    }
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i.f << " " << i.s << "\n";
    }
    
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
