#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

int nxt() {
    int x; cin >> x; return x;
}

int main() {
    int N = nxt();
    vector<int> a(N);
    generate(all(a), nxt);
    int g = *max_element(all(a));
    int best = 0;
    for (int i : a) if (i != g) best = max(best, i);
    cout << best << "\n";
}
