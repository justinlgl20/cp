#include <bits/stdc++.h>
using namespace std;
 
 
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
    int q; cin >> q; return q;
}

#ifndef DEBUG
#include "celebrity.h"
#else
#include "celebrities.h"
#endif

vector<int> find_celebrities(int N) {
    vector<int> possible(N+1, 1);
    possible[0] = 0;
    int pos = N;
    while (pos > 1) {
        int first = 0;
        while (!possible[first]) first++;
        int second = 0;
        while (second == first or !possible[second]) second++;
        int knows = ask_question(first, second);
        if (knows) {
            possible[first] = 0;
            pos--;
        } else {
            possible[second] = 0;
            pos--;
        }
    }
    int ans = 0;
    while (!possible[ans]) ans++;
    int works = 1;
    dbg(ans);
    for (int i = 1; i <= N; i++) {if (ans == i) continue; if (!ask_question(i, ans) or ask_question(ans, i)) {dbg(i); works = false; break;}}
    dbg(works);
    if (works) return {ans};
    return {};
    
}
