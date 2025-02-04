#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
#ifdef DEBUG
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif
#include "Bob.h"

// you may define some global variables, but it does not work if you try to transfer any information from function Alice() to function Bob() through these variables.
// you had better not use the same global variables in function Alice() and in function Bob().

long long Bob(std::vector<std::pair<int,int>> V){
    srand(69);
    vector<int> order;
    for (int i = 65; i <= 5000; i++) order.push_back(i);
    //shuffle(all(order));
    
    vector<int> deg(5005, 0);
    vector<set<int>> adj(5005, set<int>());
    vector<int> has(64, 0);
    for (auto i : V) {
        if (i.first == 1 and i.second != 2) {
            cerr << (i.second) << " " << (i.second%64-3+64)%64 << "\n";
            has[(i.second%64-3+64)%64] = 1;
        }
    }
    ll ans = 0;
    for (int i = 0; i < 64; i++) {
        if (has[i]) {
            cerr << i << "\n";
            ans += ((ll)1)<<((ll)i);
        }
    }
    cerr << ans << "\n";
    return ans;
}

