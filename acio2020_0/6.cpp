#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second
int n, m;
multiset<int> idek;
int val[1005][1005];
int psa[1005][1005];

int sum(int a, int b, int A, int B) {
    return psa[A][B]-psa[a-1][B]-psa[A][b-1]+psa[a-1][b-1];
}

void build() {
    for (int i= 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            psa[i][j] = val[i][j]+psa[i-1][j]+psa[i][j-1]-psa[i-1][j-1];
        }
    }
}

int main() {
    int k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> val[i][j];
        }
    }
    for (int i = 1; i <= n-k; i++) {
        for (int j = 1; j <= m; j++) {
            idek.insert(sum(i, j, i+k, j));
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m-k; j++) {
            idek.insert(sum(i, j, i, j+k));
        }
    }
    for (int j = 1; j <= m; j++) {
        //remove all relating to (1, j) to (k, j)
        for (int i = 2; i <=
        //insert stuff
    }
}
