#include <bits/stdc++.h>

using namespace std;

int p[1000005];
int good[1000005];
int rep(int u) {
    if (p[u] == u) return u;
    return p[u] = rep(p[u]);
}
void merge(int a, int b) {
    a = rep(a), b = rep(b);
    if (a == b) return;
    p[a] = b;
    good[b] = good[b] and good[a];
}

char graph[1005][1005];

int id(int i, int j) {
    return i*1001+j;
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> graph[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            good[id(i, j)] = graph[i][j] != '*';
        }
    }
    for (int i = 0; i < 1000003; i++) p[i] = i;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == 'X') continue;
            if (i > 0) {
                if (graph[i-1][j] != 'X') merge(id(i, j), id(i-1, j));
            }
            if (j > 0) {
                if (graph[i][j-1] != 'X') merge(id(i, j), id(i, j-1));
            }
            if (j < m-1) {
                if (graph[i][j+1] != 'X') merge(id(i, j), id(i, j+1));
            }
            if (i < n-1) {
                if (graph[i+1][j] != 'X') merge(id(i, j), id(i+1, j));
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (rep(id(i, j)) == id(i, j) and good[id(i, j)] and graph[i][j] != 'X') ans++;
        }
    }
    cout << ans << "\n";
}
