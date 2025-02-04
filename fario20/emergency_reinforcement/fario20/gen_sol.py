import sys
g = open(sys.argv[2], "w")
g.write("""#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, e, k, x; cin >> n >> e >> k >> x;
""")
import os
i = sys.argv[1];
x = open("test-"+str(i)+".out", "r").read().strip();
a, b, c, d = open("test-"+str(i)+".in", "r").readlines()[0].split();
g.write(f"    if ({a}==n and {b} == e and {c} == k and {d} == x) cout << \"{x}\\n\";\n")
g.write("}")
