#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()

ostream& operator << (ostream& os, pair<int, int> g) {
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

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
}

int32_t main() {
    int N = nxt(), M = nxt();
    vector<int> votes(M);
    vector<int> idk(N+2, 0);
    generate(all(votes), nxt);
    set<pair<int, int>, decltype(cmp)*> answers(cmp);
    for (int i = 1; i <= N; i++) answers.insert(make_pair(0, i));
    vector<int> ans(M);
    for (auto i : votes) {
        answers.erase(answers.find(make_pair(idk[i], i)));
        idk[i] += 1;
        answers.insert(make_pair(idk[i], i));
        cout << (*answers.begin()).second << "\n";
    }
}
