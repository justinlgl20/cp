#include <bits/stdc++.h>
using namespace std;


#define all(x) (x).begin(), (x).end()

template<template<typename> class Container, typename T>
ostream& operator << (ostream& os, Container<T> d) {
    int s = d.size();
    os << "{";
    for (auto &i : d) os << i << (--s?", ":"}");
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
#define dbg(x...) cerr << "\e[91m" << __func__ <<":" << __LINE__ << " [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...) 
#endif

int dp[1005][5005]; // ends at i
pair<int, int> from[1005][5005];
int last0[1005];

int N;
string P;

int get(int i, int j) {
    if (0 <= i and i <= N and 0 <= j and j <= 5000) return dp[i][j];
    return 1e9;
}

int num(char g) {
    if (g == 'g') return 1e8;
    return g - '0';
}

char get(int inx) {
    if (0 <= inx and inx < P.size()) return P[inx];
    return 'g';
}

int get(pair<int, int> g) {
    return get(g.first, g.second);
}

void setto(int i, int j, vector<pair<int, int>> g) {
    vector<int> pos = {get(g[0])+(g[0].second == 0?0:1), get(g[1])+(g[0].second == 0?0:1), get(g[2])+(1, get(g[3])+1, get(g[4])+1};
    dp[i][j] = min({pos[0], pos[1], pos[2], pos[3]});
    if (dp[i][j] == pos[4]) from[i][j] = g[4];
    else if (dp[i][j] == pos[0]) from[i][j] = g[0];
    else if (dp[i][j] ==pos[1]) from[i][j] = g[1];
    else if (dp[i][j] == pos[2]) from[i][j] = g[2];
    else from[i][j] = g[3];
}

int32_t main() {
#ifndef DEBUG
    freopen("bingle.in", "r", stdin);
    freopen("bingle.out", "w", stdout);
#endif
    int H; cin >> P >> H;
    N = P.size();
    P = "0"+P;
    for (int i = 0; i <= 1001; i++) for (int j = 0; j <= 5005; j++) dp[i][j] = 1e7;
    dp[0][0] = 0;
    int start = 0;
    for (int i = 1; i <= N; i++) {
        last0[i] = start;
        dbg(last0[i], i);
        if (P[i] != '0') start = i;
    }
    for (int i = 1; i <= N; i++) {
        // dp[i] can come from dp[i-1], dp[i-2], dp[i-3], dp[i-4];
        // from dp[i-1], dp[i][j] = dp[i-1][j - P[i]] +1
        for (int j = 0; j <= 5002; j++) {
            vector<pair<int, int>> g = {
                    make_pair(i-1, j - num(P[i])),
                    make_pair(i-2, j - num(P[i])-num(get(i-1))*10),
                    make_pair(i-3, j - num(P[i])-num(get(i-1))*10-num(get(i-2))*100),
                    make_pair(i-4, j - num(P[i])-num(get(i-1))*10-num(get(i-2))*100-num(get(i-3))*1000),
                    make_pair(last0[i-3], j - num(P[i])-num(get(i-1))*10-num(get(i-2))*100-num(get(i-3))*1000)
                    };
            setto(i, j, g);
            //dbg(i, j, dp[i][j]);
        }
    }
    vector<int> breaks = {};
    int f = N;
    int s = H;
    while (f != 0) {
        dbg(f, s);
        breaks.push_back(f);
        pair<int, int> g = from[f][s];
        f = g.first;
        s = g.second;
    }
    reverse(all(breaks));
    dbg(breaks);
    breaks.pop_back();
    vector<char> ans;
    for (int i = N; i > 0; i--) {
        if (i == breaks.back()) {
            ans.push_back(' ');
            breaks.pop_back();
        }
        ans.push_back(P[i]);
    }
    reverse(all(ans));
    int last_non_zero = 0;
    vector<vector<char>> answers;
    vector<char> cur;
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] == ' ') {answers.push_back(cur); cur = {};}
        else {
            cur.push_back(ans[i]);
        }

    }
    if (cur.size()) answers.push_back(cur);
    dbg(answers);
    vector<bool> merge(1002);
    for (int i = 0; i < answers.size(); i++) {
        int m = true;
        for (char j : answers[i]) m = m and (j == '0');
        merge[i] = m;
    }
    for (int i = 0; i < answers.size(); i++) {
        for (char j : answers[i]) cout << j;
        if (!merge[i]) cout << " ";
    }
    cout << "\n";
}
