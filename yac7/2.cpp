#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> gen(int N, int M) {
	vector<vector<int>> ans(N+1, vector<int>(M+1));
	if (N == 1 or M == 1) return {{0}};
	if (N % 2 == 0 and M % 2 == 0) {
		int i = 0; int j = 0;
		int no = 1;
		for (;no<=N;no++) { ans[i][j] = no; i++;}
		for (j = 1; j < M; j+=2) {
			for (i = N-1; i > 0; i--) {
				ans[i][j] = no;
				no++;
			}
			for (int i = 1; i < N; i++) {
				ans[i][j+1] = no;
				no++;
			}
		}
		no = N+(M-1)*(N-1)+1;
		for (j = M-1; j > 0; j--) {ans[0][j] = no; no++;}
		return ans;
	}  
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		int N, M;
		cin >> N >> M;
		auto a = gen(N, M);
		if (a == {{0}}) {cout << "-1\n";continue;}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cout << a[i][j] << " \n"[j==M-1];
	}
}
