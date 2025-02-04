#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> e;
vector<int> o;
int vals[1000005];

int32_t main() {
	int N; cin >> N;
	for (int i = 0; i < N; i++)
	{
		int x; cin >> x;
		if (x % 2 == 0) e.push_back(i+1);
		else o.push_back(i+1);
		vals[i+1] = x;
	}
	vector<int> order;
	int no = 0;
	bool added_o = false;
	if (o.size()) {
		added_o = true;
		int x = o.back();
		o.pop_back();
		order.push_back(x);
		no += (vals[x]-1)/2;
	}
	for (auto i : e) {
		order.push_back(i);
		if (added_o) {
			no += (vals[i]/2-1);
		}
		else {
			no += vals[i]/2;
		}
	}
	int cur_inx;
	if (added_o) cur_inx = 0;
	else cur_inx = 1;	
	for (auto i : o) {
		order.push_back(i);
		if (cur_inx == 1) no += (vals[i]/2);
		else no+= (vals[i]/2);
		cur_inx = (cur_inx+1)/2;
	}
	cout << no << "\n";
	for (auto i : order) cout << i << " ";
	cout << "\n";
}
