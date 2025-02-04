template<typename T>
struct lichao {
	int tl, tr;
	T val;
	lichao *l, *r;
	lichao(int tl,int tr): tl(tl), tr(tr), val(),l(NULL),r(NULL){}
	void add(T v){
		int tm=(tl+tr)/2;
		if(val.get(tm)<v.get(tm))swap(v,val); // v is worse
		if(tl==tr)return;
		if(v.get(tl)>val.get(tl)){
			if(l==NULL)l=new lichao(tl,tm);
			l->add(v);
		}
		else if(v.get(tr)>val.get(tr)){
			if(r==NULL)r=new lichao(tm+1,tr);
			r->add(v);
		}
	}
	int query(int x) {
		int tm=(tl+tr)/2;
		int ans=val.get(x);
		if(tl==tr)return ans;
		if(l!=NULL and x<=tm)ans=max(ans,l->query(x));
		if(r!=NULL and x>tm)ans=max(ans,r->query(x));
		return ans;
	}
};
