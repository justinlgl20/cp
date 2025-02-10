#include "recovery.h"
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

static int C = -1;
static int N;
static vector<vector<int> > subsets;

static void bound_int(int x, int mn, int mx, string name) {
	if (x < mn || x > mx) {
		printf("Error: %s called with invalid argument\n", name.c_str());
		exit(0);
	}
}

void num_check_bits(int c) {
	bound_int(c, 1, 2*N, "num_check_bits");
	if (C != -1) {
		printf("Error: Called num_check_bits more than once\n");
		exit(0);
	}
	C = c;
	subsets = vector<vector<int> >(c);
}

void add_index(int x, int i) {
	if (C == -1) {
		printf("Error: Called add_index prior to calling num_check_bits\n");
		exit(0);
	}
	bound_int(x, 0, C-1, "add_index");
	bound_int(i, 0, N-1, "add_index");
	subsets[x].push_back(i);
}

int main() {
	int S;
	assert(scanf("%d%d", &N, &S) == 2);

	string id;
	for (int i = 0; i < N; i++) {
		char c;
		assert(scanf(" %c", &c) == 1);
		id.push_back(c);
	}

	vector<int> scratched;

	if (S == 1) {
		int a;
		assert(scanf("%d", &a) == 1);
		scratched.push_back(a);
	} else {
		int a, b;
		assert(scanf("%d%d", &a, &b) == 2);
		scratched.push_back(a);
		scratched.push_back(b);
	}

	set_scheme(N, S);

	for (int i = 0; i < C; i++) {
		if (subsets[i].empty()) {
			printf("Error: Empty check subset\n");
			exit(0);
		}
		sort(subsets[i].begin(), subsets[i].end());
		if (unique(subsets[i].begin(), subsets[i].end()) != subsets[i].end()) {
			printf("Error: Indexed added to subset more than once\n");
			exit(0);
		}

		int sum = 0;
		for (int index : subsets[i]) {
			sum += id[index] == '1';
		}

		id.push_back((sum%2) ? '1' : '0');
	}

	for (int i : scratched) {
		if (i < 0 || i > N+C-1) {
			printf("Error: Provided scratch bit doesn't exist\n");
			exit(0);
		}
		id[i] = '?';
	}

	string result = recover(id);

	printf("%s\n", result.c_str());
}
