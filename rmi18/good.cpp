
#include <bits/stdc++.h>
using namespace std;

#define ll int64_t
 
#define all(x) (x).begin(), (x).end()

template<typename A, typename B>
ostream& operator<<(ostream& os, pair<A, B> g) {
    os << "{" << g.first << ", " << g.second << "}";
    return os;
}
 
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
 
 
 
priority_queue <pair<ll, pii>> pq;
 
#define idk(a, b, c) ((a <= b and b <= c) or (a >= b and b >= c))
 
ll dist[5005][5005];
int n;

void add(int i, int j, ll d) {
    //cerr << i*n+ j  << " " << i << " " << j << " "  << d << " " <<  dist[i][j] << "\n";
    if (d < dist[i][j]) {
        dist[i][j] = d;
        pq.push({ -d, { i, j } });
        //cerr << "INSERT " << -d << " " << i << " " << j << "\n";
    }
}
int main() {
    cin >> n;
    vector <int> v;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        while (v.size() >= 2 and idk(v[v.size()-2], v[v.size()-1], x)) v.pop_back();
        v.push_back(x);
    }
 
 
    n = v.size();
    //cerr << n << "\n";
    for (int i = 0; i <= n-1; i++) {
        for (int j = 0; j <= n-2; j++) {
            dist[i][j] = 1e18;
        }
    }
    dist[0][n-2] = 0;
    pq.push({ 0, {0, n-2} });
 
    while (!pq.empty()) {
        /*auto g = pq;
        
        while (g.size()) {
            dbg(g.top());
            g.pop();
        }*/
        auto p = pq.top();
        int i = p.s.f, j = p.s.s;
        ll d = dist[i][j];
        dbg(i, j, i*n+j, -d);
        ////cerr << i*n+j << " " << i << " " << j << " "  << d << "\n";
        if (-p.f == d) {
 
            if (i == j or i == j+1) {
                cout << d << '\n';
                return 0;
            }
            if (i+1 < n) { 
                dbg("before");
                if (idk(v[j], v[i+1], v[j+1])) {
                    add(i+1, j, d+abs(v[i]-v[i+1]));
                    dbg("CASE 1");
                }
                if (idk(v[i], v[j], v[i+1])) {
                    add(j, i, d+abs(v[i]-v[j]));
                    dbg("CASE 2");
                }
                if (idk(v[i], v[j+1], v[i+1])) {
                    add(j+1, i, d+abs(v[i]-v[j+1]));
                    dbg("CASE 3");
                }
            }
            if (i-1 >= 0)
            {
                dbg("after");
                if (idk(v[j], v[i-1], v[j+1])) {
                    add(i-1, j, d+abs(v[i]-v[i-1]));
                    dbg("CASE 4");
                }
                if (idk(v[i], v[j], v[i-1])) {
                    add(j, i-1, d+abs(v[i]-v[j]));
                    dbg("CASE 5");
                }
     
                 if (idk(v[i], v[j+1], v[i-1])) {
                    add(j+1, i-1, d+abs(v[i]-v[j+1]));
                    dbg("CASE 6");
                }
            }
        }
        pq.pop();
    }
    cout << "NO\n";
}
