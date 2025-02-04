#include "Alice.h"
#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
#define all(x) (x).begin(), (x).end()
 
template<template<typename> class Container, typename G>
ostream& operator<<(ostream& os, Container<G> x) {
    int f = 0; os << '{'; for (auto &i: x) os << (f++ ? ", " : ""), os << i; os << "}";
    return os;
}
 
#ifdef DEBUG
void __print() {cerr << "]\n";}
 
template<typename T, typename... V>
void __print(T t, V... v) {cerr << t; if (sizeof...(v)) cerr <<", "; _print(v...);}
 
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; __print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

#define pii pair<int, int>


std::vector<std::pair<int,int>> Alice(){
	// add your code here
    srand(69);
    random_device rd;
    mt19937 g(rd());
    
    vector<int> order;
    for (int i = 165; i <= 5000; i++) order.push_back(i);
    //shuffle(all(order));
	
	// change below into your code
    long long x = setN(5000);
    vector<pii> ans;
    ans.emplace_back(1, 2);
    for (int i = 0; i < 64; i++) {
        if (((1ll)<<((ll)i))&x) {
            cerr << i << "\n";
            for (int j = 3+i; j <= 5000; j+=64) ans.emplace_back(1, j);
        } else {
            for (int j = 3+i; j <= 5000; j+=64) ans.emplace_back(2, j);
        }
    }
    return ans;
}
