inline int lastbit(int x) {
  return x & (-x);
}

template <int... ArgsT> struct BIT {
  int val = 0;
  void update(int val) {
    this->val += val;
  }
  int query() {
    return val;
  }
};

template <int N, int... Ns>
struct BIT<N, Ns...> {
  BIT<Ns...> bit[N + 1];
  template<typename... Args>
  void update(int pos, Args... args) {
    for (; pos <= N; bit[pos].update(args...), pos += lastbit(pos));
  }
  template<typename... Args>
  int query(int l, int r, Args... args) {
    int ans = 0;
    for (; r >= 1; ans += bit[r].query(args...), r -= lastbit(r));
    for (--l; l >= 1; ans -= bit[l].query(args...), l -= lastbit(l));
    return ans;
  }
};

