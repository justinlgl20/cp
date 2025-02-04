import subprocess

fl = input("Name of input file: ").strip()  

subprocess.call("rm log.txt", shell=True)
subprocess.call("touch log.txt", shell=True)
subprocess.call("g++ -g grader.cpp -o grader -std=gnu++20", shell=True)
subprocess.call("g++ -g solution.cpp -o solution -std=gnu++20", shell=True)

solution = subprocess.Popen(["./solution"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
grader = subprocess.Popen(["./grader"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

with open(fl, "r") as fopen:
    n, m = map(int, fopen.readline().strip().split())
    vals = [list(map(int, fopen.readline().strip().split())) for _ in range(m)]

grader.stdin.write(f"{n} {m}\n".encode())
for i in vals:
    grader.stdin.write(f"{i[0]} {i[1]} {i[2]}\n".encode())
grader.stdin.flush()

for _ in range(m + 1):
    solution.stdin.write(grader.stdout.readline())
solution.stdin.flush()

queries = -1
ans = 0
while True:
    ipt = solution.stdout.readline()
    if not ipt:
        break  
    ans = ipt.decode().split()[-1]
    grader.stdin.write(ipt)
    grader.stdin.flush()
    opt = grader.stdout.readline()
    if not grader.poll() is None:
        break
    
    solution.stdin.write(opt)
    solution.stdin.flush()
    queries += 1
subprocess.call("cat log.txt", shell=True)

