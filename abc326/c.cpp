#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<int> positions;
    for (int i = 0; i < N; i++) {
        int a; cin >> a;
        positions.push_back(a);
    }
    sort(positions.begin(), positions.end());
    int best = 0;
    for (int i = 0; i < N; i++) {
        // i is start
        int en = i;
        for (int j = 1<<30; j > 0; j >>= 1) {
            if (j+en < N and positions[j+en] < positions[i]+M) en += j;
        }
        best = max(best, en-i+1);
    }
    cout << best << "\n";
}
