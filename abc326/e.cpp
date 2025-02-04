#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

int a[300005];
double ways[300005];
double total[300005];

const int mod = 998244353;

int32_t main() {
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    ways[0] = 1;
    total[0] = 0;
    double sum_so_far = 0;
    double ways_so_far = 1;
    for (int i = 1; i <= N; i++) {
        ways[i] = (double)ways_so_far/(double)N;
        ways_so_far += ways[i];
        total[i] = (double)sum_so_far/(double)N + (double)a[i];
        sum_so_far += total[i];
    }
    //sum_so_far = ways_so_far * z (mod thingy);
    cerr << sum_so_far << " " << ways_so_far << "\n";
    int z = sum_so_far*mod/ways_so_far;
    z %= mod;
    cout << z << "\n";

}
