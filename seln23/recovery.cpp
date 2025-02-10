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
#include "recovery.h"

void set_scheme(int N, int S) {
	Each bit is in at most 4 subsets
	we get 15 subsets
	two bits are scratched
	we want 2^15 subset activations to correspond with each unique integer if we add them
	if we have subset x with bit i in it, we want some subsets sum to have the rest of what is in x without having i in it
	IF i is in A and i is in B, i is not in v_A+v_B 
	We want some subsets such that the number of occurences of i is odd, and number of occurences of everything else is even
	IF WE HAVE 2 IN CHECK BITS, ITS FINE
	IF WE HAVE 1 IN CHECK BITS and 1 IN NORMAL STUFF, WE CAN SOLVE BECAUSE THE 1 IN NORMAL STUFF IS IN 4 SETS AND THEY CAN'T DELETE ALL OF THEM
	NOW IF THEY HAVE 2 IN NORMAL STUFF WE CAN FIND THEM NORMALLY




}

std::string recover(std::string ID) {

}
