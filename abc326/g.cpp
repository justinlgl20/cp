#include <bits/stdc++.h>
using namespace std;

int N, M;
int C[55];
vector<int> L[55];

int cost(int u, int j) {
    int c = 0;
    for (int i = 1; i <= N; i++) {
        if (L[u][i] < L[j][i]) {
            c += (L[j][i] - L[u][i])*C[i];
        }
    }
    return c;
}
