from random import *

m = randint(2, 20);
n = 2*(10**6)//m;
q = 3000;
out = open("file.in", "w")
out.write(str(n)+" " +str(m)+" " +str(q)+"\n");
a = []
for i in range(m):
    l = [str(randint(1, 10000005)) for j in range(n)]
    out.write(" ".join(l)+"\n");
for i in range(q):
    a = randint(1, 2);
    a = 2;
    out.write(str(a)+" ");
    if (a == 1):
        x = randint(1, m);
        y = x
        while (y == x):
            y = randint(1, m);
        x = str(x)
        y = str(y);
        out.write(x+" "+y+"\n")
    else:
        x = randint(1, m);
        y = randint(1, n);
        x = str(x)
        y = str(y);
        out.write(x+" "+y+"\n");
