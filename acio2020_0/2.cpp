#include <bits/stdc++.h>
using namespace std;


void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif


int main() {
#ifndef DEBUG
    freopen("jewelsin.txt", "r", stdin);
    freopen("jewelsout.txt", "w", stdout);
#endif
    int N;
    cin >> N;
    vector<int> things;
    vector<char> idk;
    for (int i = 0; i < N; i++) {char c; cin >> c; idk.push_back(c);}
    bool last = idk[0]=='r';
    int length = 0;
    for (int i = 0; i < N; i++) {
        char c = idk[i];
        idk.push_back(c);
        bool a = c=='r';
        if (a == last) length++;
        else {
            things.push_back(length);
            length = 1;
            last = a;
        }
    }
    if (idk[N-1] == idk[0]) {
        if (!things.size()) things.push_back(length);
        else things[0] += length;
    }
    else
        things.push_back(length);
    dbg(things);
    if (things.size() == 1) cout << N << "\n";
    else {
        things.push_back(things[0]);
        int best = 0;
        for (int i = 1; i <= things.size()-1; i++) {
            dbg(things[i], things[i-1]);
            best = max(best, things[i]+things[i-1]);
        }
        dbg(best);
        cout << best << "\n";
    }
}
