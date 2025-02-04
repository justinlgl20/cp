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

struct node {
    unordered_map<char, node*> children;
    vector<pii> values; // depth, value
    vector<int> psa;
    node() {
        values.clear();
        psa.clear();
    }
    void add(string &s, int i, int dep, int val) {
        values.emplace_back(dep, val);
        if (i == s.size()) return;
        if (children.find(s[i]) == children.end()) {
            children[s[i]] = new node();
        }

        children[s[i]]->add(s, i+1, dep, val);
    }
    void build() {
        sort(all(values));
        int cnt = 0;
        for (auto i : values) {
            dbg(i.f, i.s);
            cnt += i.s;
            psa.push_back(cnt);
        }
        for (auto &i : children) {
            dbg(i.f);
            (i.s)->build();
        }
        dbg("UP");
    }
    int query(string &s, int i, int d) {
        if (children.find(s[i]) == children.end()) {
            children[s[i]] = new node();
        }
        if (i == s.size()) {
            int covers = 0;
            if (values.size() and values[0].f > d) return 0;
            for (int j = 18; j >= 0; j--) {
                if (covers + (1ll<<j) < values.size() and values[covers+(1ll<<j)].f <= d) {
                    covers += (1ll<<j);
                }
            }
            return psa[covers];
        }
        return children[s[i]]->query(s, i+1, d);
    }
};

int32_t main() {
    node trie = node();
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int dep, val; string s;
        cin >> dep >> val >> s;
        trie.add(s, 0, dep, val);
    }
    trie.build();
    while (m--) {
        int d; string q;
        cin >> d >> q;
        int ans = trie.query(q, 0, d);
        cout << ans << "\n";
    }
}
