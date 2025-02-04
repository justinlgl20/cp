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

#define ull unsigned long long

const ull idk = 2000000000000021;
const int idk2= 1000000000000000;

int32_t main() {
    int n, m; cin >> n >> m;
    vector<int> vals(n*m+10, 0);
    function<int(int, int)> id = [&](int i, int j) {
        if (i < 0 or i >= n or j < 0 or j >= m) return n*m+1ll;
        return i * m + j;
    };
    vector<int> to(n*m+10, n*m);
    char x;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> x;
            if (x == '^') {
                to[id(i, j)] = id(i-1, j);
            }
            else if (x == 'v') {
                to[id(i, j)] = id(i+1, j);
            } else if (x == '>') {
                to[id(i, j)] = id(i, j+1);
            } else {
                to[id(i, j)] = id(i, j-1);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> vals[id(i, j)];
        }
    }
    vector<int> scores(n*m+10, -1e9);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int start = id(i, j);
            int pos = id(i, j);
            int cur = 0;
            vector<int> seen(n*m+10, 0);
            int foot = 0; // 0 is l, 1 is r
            while (pos != n*m+1ll) {
                if (seen[pos] == 4) break;
                if (foot == 0) {
                    cur += vals[pos] * (seen[pos]%2 == 1 ? -1 : 1);
                } else {
                    cur -= vals[pos] * (seen[pos]%2 == 1 ? -1 : 1);
                }
                seen[pos]++;
                dbg(pos, cur);
                scores[start] = max(scores[start], cur);
                foot = (foot+1ll)%2;

                pos = to[pos];
            }
        }
    }
    ull ans = 0;
    ull v = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int g =  scores[id(i, j)];
            ans += ((ull)(g + idk2)) * v;
            v *= idk;
        }
    }
    cout << ans << "\n";
}
