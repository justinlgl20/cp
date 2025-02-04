#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> g) {
    os << "{" << g.first << ", " << g.second << "}";
    return os;
}
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
    int c; cin >> c; return c;
}

int n;
int st[19][262149];

int log(int i) {
    return i ? __builtin_clzll(1)- __builtin_clzll(i) : -1;
}

struct sparse {
    sparse(vector<int> t) {
        copy(all(t), st[0]);
        for (int i = 1; i <= 18; i++) {
            for (int j = 0; j + (1<<i) < n; j++) {
                st[i][j] = max(st[i-1][j], st[i-1][j+(1<<(i-1))]);
            }
        }
    }
    int query(int l, int r) {
        int i = log(r-l+1);
        return min(st[i][l], st[i][r-(1<<i)+1]);
    }
};

int under[19][262149];

int battles(int a, int b) {
    return (abs(a-b))*(abs(a-b));
}

int idk[262149];

int32_t main() {
    cin >> n;
    vector<int> t(n);
    generate(all(t), nxt);
    for (auto i : t) idk[i] = 1;
    int missing = -1;
    for (int i = 1; i <= n; i++) {
        if (!idk[i]) missing = i;
    }
    sparse x = sparse(t);
    for (int i = 0; i < n; i++) {
        under[0][i] = 0;
    }
    for (int i = 1; i < 19; i++) {
        for (int j = 0; j + (1<<i) < n; j++) {
            under[i][j] = under[i-1][j]+under[i-1][j+(1<<(i-1))] + battles(st[i-1][j], st[i-1][j+(1<<(i-1))]);// bottom + bottom + winner's battle
        }
    }
    for (int i = 0; i < n; i++) {
        // insert before this position
        // if even, we vs the one on the right, otherwise vs one on left
        int ans = 0;
        int left = 0;
        int stuff = missing;
        vector<pair<int, int>> versus;
        for (int j = 18; j >= 0; j--) {
            if (left + (1<<j) <= i) {
                ans += under[j][left];
                versus.push_back({j, st[j][left]});
                left += (1<<j);
            }
        }
        int right = n-1;
        for (int j = 18; j >= 0; j--) {
            if (right - (1<<j) >= i) {
                ans += under[j][right-(1<<j)];
                versus.push_back({j, st[j][right-(1<<j)]});
                right -= (1<<j);
            }
        }
        sort(all(versus));
        for (auto i : versus) {
            int g= i.second;
            ans += battles(g, stuff);
            stuff = max(g, stuff);
        }
        cout << ans << " ";
    }
    // insert at end
}
