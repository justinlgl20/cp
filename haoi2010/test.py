import subprocess
from random import *


for i in range(1000000):
    n = randint(3, 50);
    m = randint(0, 10);
    s = randint(0, 10000);
    u = [randint(0, 10000) for i in range(n)]
    d = [randint(0, 100) for i in range(n)]
    x = open("file.in", "w")
    x.write(str(n)+" "+str(m)+" "+str(s)+"\n")
    x.write(" ".join([str(i) for i in u])+"\n")
    x.write(" ".join([str(i) for i in d])+"\n")
    x.close();

    a = subprocess.check_output("./P2517 < file.in", shell=True);
    try:
        str(a)
    except:
        break;
    if (i % 1000 == 0):
        print(i)
