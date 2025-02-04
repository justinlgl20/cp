#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
/*template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}*/
 
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

int difference(string a, string b) {
    int x = min(a.size(), b.size());
    int ans= 0;
    for (int i = 0; i < x; i++) ans += a[i] == b[i];
    return (double)ans > (double)x/(double)2;
}

int32_t main() {
    int n; cin >> n;
    string x; cin >> x;
    string a;
    getline(cin,a); 
    vector<string> s(n);
    for (int i = 0; i < n; i++) getline(cin, s[i]);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        dbg(i, s[i], x, difference(s[i], x));
        ans += difference(s[i], x);
    }
    cout << ans << "\n";
    if (ans == 0) cout<< "Good job!\n";
    else cout << "Make persistent efforts.\n";
    
}
