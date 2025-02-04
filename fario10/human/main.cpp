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

int r, c;

int grid[100005];
int ideal[100005];

int randint(int l, int r) {
    return rand()%(r-l+1)+l;
}

int id(int i, int j) {
    return c*i+j;
}

int get_score(vector<pii> &edges) {
    int ans = 0;
    for (auto i : edges) {
        ans += (grid[edges.f] == ideal[edges.s]);
        ans += (grid[edges.s] == ideal[edges.f]);
    }
    return ans;
}

state {
    int oldscore;
    int score;
    //info
    vector<pii> edges;

    vector<pii> removed;
    vector<pii> added;
    vector<int> free;

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

vector<pii> ans;
int best_score = 0;

void transition(state &current) {
    current.become_neighbour();
    if (p(current.oldscore, current.score)*1e9 >= randint(0, 1e9)) {
        // we go to current
        return;
    } else {
        current.rollback();
    }
    if (current.score >= best_score) {
        ans = current.edges;
        best_score = current.score;
    }
    upd_temp();
}

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int32_t main() {
    auto start = std::chrono::steady_clock::now();
    cin >> r >> c;
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> grid[id(i, j)];


    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> ideal[id(i, j)];
    
    state curr;
    
    // greedy;

    while (since(start) < 2000) {
        transition(curr);
    }
}
