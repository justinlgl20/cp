#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;

using ll = long long;

struct mi {
 	int v;
	mi() { v = 0; }
	mi(ll _v) { v = int(_v%MOD); }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
 
void solve() {
	mi dp[101][101]{};
	bool send[101]{}, recei[101]{};
	bool adj[101][101]{};
	int in_deg[101]{}, out_deg[101]{}, deg[101]{};

	// setup
	int N,K; cin >> N >> K; assert(K <= 1);
	for (int i = 1; i <= N; ++i) {
		char c; cin >> c;
		if (c == 'S') send[i] = 1;
		if (c == 'R') recei[i] = 1;
	}
	int e_start = 0, e_end = 0;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			char c; cin >> c;
			if (c == '1') {
				adj[i][j] = 1;
				++out_deg[i], ++in_deg[j];
				if (i > j) e_start = i, e_end = j;
			}
		}
	for (int i = 1; i <= N; ++i) {
		assert(in_deg[i]+send[i] == out_deg[i]+recei[i]);
		deg[i] = in_deg[i]+send[i];
	}
	vector<mi> factorial(N+1); factorial[0] = 1;
	for (int i = 1; i <= N; ++i) factorial[i] = i*factorial[i-1];

	// now do DP
	dp[0][e_end] = 1;
	for (int i = 1; i <= N; ++i)
		for (int j = 0; j <= N; ++j) if (dp[i-1][j].v != 0) {
			assert(j == 0 || j >= i);
			if (j == i) {
				mi ad = dp[i-1][j]*factorial[deg[i]-1];
				if (j == e_start) dp[i][0] += (deg[i]-1)*ad;
				else {
					if (recei[j]) dp[i][0] += ad;
					for (int k = i+1; k <= N; ++k) if (adj[j][k]) dp[i][k] += ad;
				}
			} else {
				dp[i][j] += dp[i-1][j]*factorial[deg[i]];
			}
		}
	cout << dp[N][0].v << "\n";
}

int main() {
	int T; cin >> T;
	while (T--) solve();
}