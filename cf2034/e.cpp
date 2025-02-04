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

int factorial(int k) {
    int ans = 1;
    for (int i = 1; i <= k; i++) ans *= i;
    return ans;
}

void solve() {
    int n, k; cin >> n >> k;
    dbg(n, k);
    if (k == 1 and n == 1) {
        cout << "Yes\n1\n";
        return;
    } else if (k == 1) {
        cout << "No\n";
        return;
    }
    if((n % 2 == 0 and k % 2 == 1) or (n < 13 and factorial(n) < k))  {
        cout << "NO\n";
        return;
    }
    if (n >= 5) {
        vector<vector<int>> ans;
    
        if (k % 2 == 0) {
            vector<int> s;
            for (int i = 1; i <= n; i++) s.push_back(i);
            for (int i = 0; i < k/2; i++) {
                ans.push_back(s);
                vector<int> rs;
                for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                ans.push_back(rs);
                dbg(i, s);
                next_permutation(s.begin(), s.end());
            }
        }
        else if (n % 2 == 1 and k % 2 == 1) {
            vector<int> s;
            for (int i = 1; i <= n; i++) s.push_back(i);

            vector<int> ne(n);
            int cnt = 1;
            for (int i = 1; i < n; i+=2) {
                ne[i] = -cnt;
                cnt++;
            }
            cnt = n/2;
            for (int i = 0; i < n-1; i+=2) {
                ne[i] = cnt;
                cnt--;
            }
            vector<int> w;
            vector<int> qw = s;
            for (int i = 0; i < n; i++) {
                qw[i] += ne[i];
                w.push_back(-ne[i] + n/2 + 1ll);
            }
            vector<int> rs;
            for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
            dbg(qw);
            ans.push_back(qw);
            ans.push_back(w);
            ans.push_back(rs);

            dbg("HI");
            next_permutation(all(s));
           for (int i = 0; i < k/2 - 1ll; i++) {
                rs.clear();
                for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                int g = ans.size();
                if (rs == w or rs == qw or s == w or s == qw) {
                    next_permutation(all(s));
                    rs.clear();
                    for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                }
                ans.push_back(rs);
                ans.push_back(s);
                next_permutation(s.begin(), s.end());
            }
                        
        }
        cout << "Yes\n";
        for (auto i : ans) {
            for (auto j : i) cout << j << " ";
            cout << "\n";
        }
    } else {
        set<vector<int>> ans;
        if (k % 2 == 0) {
            vector<int> s;
            for (int i = 1; i <= n; i++) s.push_back(i);
            for (int i = 0; i < k/2; i++) {
                vector<int> rs;
                for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                int g = ans.size();
                while (ans.find(s) != ans.end() or ans.find(rs) != ans.end()) {
                    next_permutation(s.begin(), s.end());
                    rs.clear();
                    for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                }
                ans.insert(rs);
                ans.insert(s);
            }
        }
        else if (n % 2 == 1 and k % 2 == 1) {
            vector<int> s;
            for (int i = 1; i <= n; i++) s.push_back(i);

            vector<int> ne(n);
            int cnt = 1;
            for (int i = 1; i < n; i+=2) {
                ne[i] = -cnt;
                cnt++;
            }
            cnt = n/2;
            for (int i = 0; i < n-1; i+=2) {
                ne[i] = cnt;
                cnt--;
            }
            vector<int> w;
            vector<int> qw = s;
            for (int i = 0; i < n; i++) {
                qw[i] += ne[i];
                w.push_back(-ne[i] + n/2 + 1ll);
            }
            vector<int> rs;
            for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
            dbg(qw);
            ans.insert(qw);
            ans.insert(w);
            ans.insert(rs);

            dbg("HI");
            next_permutation(all(s));
           for (int i = 0; i < k/2 - 1ll; i++) {
                rs.clear();
                for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                int g = ans.size();
                while (ans.find(s) != ans.end() or ans.find(rs) != ans.end()) {
                    next_permutation(s.begin(), s.end());
                    rs.clear();
                    for (int i = n-1; i >= 0; i--) rs.push_back(s[i]);
                }
                ans.insert(rs);
                ans.insert(s);
            }
                        
        }
        cout << "Yes\n";
        for (auto i : ans) {
            for (auto j : i) cout << j << " ";
            cout << "\n";
        }

    }
    /*set<vector<int>> vs;
    for (auto i : ans) vs.insert(i);
    if (vs.size() != k) {
        cout << "No\n";
        return;
    }*/
    
}

int32_t main() {
    int t; cin >> t;
    while (t--) solve();
}
