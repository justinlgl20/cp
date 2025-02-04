#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    vector<char> s(n, 0);
    for (int i = 0; i < n; i++) cin >> s[i];
    vector<int> val(n, 0);
    vector<int> psa(n+2, 0);
    for (int i = 0; i < n-1; i++) {
        val[i] = s[i]==s[i+1];
        psa[i+1] = psa[i]+val[i];
    }
    psa[n] = psa[n-1];
    while (q--) {
        int l, r; cin >> l >> r;
        cout << psa[r-1]-psa[l-1] << "\n";
    }
}
