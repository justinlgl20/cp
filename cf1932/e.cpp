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

void solve() {
    int n;
    string s; cin >> n >> s;
    vector<int> psa(n+3);
    psa[0] = s[0]-'0';
    for (int i = 1; i < n; i++) {
        psa[i] = psa[i-1] + (s[i]-'0');
    }
    vector<int> ans;
    int carry = 0;
    for (int i = n-1; i >= 0; i--) {
        ans.push_back((psa[i]+carry)%10);
        carry = (psa[i]+carry)/((int)10);
    }
    if (carry != 0)
        ans.push_back(carry);
    reverse(all(ans));
    bool zero = true;
    for (auto i : ans) {
        if (zero and i == 0) continue;
        zero = false;
        cout << i;
    }
    cout << "\n";
}

int32_t main() {
    int t; cin >> t; while (t--) solve();
}
