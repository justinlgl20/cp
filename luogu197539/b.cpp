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

int powers[1005][1005];

int32_t main() {
    int t, p; cin >> t >> p;
    vector<int> r;
    for (int i = 0; i < 5; i++) {
        cout << "?\n" << flush;
        int x; cin >> x;
        r.push_back(x);
    }
    if (t==1) {
        for (int s = 0; s < p; s++) {
            // check if seed s works
            bool works = 1;
            for (int i = 1; i < 5; i++) {
                if (r[i-1] * s % p != r[i]) {
                    works = false;
                }
            }
            if (works) {
                cout << "! " << s << "\n" << flush;
                return 0;
            }
        }
    } else {
        // BIGGER P IS RE'ING
        // APPARENTLY X ISN'T BOUND BY P
        // X COULD BE NEGATIVE?
        for (int i = 0; i < 1003; i++) {
            powers[i][0] = 1;
            for (int j = 1; j < 1003; j++) {
                powers[i][j] = (powers[i][j-1]*i)%p;
            }
        }
        for (int x = 0; x <= p+30; x++) {
            int g = 1;
            for (int s = 0; s < p; s++) {
                bool works = true;
                for (int i = 0; i < 5; i++) {
                    if (powers[x+i][s] != r[i]) {
                        works = false;
                    }
                }
                if (works) {
                    cout << "! " << s << "\n" << flush;
                    return 0;
                }
            }
        }
    }

}
