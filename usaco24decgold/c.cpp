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

struct Job {
    int deadline, dur;
    bool operator < (Job other) const {
        return deadline < other.deadline;
    }
};

void solve() {
    int n; cin >> n;
    vector<Job> jobs(n);
    for (int i = 0; i < n; i++) {
        cin >> jobs[i].deadline >> jobs[i].dur;
        jobs[i].deadline += jobs[i].dur;
        dbg(jobs[i].deadline, jobs[i].dur);
    }
    jobs.push_back(Job{0, 0});
    sort(all(jobs));
    multiset<int> s;
    int ans = 0; 
    for (int i = jobs.size()-1; i >= 0; i--) {
        int t = jobs[i].deadline;
        if (i) {
            t -= jobs[i-1].deadline;
        }
        s.insert(jobs[i].dur);
        dbg(jobs[i].deadline, jobs[i].dur);
        while (t && s.size()) {
            auto it = s.begin();
            if ((*it) <= t) {
                t -= (*it);
                dbg("REMOVE", (*it));
                ans++;
            } else {
                dbg("TAKE SOME OUT OF", *it);
                s.insert((*it)-t);
                t = 0;
            }
            s.erase(it);
        }
        dbg(t, s);
    }
    cout << ans << "\n";
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
