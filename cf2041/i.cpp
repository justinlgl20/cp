#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}

ostream& operator<<(ostream& os, string x) {
    for (auto i : x) os << i;
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

int sz[2000005];
string thing[2000005];

struct comp {
    bool operator()(int a, int b) const {
        if (sz[a] == sz[b]) {
            // smallest lexicographic order
            return thing[a] > thing[b];
        }
        return sz[a] < sz[b]; 
    }
};

struct node {
    unordered_map<int, node*> children;
    node* parent;
    set<int, comp> ids; // end is best
    node() {
        ids.clear();
        parent = NULL;
    }
    void add(int id, int inx) {
        ids.insert(id);
        if (inx == sz[id]) return;
        int c = thing[id][inx]-'!';
        if (children.find(c) == children.end()) {
            children[c] = new node();
            children[c]->parent = this;
        }
        children[c]->add(id, inx+1);
    }
    void remove(int id, int inx) {
        ids.erase(ids.find(id));
        if (inx == sz[id]) return;
        int c = thing[id][inx]-'!';
        children[c]->remove(id, inx+1);
    }
    int query(int id, int inx) {
        if (inx == sz[id]) {
            if (ids.size() == 0) return -1;
            return *ids.rbegin();
        }
        int c = thing[id][inx]-'!';
        if (children.find(c) == children.end()) return -1;
        return children[c]->query(id, inx+1);
    }
};

node* root;

node* current;

void add(int i, string s) {
    thing[i] = s;
    sz[i] = s.size();
    dbg(thing[i], sz[i], i);
    root->add(i, 0);
}

void remove(int i) {
    root->remove(i, 0);
    sz[i] = 0;
    thing[i] = "";
}

void append(string s) {
    for (auto i : s) {
        if ((current->children).find(i-'!') == (current->children).end()) {
            current->children[i-'!'] = new node();
            current->children[i-'!']->parent = current;
        }
        current = current->children[i-'!'];
    }
}

int query() {
    if ((current->ids).size()) {
        return *(current->ids).rbegin();
    }
    return -1;
}

int32_t main() {
    root = new node();
    root->parent = root;
    current = root;
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        dbg(s);
        if (s == "add") {
            int id; string c;
            cin >> id >> c;
            add(id, c);
        } else if (s == "append") {
            string c; cin >> c;
            append(c);
        } else if (s == "delete") {
            int i; cin >> i;
            remove(i);
        } else if (s == "backspace") {
            int i; cin >> i;
            for (int j = 0; j < i; j++) {
                current = current->parent;
            }
        }
        dbg("FINISH");
        cout << query() << "\n";
    }
}
