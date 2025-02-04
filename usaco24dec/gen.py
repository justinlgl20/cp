import subprocess
from random import *

for _ in range(100000):
    n, k = randint(1, 5), randint(1, 5);
    x = [randint(1, 14) for i in range(n)]
    out = open("file.in", "w");
    print(1, file=out);
    print(n, k, file=out);
    print(*x, file=out);
    for i in range(k):
        s = randint(1, 14);
        e = randint(s, 14);
        o = 0;
        for j in x:
            o += (s <= j and j <= e);
        t = randint(0, o);
        print(s, e, t, file=out)
    out.close();
    f = subprocess.check_output("./bf < file.in", shell=True);
    g = subprocess.check_output("./wrong < file.in", shell=True);
    if (int(f)!= int(g)):
        print("FOUND")
        break
    if (_%1000 == 0):
        print(_);
