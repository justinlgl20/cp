import subprocess

problem = "show"
for i in range(1, 7):
    f = problem + str(i)
    g = [int(i.strip()) for i in subprocess.check_output("./"+problem+"exe < "+problem+"/"+f+".in", shell=True).split()]
    q = [int(i.strip()) for i in open(problem+"/"+f+".ans", "r").read().split()]
    if (g != q):
        print(i, "doesn't work", g[0], q[0]);
    else:
        print(i, "works");
print("SUCCESS");
