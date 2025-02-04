import subprocess

for _ in range(1000000):
	subprocess.check_output("python3 gen.py > in.txt", shell=True);

	a = subprocess.check_output("./bad<in.txt",shell=True);
	b=subprocess.check_output("./bf<in.txt",shell=True);
	if(int(a)!=int(b)):
		print("FOUND")
		break
	if(_%100==0):
		print(_)
