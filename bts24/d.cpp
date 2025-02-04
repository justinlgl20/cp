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
    int c; cin >> c; return c;
}

void lose() {
    while (1) 0;
    cout << "-1\n";
    exit(0);
}

int32_t main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    generate(all(a), nxt);
    vector<int> pos(n+5);
    for (int i = 0; i < n; i++) pos[a[i]-1] = i;

    vector<vector<int>> cand(n);
    vector<vector<int>> idk;
    for (int i = 0; i < n; i++) {
        cand[pos[i]].resize(k);
        generate(all(cand[pos[i]]), nxt);
        idk.push_back(cand[pos[i]]);
    }
    // cand is now in order sigma sigma
    vector<vector<int>> points(k, vector<int>());
    for (int i = 0; i < n; i++) {
        dbg(cand[i]);
    }
    vector<vector<int>> active(n+2, vector<int>(k+2, 0));
    for (int i = 0; i < k; i++) {
        points[i].push_back(0);
        active[0][i] = 1;
        for (int j = 1; j < n; j++) {
            if (cand[j][i] > cand[j-1][i]) {points[i].push_back(j);active[j][i] = 1;}
        }
        points[i].push_back(n);
        active[n][i] = 1;
        dbg(i, points[i]);
    }
    int x;
    for (int i = 0; i < k; i++) {
        if (points[i].size() == 2) {x = i;break;}
    }
    vector<int> g;
    for (int i = 0; i < k; i++) g.push_back(i);
    sort(all(g), [&](int i, int j) { 
            if (i == x) return true;
            if (j == x) return false;
            //if (points[i].size() != points[j].size()) return points[i].size() < points[j].size(); // must start with smallest but that is only condition
            // if their sizes are equal, then whichever changes from initial first is second
            // if the positions of points are different, then it doesn't work anyway and we'll check that later
            for (int q = 1; q < n; q++) { // THIS SECTION IS VERY VERY SUSSY ABOUT LOSING WHEN ITS NOT ACTUALLY A LOSS IT IS SHOCKINGLY NOT THIS BIT WTF
                bool firs = cand[q][i] != cand[q-1][i];
                bool seco = cand[q][j] != cand[q-1][j];
                if (firs and !seco) {
                    // i changes first, so j should go first
                    return false;
                }
                if (seco and !firs) {
                    return true;
                }
                /*
                firs = cand[q-1][i] < cand[q][i];
                seco = cand[q-1][j] < cand[q][j];
                // IF ANY OF THESE HAPPEN WE LOSE
                if (firs and !seco) {
                    lose();
                }
                if (seco and !firs) {
                    lose();
                }*/

            }
            return i < j;
            });
    //now need to check if that sequence works
    dbg(g);
    /*
    for (int i = 0; i < k-1; i++) {
        //points[g[i]] must be a subset of points[g[i+1]]
        // NOTE THAT ABOVE CLAIM IS VERY SUS BUT KINDA NOT REALLY
        dbg(i, g[i], points[g[i]]);
        for (auto j : points[g[i]]) {
            if (!active[j][g[i+1]]) lose();
        }
    }*/
    /*for (int i = 1; i < k; i++) {
        // find extra points that are in points[g[i]] and not points[g[i-1]]
        for (int j : points[g[i]]) {
            if (!active[j][g[i-1]]) {
                // j and j-1 must differ
                if (j > 0) {
                    if (cand[j][i] == cand[j-1][i]) lose();
                }
            }
        }
    }*/

    auto works =  [&](vector<int> a, vector<int> b) {
                for (int i : g) {
                    if (a[i] != b[i]) return a[i] > b[i];
                }
                return true;
            };
    // BUG UNDER HERE WTF WTF WTF
    for (int i = 0; i < n-1; i++) {
        dbg(idk[a[i]-1], idk[a[i+1]-1]);
        if (!works(idk[a[i]-1], idk[a[i+1]-1])) lose();
    }
    dbg("HI");
    
    auto idrk = cand;
    random_shuffle(all(idrk));
    sort(all(idrk), works);
    if (idrk != cand) lose();

    for (int i : g) cout << i+1 << " "; 
    cout << "\n";
}
