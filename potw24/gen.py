import subprocess
from random import*
for i in range(10000):
	n=randint(1,6)
	l=[randint(1,3) for i in range(n)]
	f = open("in.txt", "w")
	f.write(str(n)+"\n")
	f.write(" ".join([str(i) for i in l])+"\n");
	f.close();
	out = subprocess.check_output("./election < in.txt", shell=True);
	out2 = subprocess.check_output("./election2 < in.txt", shell=True);
	x=[l[int(i)-1] for i in out2.split()[1:]];
	if(len(l) and sum(x)-sorted(x)[0] > sum(x)//2+(sum(x)%2)):
		continue;
	if(out.strip() != out2.strip()):
		print("FOUND")
		break
	if(i%1000==0):
		print(i) 
