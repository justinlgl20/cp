import subprocess

for i in range(1000):
    subprocess.check_output("./generate > in.txt", shell=True)
    g = subprocess.check_output("./good < in.txt", shell=True).decode()
    d = subprocess.check_output("./Compiled < in.txt", shell=True).decode()
    if (g.split() != d.split()):
        print("CASE FOUND")
        break
    if (i % 100 == 0):
        print(i);
