from random import *
from subprocess import *

for i in range(10000):
    n = randint(1, 3);
    t = randint(1, 3);
    out = open("in.txt", "w");
    print(1, file=out);
    print(n, file=out);
    for _ in range(n):
        print(randint(1, 4), t, file=out)
    out.close();
    g = check_output("python3 c.py < in.txt", shell=True)
    f = check_output("./wrong < in.txt", shell=True)
    if (int(g) != int(f)):
        print("FOUND")
        break
    if (i % 100 == 0):
        print(i)
