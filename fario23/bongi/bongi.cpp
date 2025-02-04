#include <bits/stdc++.h>
#include "bongi.hpp"
using namespace std;




void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif


#define ll long long

template <
    class result_t   = std::chrono::milliseconds,
    class clock_t    = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

int rand_pop(vector<int> &x) {
    int inx = rand()%(x.size());
    int g = x[inx];
    x[inx] = x.back();
    x.pop_back();
    return g;
}

double temp;
double alpha;

void temperature() {
    temp *= alpha;
}

double P(int old, int ne) {
    if (ne > old) return 1.0;
    return 0.0;
    return (double)exp((double)(ne-old)/temp);
}

double score(vector<int> cnt) {
    double x = 1;
    for (int i : cnt) {
        x *= i;
    }
    return x;
}

int32_t main()
{
  auto start = std::chrono::steady_clock::now();
  temp = 2000;
  alpha = 0.9999995;
  //////////////////////////////////////////////////
  // read the input
  // for (ll p = 1; p <= 8; p++)
  //{
  // cerr << (string("input_") + to_string(p) + ".txt").c_str() << endl;
  // freopen((string("input_") + to_string(p) + ".txt").c_str(), "r", stdin);
  // freopen((string("output_") + to_string(p) + ".txt").c_str(), "w", stdout);
  ll N, K;
  cin >> N >> K;

  vector<ll> A;
  ll x = 0;
  int S = 0;
  for (ll i = 0; i < N; i++)
  {
    ll h;
    cin >> h;
    S += h;
    A.push_back(h);
    x += h;
  }
  //cerr << "INPUT\n";
  sort(A.begin(), A.end());
  vector<ll> b(K);
  vector<int> sums(K);
  vector<vector<int>> solution(K);
  for (int i = 0; i < N; i++) {
      solution[i%K].push_back(A[i]);
      sums[i%K] += A[i];
  }

  vector<vector<int>> best = solution;
  double bscore = get_score(solution);
  int iter = 0;
  double G = get_best(S);
  srand(69);
  cerr << std::setprecision(12);
  int progress = 0;
  //while (get_score(solution) < G-0.01) {// or since(start).count() <= 80) {
  while (since(start).count() <= 1200000) {
      temperature();
      vector<vector<int>> sol = solution;
      dbg(sol)
      int a = rand()%K;
      int b = rand()%K;
      if (rand()%3 == 0 and sol[a].size()) {
          int c = rand_pop(sol[a]);
          sol[b].push_back(c);
      }
      else if (sol[a].size() and sol[b].size() and a != b){
        int c = rand_pop(sol[a]);
        int d = rand_pop(sol[b]); // this line
        sol[b].push_back(c);
        sol[a].push_back(d);
      } else continue;
      if (get_score(sol) >= bscore) {best = sol; bscore = get_score(sol);}
      if (P(get_score(solution), get_score(sol))*1e9 > rand()%10000000000) {
          solution = sol;
          progress = iter;
      }
      //if (iter - progress > 3000000){ solution = best; temp = 100; progress = iter;}
      iter++;
      if (iter % 100000 == 0) cerr << temp << ": " << get_score(sol) << " " << get_score(solution) << "\n";
  }
  best = solution;
  // MAKE ALL BUCKETS AS EQUAL AS POSSIBLE
  // K buckets
  // N elements
  // put elements in buckets to maximise the product of the sum of the buckets

    //////////////////////////////////////////////////
  // write the output  // functions in bongi.hpp
  cerr << "score = " << get_score(best) << endl;
  cerr << "percentage = " << get_percentage(best) << "%" << endl;

  for (ll k = 0; k < (ll)best.size(); k++)
  {
    for (ll j = 0; j < (ll)best[k].size(); j++)
    {
      if (j)
        cout << " ";
      cout << best[k][j];
    }
    cout << endl;
  }
  //}
}
