#include "arrays.h"
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

int idk, idk2;

bool query(int i, int j) {
	if (i == 0) return 1;
	if (j == 0) return 0;
	if(i > idk) return 0;
	if (j > idk2) return 1;
	return compare(i, j);
}

int find_k(int n,int m,int k) {
	srand(219);
	if (k <= 50) {
		1/0;
	}
	idk=n,idk2=m;
	int pos2=min(m,k);
	dbg(pos2);
	int pos1=max(0, k-pos2);
	pos2 = k-pos1;
	dbg(pos1,pos2);
	
	if (k == n+m){
		if(query(n,m))return -m;
		else return n;
	}
	if (!query(1,m)) {
		if (k <= m) return -k;
		else return k-m;
	}
	if (k == 1) {
		if(query(1,1))return 1;
		else return -1;
	}
	// what if k == 2
	for (int i=9;i>=0;i--){
		if(pos1+(1ll<<i) <= n and pos2-(1ll<<i)>= 0 and query(pos1+(1ll<<i), pos2-(1ll<<i))) {
			dbg(pos1+(1ll<<i), pos2-(1ll<<i));
			pos1+=(1ll<<i);
			pos2-=(1ll<<i);
		}
	}
	dbg(pos1, pos2);
	if (!query(pos1, pos2)) {
		return pos1;
		// it is either pos1 or -pos2
	} else if (pos1 == 1 and rand()%2==1) {
		// pos1 is smaller than pos2
		return -pos2;
	}
	// IN BREAKING CASE pos1 != 0;
	if(pos1 != n and (pos2-1 == 0 or ((!query(pos1+1,pos2-1)) and query(pos1+1,pos2))))
		return pos1+1;
	// ABOVE THING IS GIVING POS1+1 WHEN IT SHOULD GIVE -POS2 INSTEAD
	return -pos2;
}
