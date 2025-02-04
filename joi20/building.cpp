#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename G>
ostream& operator << (ostream& os, Container<G> g) {
    int s = g.size();
    os << "{";
    for (auto i : g) os << i << (--s?", ":"}");
    return os;
}

void _print() {cerr << "]" << endl;}

template<typename T, typename... V>
void _print(T t, V... v) {
    cerr << t;
    if (sizeof...(v)) cerr << ", ";
    _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

int nxt() {
    int x; cin >> x; return x;
}

int dpl[1000005][3];
int dpr[1000005][3];
int n, q;

int main() {
    cin >> n;
    n*=2;
    vector<int> a(n), b(n);
    generate(all(a), nxt);
    generate(all(b), nxt);

    dpr[0][0] = dpl[0][0] = 1;
    dpl[0][1] = dpr[0][1] = 0;
    for (int i = 1; i < n; i++) {
        dpr[i][0] = dpr[i][1] = -1;
        dpl[i][0] = dpl[i][1] = 1e9;
            if (b[i-1] <= b[i]) {
            dpl[i][1] = dpl[i-1][1];
            dpr[i][1] = dpr[i-1][1];
        }
        if (a[i-1] <= a[i]) {
            dpl[i][0] = dpl[i-1][0]+1;
            dpr[i][0] = dpr[i-1][0]+1;
        }

        if (a[i-1] <= b[i]) {
            dpl[i][1] = min(dpl[i][1], dpl[i-1][0]);
            dpr[i][1] = max(dpr[i][1], dpr[i-1][0]);
        }
        if (b[i-1] <= a[i]) {
            dpl[i][0] = min(dpl[i][0], dpl[i-1][1]+1);
            dpr[i][0] = max(dpr[i][0], dpr[i-1][1]+1);
        }
    }

    if ( (dpl[n-1][0] > n/2 and dpl[n-1][1] > n/2) or (dpr[n-1][0] < n/2 and dpr[n-1][1] < n/2)) {
        cout << "-1\n";
        return 0;
    }
    bool plan = 0;
    if (dpl[n-1][1] <= n/2 and dpr[n-1][1] >= n/2) plan = 1;
    vector<char> ans = {};
    ans.push_back(char((int)'A'+plan));
    int idk = n/2-1+plan;
    for (int i = n-2; i >= 0; i--) {
        if (dpl[i][0] <= idk and dpr[i][0] >= idk and a[i] <= (plan ? b[i+1] : a[i+1])) 
            plan = 0;
        else
            plan = 1;
        idk = idk-1+plan;
        ans.push_back((char)('A'+plan));
    }
    reverse(all(ans));
    for (auto i : ans) cout << i;
    cout << "\n";
}
