#include <bits/stdc++.h>
using namespace std;
 
#define int long long
#define double long double
 
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

double a[105], b[105], p[105], q[105];
double epsilon;

struct line {
    double m, c;
    double get(double x) {
        return m*x + c;
    }
};

double intersect(line a, line b) {
    return (double)(a.c-b.c)/(b.m-a.m);
}

int cheapest(int i, int w) {
    dbg(i, a[i], b[i], p[i], q[i]);
    double g = (double)w/a[i]; //(0, g)
    double t = (double)w/b[i]; //(q, 0)
    line l = {-(double)g/t, g};
    dbg(g, t, l.m, l.c);
    double r = min(ceil(g)*q[i], ceil(t)*p[i]);
    // y above 0 then we are fine
    if (l.m < -(double)p[i]/q[i]) {
        int ans = 0;
        for (int j = 30; j >= 0; j--) {
            line li = {(double)-p[i]/q[i], ans+(1ll<<j)};
            int x = ceil(intersect(l, li));
            int y = ceil(l.get(x));
            if (y < 0) {
                ans += (1ll<<j);
                continue;
            }
        }
        ans += 1;
        line li = {-(double)p[i]/q[i], ans};
        double x = ceil(intersect(l, li)); // can't just round up need certain amount of machines
        double y = ceil(l.get(x));
        dbg(ans, x, y);
        return min(r, x*q[i]+y*p[i]);
    } else if (l.m > -(double)p[i]/q[i]){
        int ans = 0;
        for (int j = 30; j >= 0; j--) {
            line li = {-(double)p[i]/q[i], ans+(1ll<<j)};
            int x = ceil(intersect(l, li));
            int y = ceil(l.get(x));
            if (x < 0) {
                ans += (1ll<<j);
                continue;
            }
        }
        ans += 1ll;
        line li = {-(double)p[i]/q[i], ans};
        double x = ceil(intersect(l, li));
        double y = ceil(l.get(x));
        return min(r, x*q[i]+y*p[i]);
    } else {
        return min(ceil(g)*q[i], ceil(t)*p[i]);
    }
}

int32_t main() {
    int n, x; cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> p[i] >> b[i] >> q[i];
    }
    int ans = 0;
    int qw1 = (cheapest(1, 6));
    dbg(qw1);
    for (int i = 20; i >= 0; i--) {
        int g = ans+(1ll<<i);
        int cost = 0;
        for (int j = 1; j <= n; j++) cost += cheapest(j, g);
        if (cost <= x) {
            ans += (1ll<<i);
        }
    }
    //}
    cout << ans << "\n";
}
