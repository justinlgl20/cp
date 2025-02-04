#include <bits/stdc++.h>
using namespace std;

int n;
int a[4002][4002];
struct BIT {
    int bit[4004][4004];
    BIT() {
        for (int i = 1; i <= 4003; i++) for (int j = 1; j <= 4003; j++) bit[i][j] = 0;
    }
    void update(int x, int y, int val) {
        for (; x <= n; x += (x & (-x))) {
            for (int i = y; i <= n; i += (i & (-i))) { bit[x][i] += val; }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        int ans = 0;
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        return ans;
    }
}
int main() {
    int N, M; cin >> N >> M;
    BIT x;
    BIT shiftL;
    BIT shiftR;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> a[i+j-1][N+j-i];
            x.update(i+j-1, N+j-i, a[i+j-1][N+j-i]);
            shiftL.update(i+j-1, N+j-1
        }
    }

}
