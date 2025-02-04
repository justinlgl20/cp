#include <bits/stdc++.h>
using namespace std;

signed main(){
	fstream log("log.txt");
	int n, m;
	cin >> n >> m;
	cout << n << " " << m << "\n";
	log << n << " " << m << "\n";
	vector<vector<pair<int, int>>> adj(n);
	for (int a, b, c; m--;){
		cin >> a >> b >> c;
		cout << a << " " << b << "\n";
		log << a << " " << b << "\n";
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}
	cout.flush();
	long long dist[n][n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dist[i][j] = -1;
	for (int start = 0; start < n; start++){
		priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		pq.push({0ll, start});
		while (!pq.empty()){
			if (!~dist[start][pq.top().second]){
				dist[start][pq.top().second] = pq.top().first;
				for (auto i : adj[pq.top().second])
					pq.push({pq.top().first+i.second, i.first});
			}
			pq.pop();
		}
	}
	int queries = 0;
	while (1){
		char a;
		cin >> a;
		log << a << " ";
		if (a == '?'){
			queries++;
			if (queries > 1000){
				log << "Too many guesses :(" << endl;
				return 0;
			}
			int b;
			cin >> b;
			int c;
			cin >> c;
			log << b << " " << c << "\n";
			cout << dist[b][c] << endl;
			log << dist[b][c] << "\n";
			cout.flush();
		} else if (a == '!'){
			long long b;
			cin >> b;
			log << b << "\n";
			log << "You answered " << b << " with " << queries << " queries!" << endl;
			return 0;
		} else {
			log << "Invalid query" << endl;
			return 0;
		}
	}
}
