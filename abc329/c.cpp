
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

template<typename T, typename P>
ostream& operator << (ostream& os, pair<T, P> g) {
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
    int x; cin >> x; return x;
}

int32_t main() {
    int N = nxt();
    string c; cin >> c;
    vector<pair<int, char>> lengths;

    char last = c[0];
    int length = 0;
    for (char i : c) {
        if (i == last) length++;
        else {lengths.push_back({length, last});length = 1;}
        last = i;
    }
    if (length) lengths.emplace_back(length, last);
    dbg(lengths);
    unordered_map<char, int> big;
    for (auto i : lengths) big[i.second] = max(big[i.second], i.first);
    int ans = 0;
    for (auto i : big) {
        dbg(i);
        ans += i.second;
    }
    cout << ans << "\n";
}
