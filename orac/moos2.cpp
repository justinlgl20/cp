#include <bits/stdc++.h>
using namespace std;

int w, l;
char col[24];

vector<int> neighbours(int u) {
    vector<int> ans;
    if (u % l != 0 and (int)u/l+1 != w) {
        ans.push_back(u+l-1);
    }
    if ((int)u/l+1 != w) {
        ans.push_back(u+l);
    }
    if ((int)u/l+1 != w and u%l != l-1) {
        ans.push_back(u+l+1);
    }
    if (u % l != 0) {
        ans.push_back(u-1);
    }
    if (u % l != l-1) {
        ans.push_back(u+1);
    }
    if ((int)u/l+1 != 1) {
        ans.push_back(u-l);
    }
    if ((int)u/l+1 != 1 and u%l != 0) {
        ans.push_back(u-l-1);
    }
    if ((int)u/l+1 != 1 and u%l != l-1) {
        ans.push_back(u-l+1);
    }
    vector<int> tru;
    for (auto i : ans) {
        if (col[i] != '.') tru.push_back(i);
    }
    return tru;
}

vector<int> adj[24];
bool is_in(int x, int q) {
    for (auto i : adj[q]) if (i == x) return 1;
    return 0;
}

int id[7][55];
int main() {
    cin >> w >> l;
    vector<vector<char>> colour(w+2, vector<char>(l+2));
    int cnt = 0;
    for (int i = 1; i <= w; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> colour[i][j];
            id[i][j] = cnt++;
            col[cnt-1] = colour[i][j];
        }
    }
    int elements = cnt;
    for (int i = 0; i < elements; i++) adj[i] = neighbours(i);
    int ans = 0;
    for (int i = 0; i <= 1<<(elements)-1; i++) {
        //use bits to determine whether i is in thingy
        vector<int> thingy;
        for (int j = 0; j < elements; j++) {
            if (i&(1<<j)) thingy.push_back(j);
        }
        int n = thingy.size();
        do {
            bool works = true;
            for (int i = 1; i < thingy.size(); i++) {
                if (!is_in(thingy[i], thingy[i-1])) works = false;
            }
            if (works) ans++;
        } while (next_permutation(thingy.begin(), thingy.end()));
    }
    cout << ans << "\n";
}
