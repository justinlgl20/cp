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

int nxt() {
    int g; cin >> g; return g;
}

vector<int> positions[100005];
int in_pos[100005];

int goes[100005];
bool seen[100005];

int answers[100005];

int SQRT;

int32_t main() {
    int n = nxt(), k = nxt();
    for (int i = 0; i <= n; i++) {
        in_pos[i] = i;
        positions[i].push_back(i);
    }
    for (int i = 0; i < k; i++) {
        int a=nxt(), b = nxt();
        int c = in_pos[a], d = in_pos[b];
        assert(positions[c].back() == a);
        assert(positions[d].back() == b);

        positions[c].push_back(b);
        positions[d].push_back(a);
        in_pos[b] = c;
        in_pos[a] = d;
    }

    int num = 0;

    for (int i = 1; i <= n; i++) {
        num += positions[i].size();
        assert(i == positions[i].front());
        goes[i] = positions[i].back();
    }

    SQRT = pow(num, 0.5);

    dbg(SQRT);

    for (int i = 1; i <= n; i++) {
        if (seen[i]) continue;
        int u = i;
        seen[u] = true;
        vector<int> stuff = {u};
        int sz = positions[u].size();
        u = goes[u];
        while (u != i) {
            stuff.push_back(u);
            sz += positions[u].size();
            seen[u] = true;
            u = goes[u];
        }
        dbg(stuff, sz);
        int ans;
        if (sz >= SQRT) {
            vector<int> have(n+2, 0);
            ans = 0;
            for (auto i : stuff) {
                for (auto j : positions[i]) {
                    ans += (have[j] != 1);
                    have[j] = 1;
                }
            }
        } else {
            unordered_set<int> have;
            for (auto i : stuff) {
                for (auto j : positions[i]) {
                    have.insert(j);
                }
            }
            ans = have.size();
        }
        for (auto i : stuff) {
            answers[i] = ans;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << answers[i] << "\n";
    }

}
