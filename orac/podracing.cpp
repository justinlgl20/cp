#include <bits/stdc++.h>
 
using namespace std;
 
 
 
#define int long long
 
int gcd(int a, int b) {
        if (b) return gcd(b, a%b);
        return a;
}
 
struct rational {
        int n, d;
        rational(int a, int b) {
                if (a == 0) {
                        n = 0;
                        d = 1;
                        return;
                }
                int g = gcd(a, b);
                n = a/g;
                d = b/g;
        }
        rational() {
                n = 0;
                d = 1;
        }
        rational operator + (rational other) {
                int t = ((n*other.d)+(other.n*d))/gcd(d, other.d);
                int b = (other.d*d)/gcd(d, other.d);
                return rational(t, b);
        }
        rational operator * (rational other) {
                return rational(n*other.n, d*other.d);
        }
        rational operator / (rational other) {
                return (*this)*rational(other.d, other.n);
        }
        bool operator < (rational other) const {
                return n*other.d < other.n*d;
        }
        bool operator == (rational other) const {
                return other.n == n and other.d == d;
        }
 
};
 
#define double rational
 
#define f first
#define s second
 
double EPILISON;
 
struct seg {
        int tl, tr;
        seg *l, *r;
        int lazy_add;
        int val;
        seg(int tl, int tr) {
                this->tl = tl;
                this->tr = tr;
                this->lazy_add = 0;
                this->val = 0;
                if (tl == tr) {val = 0;return;}
                int tm = (tl+tr)/2;
                l = new seg(tl, tm);
                r = new seg(tm+1, tr);
        }
        void lazy_push() {
                if (lazy_add) {
                        val += lazy_add;
                        if (tl != tr) {
                                l->lazy_add += lazy_add;
                                r->lazy_add += lazy_add;
                        }
                        lazy_add = 0;
                }
        }
        int range_max(int ql, int qr) {
                if (ql > tr or qr < tl) return -1e18;
                lazy_push();
                if (ql <= tl and tr <= qr) return val;
                return max(l->range_max(ql, qr), r->range_max(ql, qr));
        }
        void point_set(int p, int v) {
                if (tl == tr) {
                        val = v;
                        lazy_add = 0;
                        return;
                }
                lazy_push();
                int tm = (tl+tr)/2;
                if (p <= tm) l->point_set(p, v);
                else r->point_set(p, v);
                l->lazy_push();
                r->lazy_push();
                val = max(l->val, r->val);
        }
        void range_add(int ql, int qr, int v) {
                if (tl > qr or ql > tr) return;
                if (ql <= tl and tr <= qr) {
                        lazy_add += v;
                        return;
                }
                lazy_push();
                l->range_add(ql, qr, v);
                r->range_add(ql, qr, v);
                l->lazy_push();
                r->lazy_push();
                val = max(l->val, r->val);
        }
};
 
int v, h;
 
struct person {
        int v, h;
        int l, r;
        double val() {
                if (this->v - ::v == 0) {
                        cerr << 3/0 << "\n";
                }
                return rational(((::v)*(this->h)-(this->v)*(::h)), (this->v-(::v)));
        }
};
 
unordered_map<int, int> compress_races;
unordered_map<int, int> decompress_races;
 
person people[200005];
struct event {
        person p;
        bool start; // false if is end
        int pos;
        bool operator < (const event other) const {
                return start > other.start;
        }
};
int N, C;
 
pair<pair<double, double>, int> range[400005]; // map compressed race to range in which if the race length is in, I win. {{l, r}, value}
int comp;
void compress() {
        set<int> poses;
        poses.insert(1);
        poses.insert(N);
        for (int i = 1; i <= C; i++) {
                poses.insert(people[i].r);
                poses.insert(people[i].l);
        }
        int q = 1;
        for (auto i : poses) {
                compress_races[i] = q;
                decompress_races[q] = i;
                q++;
        }
        for (int i = 0; i <= C; i++) {
                people[i] = {people[i].v, people[i].h, compress_races[people[i].l], compress_races[people[i].r]};
        }
        comp = q;
}
 
int no_of_ranges;
 
void gen_ranges() {
        vector<vector<event>> peeps(comp+1, vector<event>());
        for (int i = 1; i <= C; i++) {
                peeps[people[i].r].push_back({people[i], 0, people[i].r});
                peeps[people[i].l].push_back({people[i], 1, people[i].l});
        }
        for (int i = 0; i <= comp; i++) sort(peeps[i].begin(), peeps[i].end());
        multiset<double> big, small;
        big.insert(rational(1e18, 1));
        small.insert(rational(-1e18, 1));
        int prev_pos = 1;
        bool first = true;
        int cant = 0;
        for (int i= 1; i < comp; i++){
                //add people
                int inx = 0;
                while (inx < peeps[i].size() and peeps[i][inx].start) {
                        if (peeps[i][inx].p.v - v == 0 and peeps[i][inx].p.h < h) {cant += 1;}
                        else if (peeps[i][inx].p.v > v) big.insert(peeps[i][inx].p.val());
                        else if (peeps[i][inx].p.v < v) small.insert(peeps[i][inx].p.val());
 
                        inx++;
                }
                int profit = decompress_races[i] - decompress_races[i-1];
                double top = (*big.begin());
                double bottom = (*small.rbegin());
                if (cant) {
                        bottom = rational((int)1050, (int)1);
                        top = rational((int)1049, (int)1);
                }
                range[i] = {{bottom, top}, profit};
                first = false;
                //cerr << i << " " << bottom << " " << top << " " << profit << "\n";
                //remove people
 
                while (inx < peeps[i].size() and not peeps[i][inx].start) {
                        if (peeps[i][inx].p.v - v == 0 and peeps[i][inx].p.h < h) cant -= 1;
                        else if (peeps[i][inx].p.v > v) big.erase(big.find(peeps[i][inx].p.val()));
                        else if (peeps[i][inx].p.v < v) small.erase(small.find(peeps[i][inx].p.val()));
                        inx++;
                }
        }
        no_of_ranges = comp;
}
 
int ans;
map<double, int> compress_l;
map<int, double> decompress_l;
void solve() {
        seg x = seg(0, 1000000);
        set<double> idk;
        vector<pair<pair<double, double>, int>> rangess;
        for (int i = 1; i < comp; i++) {
                double st = range[i].f.f;
                double e = range[i].f.s;
                if (e < st or e < rational(0ll, 1ll)) continue;
                st = max(st, rational(0ll, 1ll));
                idk.insert(st);
                idk.insert(e);
                rangess.push_back({{st, e}, range[i].s});
        } // this part above feels sus
        int i = 0;
        for (auto j : idk) {
                compress_l[j] = i;
                decompress_l[i] = j;
                i++;
        }
        vector<pair<pair<int, int>, int>> ranges;
        for (int i = 0;  i < rangess.size(); i++) {
                ranges.push_back({{compress_l[rangess[i].f.f], compress_l[rangess[i].f.s]}, rangess[i].s});
        }
 
        //cerr << "COMPRESSED RANGES: \n";
 
        ans = 0;
        for (auto i : ranges) {
                int s = i.f.f;
                int e = i.f.s;
                int v = i.s;
                int c = x.range_max(s, s);
                int p = x.range_max(0, s);
                if (p > c) x.point_set(s, p);
                x.range_add(s, e, v);
                /*cerr << i.f.f << " " << i.f.s << " " << i.s << "\n";
                for (int v = 0; v <= 10; v++) {
                        cerr << x.range_max(v, v) << " ";
                }
                cerr << "\n";*/
                ans = max(ans, x.range_max(0, 999999));
        }
}
 
int32_t main() {
        //EPILISON = 0;
        cin >> N >> C >> h >> v;
        for (int i = 1; i <= C; i++) {
                int l, r, hi, vi; cin >> l >> r >> hi >> vi;
                people[i] = {vi, hi, l, r};
        }
        compress();
        gen_ranges();
        solve();
        cout << ans << "\n";
 
}
