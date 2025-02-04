#include <bits/stdc++.h>
using namespace std;

const int MOD = 10000;

char idk[7][55];
int dp[7][55][2]; // row, col, if other thing is available

int main() {
    int W, L;
    cin >> W >> L;
    bool works = true;
    for (int i = 1; i <= W; i++) {
        for (int j = 1; j <= L; j++) {
            cin >> idk[i][j];
            works = works&(idk[i][j] != '.');
        }
    }
    if (W == 1) {
        if (works) cout << "1\n";
        else cout << "0\n";
        return 0;
    }
    dp[1][1][1] = 1;
    for (int i = 1; i <= W; i++) {
        for (int j = 1; j <= L; j++) {
            if (i == 1 and j == 1) continue;
            // dp[i][j] can come from dp[i|1][j], dp[i][j-1], dp[i|1][j-1]
            
            //dp[i][j][0] = //other side not available
            if ((dp[i][j-1] == 'S' or dp[i][j-1] == 'X') and dp[i|1][j-1] == '.') {
                dp[i][j][0] += 
            }
            if (idk[i|1][j] == '.') {
                dp[i][j][1] = 0;
            } else {

            }
        }
    }
}
