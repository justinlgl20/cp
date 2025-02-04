#include "celebrities.h"
#include <bits/stdc++.h>
using namespace std;

bool ask_question(int i, int j) {
    cout << "? " << i << " " << j << ": ";
    int ans; cin >> ans; cout << "\n";
    return ans;
}

int main() {
    int N; cin >> N;
    vector<int> g = find_celebrities(N);
    for (auto i : g) cout << i << " ";
    cout << "\n";
}
