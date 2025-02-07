#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
void _print() {cerr << "]\n";}
 
template<typename T, typename... V>
void _print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>
#define f first
#define s second

struct graph {
    vector<vector<pii>> adj;
    int n;
    graph(int n) {
        this->n = n;
        adj.resize(n+4);
        for(int i=0;i<n+3;i++)adj[i].clear();
    }
    void ae(int u, int v, int w) {
        adj[u].emplace_back(v,w);
    }
    vector<int> from;
    vector<int> bfs(int s) {
        vector<int> dist(n+4,1e18);
        dist[s]=0;
        queue<int> q;
	from.assign(n+4,0);
        q.push(s);
        while (q.size()) {
            int u=q.front();
            q.pop();
            for(auto i:adj[u]){
                if(dist[i.f]==1e18){
                    dist[i.f]=i.s+dist[u];
		    from[i.f]=u;
                    q.push(i.f);
                }
            }
        }
        return dist;
    }
};
struct dsu{
	vector<int> p, sz;
	dsu(int n) : p(n+3,-1), sz(n+3,1){}
	int rep(int u){
		if(p[u]<0)return u;
		return p[u]=rep(p[u]);
	}
	void merge(int a,int b){
		a=rep(a),b=rep(b);
		if(a==b)return;
		if(p[a]<p[b]) swap(a,b);
		sz[b]+=sz[a];
		p[a]=b;
	}
};

vector<int> adj[100005];
int a[400005],b[400005];
int deg[100005];

int32_t main() {
	int n,m;cin>>n>>m;
	graph g = graph(n+3);
	dsu uf = dsu(n+3);
	for(int i=0;i<m;i++){
		int u,v;cin>>u>>v;adj[u].push_back(v);adj[v].push_back(u);
		g.ae(u,v,1);
		g.ae(v,u,1);
		deg[u]++;deg[v]++;
		dbg(u,v,1);
		uf.merge(u,v);
		a[i]=u;b[i]=v;
	}
	int q;cin>>q;
	function<void()> fail=[&]() {
		cout<<"NO\n";
		exit(0);
	};
	vector<int> colour(n+4,0); // 1 is blue, 2 is red
	bool got3=0;
	for(int i=1;i<=n;i++){
		if(colour[i]==1)continue;
		vector<int> dist=g.bfs(i);
		dbg(i, dist);
		for(int j=1;j<=n;j++){
			if(j==i or uf.rep(i)!=uf.rep(j))continue;
			if(dist[j]>3)fail();
			if(dist[j]==3 and colour[j]==1){
				fail();
			}
			if(dist[j]==3){
				got3=1;
				dbg(i,j);
				if(colour[i]!=2) {
					colour[i]=2;
					for(auto jw : adj[i]){
						if(colour[jw]==2)fail();
						colour[jw]=1;
					}
				}
				if(colour[j]!=2) {
					colour[j]=2;
					for(auto jw : adj[j]){
						if(colour[jw]==2)fail();
						colour[jw]=1;
					}
				}
			}
		}
	}
	vector<int> inside;
	for(int i=1;i<=n;i++){
		//if(colour[i]==0)colour[i]=2;
		if(colour[i]==1){
			inside.push_back(i);
		}
		dbg(i, colour[i]);
	}

	vector<pii> sizes;
	int main_comp = 0;
	for(int i=1;i<=n;i++){
		if(uf.rep(i)==i)sizes.emplace_back(uf.sz[i], i);
	}
	sort(all(sizes));
	if(sizes.size()>=2 and sizes[sizes.size()-2].f > 1)fail();
	main_comp = sizes.back().s;
	if (!got3) {
		// ADDING THIS MADE SOME WRONG AND SOME RIGHT
		// THERE ARE ONLY PATHS OF LENGTH 2
		for (int i=1;i<=n;i++){
			if(uf.rep(i) !=main_comp)continue;
			int bw=0;
			for(auto j:adj[i])bw+=(deg[j]>1);
			if(bw>=2)continue;
			vector<int> rem(n+4,0);
			for(auto j : adj[i])rem[j]=deg[j]==1;
			int cnt=0;
			for(int j=1;j<=n;j++){
				if(uf.rep(j)!=main_comp)continue;
				cnt+=rem[j]==0;
			}
			int wq=0;
			for(int j=0;j<m;j++){
				if(rem[a[j]]==rem[b[j]]){
					if(rem[a[j]]==0)wq++;
				}
			}
			if(wq!=(cnt)*(cnt-1ll)/2)continue;
			cout<<"YES\n";
			return 0;
		}
		// DOESN'T CHANGE ANYTHING UNLESS I PUT A FAIL HERE

	}
	int biggest = sqrt(m)+50;
	
	int cnt=0;
	
	for(int i=0;i<m;i++){
		if(colour[a[i]]==colour[b[i]]){
			if(colour[a[i]]==1){
				cnt++;
			} else if (colour[a[i]]==2){
				fail();
			}
		}
	}
	int k = inside.size();
	if(cnt != (k)*(k-1ll)/2) fail();
	cout<<"YES\n";
}
