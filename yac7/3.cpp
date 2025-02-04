#include <bits/stdc++.h>
using namespace std;

vector<int> adj[1000005];

int child[1000005];
vector<int> find_cycle(int start) {
	int a = child[start];
	int b = child[child[start]];
	while (a != b) {
		a = child[a];
		b = child[child[b]];
	}
	a = start;
	while (a != b) {
		a = child[a];
		b = child[b];
	}
	int first = a;
	b = child[a];
	int length = 1;
	vector<int> cycle = {a};
	while (a != b) {
		cycle.push_back(b);
		b = child[b];
	}
	return cycle;

}

int par[1000005];

int rep(int u) {
	if (par[u] == u) return u;
	return par[u] = rep(par[u]);
}

void merge(int a, int b) {
	a = rep(a);
	b = rep(b);
	if (a != b)
		par[a] = b;
}

int indeg[1000005];
int is_in_cycle[1000005];
int is_line[1000005];
int length[1000005];
vector<int> cycles[1000005];
int inxes[1000005];
int connection[1000005];

int main() {
	int N; cin >> N;
	for (int i = 1; i <= N; i++) {
		par[i] = i;
		int x; cin >>x;
		adj[i].push_back(x);
		child[i] = x;
		indeg[x] ++;

	}
	for (int i = 1; i <= N; i++) { // APPARANTLY SOMETHING WRONG WITH THIS PART
		merge(i, child[i]);
	}

	vector<int> comps;
	for (int i = 1; i <= N; i++) {
		if (par[i] == i) comps.push_back(i);
	}
	//cerr << "FOUND COMPS\n";
	for (auto i : comps) {
		vector<int> cycle = find_cycle(i);
		bool line = false;
		cycle.push_back(cycle.back());
		for (int j = 0; j < cycle.size()-1; j++)
			if (child[cycle[j]] != cycle[j+1]) line = true;
		cycle.pop_back();
		//cerr << "COMPONENT: " << i << "\n";
		for (auto j = 0; j < cycle.size(); j++) {
			//cerr << j << "\n";
			inxes[cycle[j]] = j;
			is_in_cycle[cycle[j]] = true;
		}
		cycles[i] = cycle;
	}
	//cerr << "FOUND CYCLES\n";
	vector<int> leaves;
	for (int i = 1; i <= N; i++) {
		if (indeg[i] == 0) {
			leaves.push_back(i);
			int l = 1;
			int u = i;
			while (!is_in_cycle[u]) {
				u = child[u];
				l++;
			}
			connection[i] = u;
			l--;
			length[i] = l;
		}
	}
	//cerr << "FOUND LEAVES\n";
	int longest_length = 0;
	int node = 0;
	for (auto i : leaves) {
		if (length[i] > longest_length) {
			longest_length = length[i];
			node = i;
		}
	}
	int A, B;
	if (longest_length == 0) {
		A = 1;
		B = child[A];
	} else {
		int n = connection[node];
		vector<int> c = find_cycle(node);
		int inx = inxes[n]-1;
		if (inx == -1) inx = c.size()-1;
		A = c[inx];
		B = node;
	}
	indeg[child[A]]--;
	indeg[B] ++;
	cout << A << " " << B << "\n";
	child[A] = B;
	int aff_comp = rep(A);
	for (auto i : cycles[aff_comp]) is_in_cycle[i] = false;
	cycles[aff_comp] = find_cycle(A);
	for (auto i : cycles[aff_comp]) is_in_cycle[i] = true;
	for (int i = 0; i < cycles[aff_comp].size(); i++) inxes[cycles[aff_comp][i]] = i;
	vector<int> vals(N+4, 0);
	vector<int> from(N+5, 0);
	//cerr << "FOUND ALL STUFF\n";
	for (int i = 1; i <= N; i++) {
		if (vals[i] != 0) continue;
	       	if (is_in_cycle[i]) vals[i] = i;
		else if (indeg[i] == 0) {
			int n = i;
			while (!is_in_cycle[n]){ 
				from[child[n]] = n;
				n = child[n];
			}
			int inx = inxes[n];
			while (n != i) {
				vals[n] = cycles[rep(i)][inx];
				n = from[n];
				inx--;
				if (inx == -1) inx = cycles[rep(i)].size()-1;
			}
			vals[n] = cycles[rep(i)][inx];
		}
	}
	for (int i = 1; i <= N; i++) {
		cout << vals[i] << " ";
	}
	cout << "\n";

			
			
}

