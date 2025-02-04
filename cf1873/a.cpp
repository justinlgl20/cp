#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string a; cin >> a;
        bool g= 1;
        if (a == "bca") g = 0;
        if (a == "cab") g = 0;
        cout << (g?"YES":"NO") << "\n";
    }
}
