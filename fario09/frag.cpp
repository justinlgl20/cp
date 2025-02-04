#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define f first
#define s second

int rand_pop(vector<int> &x) {
    int in = rand()%x.size();
    int v = x[in];
    x[in] = x.back();
    x.pop_back();
    return v;
}

int N, K, P;
pii pairs[100005];

vector<int> use;
unordered_map<int, unordered_map<int, int>> value;
bool is_in[1005];

int main() {
    srand(926);
    cin >> N >> K >> P;
    for (int i = 0; i < P; i++) {
        int a, b, v; cin >> a >> b >> v;
        pairs[i] = {a, b};
        value[a][b] = v;
        value[b][a] = v;
    }
    double temp = 20000;
    double alpha = 0.999999999;
   
    function<double(int, int)> P = [&](int ol, int ne) {
        if (ne > ol) return 1.0;
        return exp((ne-ol)/temp);
    };
    int score = 0;
    for (int i = 0; i < K; i++) {
        int r = rand()%N+1;
        while (is_in[r]) r = rand()%N+1;
        use.push_back(r);
        is_in[r] = false;
    }
    assert(use.size() == K);
    for (auto i : use) is_in[i] = true;
    for (int i = 0; i < K; i++) {
        for (int j = i+1; j < K; j++) {
            score += value[use[i]][use[j]];
        }
    }
    vector<int> best=use;
    int bestscore=score;
    int iter = 0;
    int progress = 0;
    while (temp > 1) {
        //cerr << "CUR: ";
        //for (auto i : use) cerr << i << " ";
        //cerr << "\n";
        temp *= alpha;
        int put_in = rand()%N+1;
        while (is_in[put_in]) put_in = rand()%N+1;
        int take_out = rand_pop(use);
        use.push_back(put_in);
        int new_score = score;

        //cerr << "TAKE OUT " << take_out << " and put in " << put_in << "\n";
        int add= 0;
        int lose = 0;
        for (int i = 0; i < K-1; i++) {
            lose -= value[use[i]][take_out];
            add += value[use[i]][put_in];
        }
        //cerr << lose << " "  << add << "\n";
        new_score += lose+add;
        function<void()> go_back = [&]() {
            use.pop_back();
            use.push_back(take_out);
        };
        if (P(score, new_score)*1e9 > rand()%1000000000) {
            score = new_score;
            is_in[put_in] = true;
            is_in[take_out] = false;
        } else {
            go_back();
        }
        if (score > bestscore) {
            bestscore = score;
            best = use;
            progress = iter;
        }
        if (iter%100000 == 0) cerr << temp << ": " << score << " " << bestscore << "\n";
        iter++;
        if (iter - progress > 4000000) {
            score = bestscore;
            for (int i : use) is_in[i] = false;
            use = best;
            for (int i : best) is_in[i] = true;
            progress = iter;
        }
    }
    cout << bestscore << "\n";
    for (int i = 0; i < best.size(); i++) cout << best[i] << "\n";
}
