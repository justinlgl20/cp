#include <bits/stdc++.h>
using namespace std;

#define int long long

#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> t) {
    int g = t.size(); os << "{"; for (auto i : t) os << i << ((--g)?", ":""); os << "}";
    return os;
}

void _print() {
    cerr << "]\n";
}

template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);
}

#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m" << __func__ << ":" << __LINE__ << " " << "[" << #x << "]" << " = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

int nxt() {
    int g; cin >> g; return g;
}

int r, c, n;

int id(int i, int j) {
    return i*c+j;
}

struct dsu {
    vector<int> p;
    
}


int randint(int l, int r) {
    return rand()%(r-l+1)+l;
}

struct state {
    int oldscore;
    int score;
    //info
    void become_neighbour() {

    }
    void rollback() {

    }
};

double t = 100000;
double delta = 0.99999;

void upd_temp() {
    t = t*delta;
}

double p(int old, int ne) {
    if (ne > old) return 1.0;
    return exp((ne-old)/t);
}

void transition(state &current) {
    current.become_neighbour();
    if (p(current.oldscore, current.score)*1e9 >= randint(0, 1e9)) {
        // we go to current
        return;
    } else {
        current.rollback();
    }
}

int32_t main() {

}
