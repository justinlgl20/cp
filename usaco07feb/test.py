import subprocess

for i in range(1, 16):
    x = "lilypad."+str(i)
    a = str(subprocess.check_output("./lilypad_pond < allfeb07/"+x+".in", shell=True));
    b = open("allfeb07/"+x+".out").read()
    if (a != b):
        print(i)
        print(a, b);
