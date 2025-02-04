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
    
vector<int> psa;

int query(int l, int r) {
    return psa[r+1]-psa[l];
};


int32_t main() {
    unordered_map<int, int> idk;
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> q = a;
    if (n == m) {
        for (int i = 0; i < n; i++) cout << "0 ";
        cout << "\n";
    }

    psa.resize(n+1);
    psa[0] = 0;
  
    sort(all(a));
    for (int i = 0; i < n; i++) {
        psa[i+1] = psa[i]+a[i];
    }
    int s = k;
    for (int i = 0; i < n; i++) s -= a[i];
    //must have >= than a[n-m]
    dbg(s);
    vector<int> ans(n, -1);
    for (int i = 0; i < n-m; i++) {
        // he must get a[n-m]-a[i]
        int g = (s-(a[n-m]-a[i]));
        if (g < 0) {
            ans[i] = -1;
            idk[a[i]] = -1;
            continue;
        }
        dbg(i, g);
        g = a[n-m]-a[i]+g/2 + g % 2; // amount he must receive
        dbg(g);
        ans[i] = g > 0 ? g : -1;
        idk[a[i]] = ans[i];
    }
    dbg(a);
    for (int i = n-m; i < n; i++) { // THIS BIT BROKEN
        // for him to lose, i-(n-m)+1 people need to overtake him
        int amount = i-(n-m)+2;
        int l = n-m-1;
        function<int(int, int)> works = [&](int l, int r) {
            int q = s - ((r-l+1)*a[r] - query(l, r));
            return q > 0;
        };
        /*
        for (int j = 20; j >= 0; j--) {
            if (l + (1<<j)+amount-1 < n and l < i and works(l+(1<<j), l+(1<<j)+amount-1)) {
                l += 1<<j;
            }
        }*/
        int r = l+amount-1;
        for (int j = 20; j >= 0; j--) {
            if (r + (1<<j) < n and works(l, r+(1<<j))) {
                r += 1<<j;
            }
        }
        dbg(works(2, 4));
        dbg(l, r, n-m-1, i, amount, query(l, r));
        int g = s - ((r-l+1)*(a[r]) - query(l, r)); // we are looking for furthest right range of size (amount)
        dbg(g);
        if (g < 0) {
            ans[i] = 0;
            idk[a[i]] = 0;
            continue;
        }
        g = a[r]-a[i] + g/(amount) + (g%(amount) > 0);
        ans[i] = g > 0 ? g : 0;
        idk[a[i]] = ans[i];
    }
    for (int i = 0; i < n; i++) {
        cout << idk[q[i]] << " \n"[i==n-1];
    }
    // hiu
}
