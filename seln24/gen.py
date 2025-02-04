import subprocess
from random import *

for i in range(1000000):
    n = randint(3, 6)
    out = open("file.in", "w")
    print(n, file=out)
    for i in range(n):
        a = randint(1, 10);
        b = randint(a, 10);
        print(a, b, file=out)
    out.close()

    g = subprocess.check_output("./wrong < file.in", shell=True)
    w = subprocess.check_output("./bf < file.in", shell=True);
    if [int(i) for i in g.split()] != [int(i) for i in w.split()]:
        print("FOUND")
        break;
    if (i%100 == 0):
        print(i)
