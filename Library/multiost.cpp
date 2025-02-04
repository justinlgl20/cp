template<typename T>
struct multi_ordered_set {
	tree<pair<T, int>, null_type, less<pair<T,int>>, rb_tree_tag,tree_order_statistics_node_update> x;
	int cnt;
	multi_ordered_set() { x.clear();cnt=0; }
	void insert(T i) { x.insert(make_pair(i,cnt++)); }
	void erase(T i) { x.erase(x.lower_bound(make_pair(i,0))); }
	T find_by_order(int i) { return (*(x.find_by_order(i))).f; }
	int order_of_key(T i) { return x.order_of_key(make_pair(i, 1e9)); }
	int size() { return x.size(); }
	auto begin() { return x.begin(); }
	auto end() { return x.end(); }
	void clear() { x.clear(); }
};
