#include "array.h"

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

#define q ask_question

vector<int> find_array(int n) {
	vector<int> ans(n, 0);
	int a= q(0, 1), b=q(1,2),c=q(0,2);
	ans[0] = (a+b+c)/2 - b;
	ans[1] = a-ans[0];
	ans[2] = c-ans[0];
	for (int i = 3; i < n; i++) ans[i] = q(i, 0)-ans[0];
	return ans;
}
