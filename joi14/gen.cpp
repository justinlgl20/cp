#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(69);
    int N = rand()%20+5;
    int Q = rand()%10+3;
    cout << N << " " << Q << "\n";
    for (int i = 1; i < N; i++) {
        cout << i << " " << rand()%i << " " << rand()%50 << "\n";
    }
    while (Q--) {
        int s = rand()%(N/4)+2; int t = rand()%(N/4)+2;
        cout << s << " " << t << "\n";
        set<int> ses;
        for (int i = 0; i < s; i++) {
            int g = rand()%N;
            while (ses.find(g) != ses.end()) g = rand()%N;
            ses.insert(g);
            cout << g << " \n"[i==s-1];
        }
        set<int> tes;
        for (int i = 0; i < t; i++) {
            int g = rand()%N;
            while (tes.find(g) != tes.end()) g = rand()%N;
            tes.insert(g);
            cout << g << " \n"[i==t-1];
        }
    }
}
