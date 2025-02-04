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
    int n, x; cin >> n >> x;
    map<int, int> amount;
    for (int i = 0; i < n; i++) {
        int g; cin >> g;
        amount[g] ++;
    }
    multiset<int> excess;
    int mex = 0;
    multiset<int> extras;
    for (auto i : amount) {
        if (i.f == mex) {
            mex++;
            for (int j = 0; j < i.s-1; j++) {
                excess.insert(i.f%x);
            }
        } else {
            for (int j = 0; j < i.s; j++) {
                extras.insert(i.f);
            }
        }
    }
    dbg(mex, extras, excess);
    for (int i = mex+1;; i++) {
        // see if we can get to this
        int g = i-1; // we need to add one of these
        dbg("NEED A", g);
        if (extras.find(g) != extras.end()) {
            dbg("USE EXTRA");
            extras.erase(extras.find(g)); // use one of our extras
        } else {
            if (excess.find(g%x) != excess.end()) {
                dbg("USE EXCESS");
                excess.erase(excess.find(g%x));
            } else {
                dbg("GOT NOTHING");
                cout << g << "\n";
                return;
            }
        }
        while (extras.size() and (*extras.begin()) <= g) {
            excess.insert((*extras.begin())%x);
            extras.erase(extras.find(*extras.begin()));
        }
    }
}

int32_t main() {
    int t; cin >> t;
    for (int _ = 0; _ < t; _++) solve();
}
