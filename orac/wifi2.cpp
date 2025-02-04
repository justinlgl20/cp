#include <bits/stdc++.h>
using namespace std;





#define pii pair<double, double>
#define f first
#define s second

#define x f
#define y s

pii centre(pii a, pii b, pii c) {
    double ydeltaa = b.y-a.y;
    double xdeltaa = b.x - a.x;
    double ydeltab = c.y - b.y;
    double xdeltab = c.x - b.x;
    double aslope = ydeltaa/xdeltaa;
    double bslope = ydeltab/xdeltab;
    double ans_x = (aslope*bslope*(a.y-c.y)+bslope*(a.x+b.x) - aslope*(b.x+c.x) ) / (double)((double)2*(bslope-aslope));
    double ans_y = ((double)-1)*((ans_x - (a.x+b.x)/(double)2)/(double)aslope) + (double)(a.y+b.y)/(double)2;
    return {ans_x, ans_y};

}

double dist(pii a, pii b) {
    return sqrt((double)((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}

pair<pii, double> circle (pii a, pii b, pii c) {
    pii q = centre(a, b, c);
    double d = dist(a, q);
    //assert(dist(a, q) <= dist(b, q)+0.00000005);
    //assert(dist(b, q) <= dist(b, q)+0.00000005);
    return {q, d};
}

pii coords[55];

int32_t main() {
    double EPILISON = 0.00000000005;
    int N; cin >> N;
    for (int i = 1; i <= N; i++) {
        double g; cin >> g;
        coords[i].x = g;
    }
    for (int i = 1; i <= N; i++) {
        double g; cin >> g;
        coords[i].y = g;
    }
    double best = 1e9;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                if (i == j or j == k or i == k) continue;
                pair<pii, double> c = circle(coords[i], coords[j], coords[k]);
                bool works = true;
                for (int q = 1; q <= N; q++) {
                    if (dist(c.f, coords[q]) > c.s) works = false;
                }
                if (works) {best = min(best, c.s);}
            }
        }
    }
    cout << fixed;
    cout << setprecision(1000);
    cout << best << "\n";
}
