#include <bits/stdc++.h>
#include <string>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}

ostream& operator<<(ostream& os, string s) {
    os << s;
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
    string s; cin >> s;
    s = "0"+s;
    int n = s.size();
    vector<int> v(10, 0);
    for (int i = 1; i <= 9; i++) cin >> v[i];
    function<int(string)> cost = [&](string s) {
        int q = s.size();
        int ans = 0;
        for (int i = 0; i < q; i++) {
            ans += v[s[i]-'0'];
        }
        return ans;
    };

    int tcost = cost(s);
    dbg(s.c_str(), tcost);

    vector<vector<int>> next(10, vector<int>(n+2, -1));
    for (int i = n-1; i > 0; i--) {
        for (int j = 1; j <= 9; j++) {
            next[j][i-1] = next[j][i];
        }
        next[s[i]-'0'][i-1] = i;
    }
    next[0][0] = 0;

    function<bool(string, int)> works = [&](string s, int i) {
        if (s.size() == 0) return true;
        int q = next[s[0]-'0'][i];
        if (q == -1) return false;
        s.erase(s.begin());
        return works(s, q);
    };
    int ans = tcost;
    for (int i = 0; i < 1000005; i++) {
        string g = to_string(i);
        int val = tcost - cost(g) + i;
        // check if g actually works
        if (works(g, 0)) {
            ans = min(ans, val);
        }
    }
    cout << ans << "\n";

}

int32_t main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int c, t; cin >> c;
    cin >> t;
    dbg(c, t);
    while(t--) solve();
}
