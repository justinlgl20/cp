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
    int x; cin >> x; return x;
}

void solve() {
    int n; cin >> n;
    vector<set<int>> races(n, vector<int>(n));
    vector<int> victor(n);
    for (int i = 1; i <= n*n; i++) {
        races[(i-1)%n].insert(i);
    }
    for (int i = 0; i < n; i++) {
        cout << "? ";
        for (int j : races[i]) cout << j << " \n"[j%n == 0];
        cin >> victor[i];
    }
    cout << "? ";
    for (int i = 0; i < n; i++) cout << victor[i] << " \n"[i==n-1];
    int win; cin >> win;
    set<int> relevant;
    for (int i = 1; i <= n*n; i++) relevant.insert(i);

    relevant.erase(win);
    int inx = 0;
    for (int i = 0; i < n; i++) {
        if (victor[i] == win) inx = i;
    }
    races[inx].erase(win);
    vector<int> ans;
    ans.push_back(win);
    victor[inx] = -1;
    cout << "? ";
    for (int i : races[inx]) {
        cout << i << " ";
        relevant.erase(i);
    }
    cout << relevant.begin();
    for (int i : races[inx]) relevant.insert(i);
    cout << "\n";
    int w = nxt();
    victor[inx] = w;
    while (ans.size() <= n*n-n+1) {
        cout << "? ";
        for (int i = 0; i < n; i++) cout << victor[i] << " \n"[i==n-1];
        cin >> win;
        ans.push_back(win);
        for (int i = 0; i < n; i++) {
            if (races.find(win) != races.end()) {
                races.erase(win);
                inx = i;
            }
        }
        relevant.erase(races);
        
    }

}
