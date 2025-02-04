#include "edstem.h"

#include <bits/stdc++.h>
using namespace std;
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
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

unordered_map<int, unordered_map<int, int>> anse;
int no = 0;
int query(int i, int j) {
	if (anse.find(i) == anse.end() or anse[i].find(j) == anse[i].end()) {
		dbg(i, j);
		no++;
		int g= ask_question(i, j);
		anse[i][j] = g;
		return g;
	}
	return anse[i][j];
}

bool find_k(int n,int m, int k) {
	int i = n, j = 1;
	while (true) {
		int g = query(i, j);
		if (g == k) return 1;
		if (g > k) i--;
		if (g < k) j++;
		if (i < 1 or j > m) return 0;
	}
	if (no > n+m) while (1)0;
	return 0;
}
