import subprocess;
for i in range(8, 2001):
    open("in.txt", "w").write(str(i)+"\n")
    g = subprocess.check_output("./2 < in.txt", shell=True).decode()
    if (int(g) != 1):
        print(i)
        break
