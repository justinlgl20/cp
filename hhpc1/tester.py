import subprocess,random

random.seed(69)

for _ in range(10000000):
    file = open("test.in", "w");
    n = random.randint(10, 50);
    q = random.randint(1, 30);
    a = []
    for i in range(n):
        a.append(random.randint(-3, 3));
    file.write(str(n)+" "+str(q)+"\n");
    file.write(" ".join([str(i) for i in a])+"\n")
    for i in range(q):
        l = random.randint(1, n-3)
        r = random.randint(l, n)
        file.write(str(l)+" " +str(r) + "\n")
    file.close()
    g = subprocess.check_output("./bad < test.in", shell=True);
    a = subprocess.check_output("./good < test.in", shell=True);
    if (g != a): break;
    if (_ % 100 == 0):
        print(_)
