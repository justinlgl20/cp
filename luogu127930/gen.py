import subprocess, random

for i in range(1000000000):
    n = random.randint(4, 15);
    k = random.randint(1, 5);
    a = list(set([random.randint(1, 20) for i in range(n)]))
    n = len(a);
    out = open("file.in", "w")
    out.write(str(n)+" "+str(k)+"\n")
    out.write(" ".join(str(i) for i in a))
    out.close();

    a = subprocess.check_output("./c < file.in", shell=True);
    b = subprocess.check_output("python3 c.py < file.in", shell=True)
    if (a != b):
        print("FOUND");
        break
    if (i % 100 == 0):
        print(i);
