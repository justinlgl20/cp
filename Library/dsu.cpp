struct dsu{
	vector<int> p;
	dsu(int n) : p(n+3,-1) {}
	int rep(int u){
		if(p[u]<0)return u;
		return p[u]=rep(p[u]);
	}
	void merge(int a,int b){
		a=rep(a),b=rep(b);
		if(p[a]<p[b]) swap(a,b);
		sz[b]+=sz[a];
		p[a]=b;
	}
};
